const crypto = require('crypto');
const { pool } = require('../config/database');
const { RATE_LIMIT } = require('../config/constants');

const rateLimitStore = new Map();

const ENCRYPTION_KEY = crypto.createHash('sha256')
    .update(process.env.ENCRYPTION_SECRET || 'fallback-secret-change-me')
    .digest('hex')
    .substring(0, 32);

function encryptPayload(data) {
    const iv = crypto.randomBytes(16);
    const cipher = crypto.createCipheriv('aes-256-gcm', Buffer.from(ENCRYPTION_KEY), iv);
    let encrypted = cipher.update(JSON.stringify(data), 'utf8', 'hex');
    encrypted += cipher.final('hex');
    const tag = cipher.getAuthTag().toString('hex');
    return JSON.stringify({ iv: iv.toString('hex'), data: encrypted, tag });
}

function decryptPayload(encryptedStr) {
    try {
        const { iv, data, tag } = JSON.parse(encryptedStr);
        const decipher = crypto.createDecipheriv('aes-256-gcm',
            Buffer.from(ENCRYPTION_KEY), Buffer.from(iv, 'hex'));
        decipher.setAuthTag(Buffer.from(tag, 'hex'));
        let decrypted = decipher.update(data, 'hex', 'utf8');
        decrypted += decipher.final('utf8');
        return JSON.parse(decrypted);
    } catch { return null; }
}

function rateLimiter(maxAttempts = RATE_LIMIT.MAX_LOGIN_ATTEMPTS) {
    return (req, res, next) => {
        const key = req.ip || req.connection.remoteAddress;
        const now = Date.now();
        if (!rateLimitStore.has(key)) {
            rateLimitStore.set(key, { count: 1, startTime: now });
            return next();
        }
        const entry = rateLimitStore.get(key);
        if (now - entry.startTime > RATE_LIMIT.WINDOW_MS) {
            rateLimitStore.set(key, { count: 1, startTime: now });
            return next();
        }
        entry.count++;
        if (entry.count > maxAttempts) {
            return res.status(429).json({
                error: 'Too many requests. Try again later.',
                retryAfter: Math.ceil((RATE_LIMIT.WINDOW_MS - (now - entry.startTime)) / 1000)
            });
        }
        next();
    };
}

function apiKeyAuth(req, res, next) {
    const apiKey = req.headers['x-api-key'];
    if (!apiKey || apiKey !== process.env.API_SECRET_KEY) {
        return res.status(401).json({ error: 'Invalid API key' });
    }
    next();
}

function adminAuth(req, res, next) {
    const authHeader = req.headers['authorization'];
    if (!authHeader || !authHeader.startsWith('Bearer ')) {
        return res.status(401).json({ error: 'No token provided' });
    }
    const token = authHeader.split(' ')[1];
    try {
        const jwt = require('jsonwebtoken');
        const decoded = jwt.verify(token, process.env.JWT_SECRET || 'jwt-secret-change-me');
        req.admin = decoded;
        next();
    } catch {
        return res.status(401).json({ error: 'Invalid or expired token' });
    }
}

function validateRequest(schema) {
    return (req, res, next) => {
        const errors = [];
        for (const [field, rules] of Object.entries(schema)) {
            const value = req.body[field];
            if (rules.required && (value === undefined || value === null)) {
                errors.push(`${field} is required`);
                continue;
            }
            if (value !== undefined && value !== null) {
                if (rules.type === 'string' && typeof value !== 'string') errors.push(`${field} must be a string`);
                if (rules.type === 'number' && (typeof value !== 'number' || isNaN(value))) errors.push(`${field} must be a number`);
                if (rules.minLength && value.length < rules.minLength) errors.push(`${field} too short`);
                if (rules.maxLength && value.length > rules.maxLength) errors.push(`${field} too long`);
            }
        }
        if (errors.length > 0) return res.status(400).json({ error: 'Validation failed', details: errors });
        next();
    };
}

async function hwidRateLimiter(req, res, next) {
    const hwid = req.body?.hwid || req.query?.hwid;
    if (hwid) {
        try {
            const { rows } = await pool.query(`
                SELECT COUNT(*) as count FROM logs 
                WHERE hwid = $1 AND status = 'failed' 
                AND timestamp > NOW() - INTERVAL '15 minutes'
            `, [hwid]);
            if (parseInt(rows[0].count) >= 10) {
                return res.status(429).json({ error: 'HWID temporarily blocked due to excessive failures' });
            }
        } catch {}
    }
    next();
}

module.exports = {
    encryptPayload, decryptPayload,
    rateLimiter, apiKeyAuth, adminAuth, validateRequest,
    hwidRateLimiter
};
