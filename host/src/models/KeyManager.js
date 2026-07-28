const { pool } = require('../config/database');
const crypto = require('crypto');
const { KEY_STATUS } = require('../config/constants');

const PLAN_CODES = { trial: 'TRIAL', monthly: 'MENSAL', quarterly: 'TRIMESTRAL', lifetime: 'VITALICIO' };

function randSegment(len = 6) {
    const chars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
    let out = '';
    for (let i = 0; i < len; i++) out += chars[crypto.randomInt(chars.length)];
    return out;
}

class KeyManager {
    static hashKey(key) {
        return crypto.createHash('sha256').update(key).digest('hex');
    }
    static generateKey(planType = 'monthly', prefix = '') {
        const code = PLAN_CODES[planType] || 'MENSAL';
        if (prefix) {
            const random = crypto.randomBytes(5).toString('hex').toUpperCase();
            return `${prefix}-${random}`;
        }
        return `M-${code}-${randSegment()}-${randSegment()}-${randSegment()}-${randSegment()}`;
    }
    static async createKey({ duration = 30, planType = 'monthly', prefix = '', createdBy = 'system' }) {
        const rawKey = this.generateKey(planType, prefix);
        const keyHash = this.hashKey(rawKey);
        const expiresAt = new Date(Date.now() + duration * 24 * 60 * 60 * 1000).toISOString();
        await pool.query(
            `INSERT INTO keys (key_hash, key_raw, key_prefix, duration, expires_at, status, plan_type, created_by)
             VALUES ($1, $2, $3, $4, $5, $6, $7, $8)`,
            [keyHash, rawKey, prefix, duration, expiresAt, KEY_STATUS.UNUSED, planType, createdBy]
        );
        return rawKey;
    }
    static async createKeysBulk({ count = 1, duration = 30, planType = 'monthly', prefix = '', createdBy = 'system' }) {
        const keys = [];
        const client = await pool.connect();
        try {
            await client.query('BEGIN');
            for (let i = 0; i < count; i++) {
                const rawKey = this.generateKey(planType, prefix);
                const keyHash = this.hashKey(rawKey);
                const expiresAt = new Date(Date.now() + duration * 24 * 60 * 60 * 1000).toISOString();
                await client.query(
                    `INSERT INTO keys (key_hash, key_raw, key_prefix, duration, expires_at, status, plan_type, created_by)
                     VALUES ($1, $2, $3, $4, $5, $6, $7, $8)`,
                    [keyHash, rawKey, prefix, duration, expiresAt, KEY_STATUS.UNUSED, planType, createdBy]
                );
                keys.push(rawKey);
            }
            await client.query('COMMIT');
        } catch (e) {
            await client.query('ROLLBACK');
            throw e;
        } finally {
            client.release();
        }
        return keys;
    }
    static async validateKey(key, hwid, ip) {
        const keyHash = this.hashKey(key);
        const { rows } = await pool.query('SELECT * FROM keys WHERE key_hash = $1', [keyHash]);
        if (rows.length === 0) return { valid: false, reason: 'Key not found' };
        const record = rows[0];
        if (record.status === KEY_STATUS.BANNED) return { valid: false, reason: 'Key is banned' };
        const banned = await pool.query('SELECT id FROM banned_hwids WHERE hwid_hash = $1', [this.hashKey(hwid)]);
        if (banned.rows.length > 0) return { valid: false, reason: 'HWID is banned' };
        if (new Date(record.expires_at) < new Date()) {
            await pool.query('UPDATE keys SET status = $1 WHERE id = $2', [KEY_STATUS.EXPIRED, record.id]);
            return { valid: false, reason: 'Key expired' };
        }
        if (record.hwid && record.hwid !== hwid) return { valid: false, reason: 'HWID mismatch' };
        await pool.query(
            `UPDATE keys SET hwid = $1, ip_address = $2, status = $3, last_login = NOW()
             WHERE id = $4`,
            [hwid, ip, KEY_STATUS.ACTIVE, record.id]
        );
        await this.logAction({ key, hwid, ip, action: 'auth', status: 'success', details: 'Authenticated' });
        return { valid: true, key: record };
    }
    static async resetHwid(key) {
        const keyHash = this.hashKey(key);
        const { rowCount } = await pool.query(
            'UPDATE keys SET hwid = NULL, status = $1 WHERE key_hash = $2 AND status != $3',
            [KEY_STATUS.UNUSED, keyHash, KEY_STATUS.BANNED]
        );
        return rowCount > 0;
    }
    static async banKey(key) {
        const keyHash = this.hashKey(key);
        const { rowCount } = await pool.query('UPDATE keys SET status = $1 WHERE key_hash = $2', [KEY_STATUS.BANNED, keyHash]);
        return rowCount > 0;
    }
    static async unbanKey(key) {
        const keyHash = this.hashKey(key);
        const { rowCount } = await pool.query(
            'UPDATE keys SET status = $1 WHERE key_hash = $2 AND status = $3',
            [KEY_STATUS.UNUSED, keyHash, KEY_STATUS.BANNED]
        );
        return rowCount > 0;
    }
    static async extendKey(key, extraDays) {
        const keyHash = this.hashKey(key);
        const { rows } = await pool.query('SELECT expires_at FROM keys WHERE key_hash = $1', [keyHash]);
        if (rows.length === 0) return false;
        const currentExpiry = new Date(rows[0].expires_at);
        const newExpiry = new Date(currentExpiry.getTime() + extraDays * 24 * 60 * 60 * 1000).toISOString();
        await pool.query('UPDATE keys SET expires_at = $1, status = $2 WHERE key_hash = $3',
            [newExpiry, KEY_STATUS.ACTIVE, keyHash]);
        return true;
    }
    static async deleteKey(key) {
        const keyHash = this.hashKey(key);
        const { rowCount } = await pool.query('DELETE FROM keys WHERE key_hash = $1', [keyHash]);
        return rowCount > 0;
    }
    static async getKeyInfo(key) {
        const keyHash = this.hashKey(key);
        const { rows } = await pool.query('SELECT * FROM keys WHERE key_hash = $1', [keyHash]);
        return rows[0] || null;
    }
    static async banHwid(hwid, reason = '', bannedBy = 'system') {
        const hwidHash = this.hashKey(hwid);
        try {
            await pool.query(
                'INSERT INTO banned_hwids (hwid_hash, reason, banned_by) VALUES ($1, $2, $3)',
                [hwidHash, reason, bannedBy]
            );
            await pool.query('UPDATE keys SET status = $1 WHERE hwid = $2', [KEY_STATUS.BANNED, hwid]);
            return true;
        } catch { return false; }
    }
    static async getAllKeys(filters = {}) {
        let query = 'SELECT * FROM keys WHERE 1=1';
        const params = [];
        let paramIdx = 1;
        if (filters.status) { query += ` AND status = $${paramIdx++}`; params.push(filters.status); }
        if (filters.plan_type) { query += ` AND plan_type = $${paramIdx++}`; params.push(filters.plan_type); }
        if (filters.search) {
            query += ` AND (key_raw LIKE $${paramIdx} OR key_hash LIKE $${paramIdx} OR ip_address LIKE $${paramIdx} OR hwid LIKE $${paramIdx})`;
            params.push(`%${filters.search}%`);
            paramIdx++;
        }
        query += ' ORDER BY created_at DESC';
        if (filters.limit) { query += ` LIMIT $${paramIdx++}`; params.push(filters.limit); }
        if (filters.offset) { query += ` OFFSET $${paramIdx++}`; params.push(filters.offset); }
        const { rows } = await pool.query(query, params);
        return rows;
    }
    static async getStats() {
        const total = await pool.query('SELECT COUNT(*) as count FROM keys');
        const active = await pool.query("SELECT COUNT(*) as count FROM keys WHERE status = 'active' AND expires_at > NOW()");
        const expired = await pool.query("SELECT COUNT(*) as count FROM keys WHERE status = 'expired' OR expires_at < NOW()");
        const banned = await pool.query("SELECT COUNT(*) as count FROM keys WHERE status = 'banned'");
        const unused = await pool.query("SELECT COUNT(*) as count FROM keys WHERE status = 'unused'");
        const activeSessions = await pool.query("SELECT COUNT(*) as count FROM keys WHERE hwid IS NOT NULL AND status = 'active' AND expires_at > NOW()");
        return {
            total: parseInt(total.rows[0].count),
            active: parseInt(active.rows[0].count),
            expired: parseInt(expired.rows[0].count),
            banned: parseInt(banned.rows[0].count),
            unused: parseInt(unused.rows[0].count),
            activeSessions: parseInt(activeSessions.rows[0].count)
        };
    }
    static async logAction({ key, hwid, ip, action, status, details = '' }) {
        await pool.query(
            `INSERT INTO logs (key_used, hwid, ip_address, action, status, details)
             VALUES ($1, $2, $3, $4, $5, $6)`,
            [key || '', hwid || '', ip || '', action, status, details]
        );
    }
    static async getLogs(limit = 100, offset = 0) {
        const { rows } = await pool.query(
            'SELECT * FROM logs ORDER BY timestamp DESC LIMIT $1 OFFSET $2', [limit, offset]
        );
        return rows;
    }
    static async getRecentLogs(minutes = 60) {
        const { rows } = await pool.query(
            'SELECT * FROM logs WHERE timestamp > NOW() - $1::interval ORDER BY timestamp DESC LIMIT 50',
            [`${minutes} minutes`]
        );
        return rows;
    }
}

module.exports = KeyManager;
