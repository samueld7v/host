const { Pool } = require('pg');

const isProduction = process.env.NODE_ENV === 'production';

const pool = new Pool({
    connectionString: process.env.DATABASE_URL || process.env.POSTGRES_URL,
    ssl: isProduction ? { rejectUnauthorized: false } : false,
    max: 10,
    idleTimeoutMillis: 30000,
    connectionTimeoutMillis: 5000,
});

async function initDatabase() {
    const client = await pool.connect();
    try {
        await client.query(`
            CREATE TABLE IF NOT EXISTS keys (
                id SERIAL PRIMARY KEY,
                key_hash TEXT NOT NULL UNIQUE,
                key_raw TEXT DEFAULT '',
                key_prefix TEXT DEFAULT '',
                duration INTEGER NOT NULL DEFAULT 30,
                created_at TIMESTAMPTZ DEFAULT NOW(),
                expires_at TIMESTAMPTZ,
                last_login TIMESTAMPTZ,
                hwid TEXT DEFAULT NULL,
                ip_address TEXT DEFAULT NULL,
                status TEXT CHECK(status IN ('active','expired','banned','unused')) DEFAULT 'unused',
                plan_type TEXT CHECK(plan_type IN ('trial','monthly','quarterly','lifetime')) DEFAULT 'monthly',
                created_by TEXT DEFAULT 'system'
            );
        `);

        await client.query(`
            CREATE TABLE IF NOT EXISTS banned_hwids (
                id SERIAL PRIMARY KEY,
                hwid_hash TEXT NOT NULL UNIQUE,
                reason TEXT DEFAULT '',
                banned_at TIMESTAMPTZ DEFAULT NOW(),
                banned_by TEXT DEFAULT 'system'
            );
        `);

        await client.query(`
            CREATE TABLE IF NOT EXISTS logs (
                id SERIAL PRIMARY KEY,
                key_used TEXT DEFAULT '',
                hwid TEXT DEFAULT '',
                ip_address TEXT DEFAULT '',
                action TEXT NOT NULL,
                status TEXT CHECK(status IN ('success','failed','blocked')) DEFAULT 'failed',
                details TEXT DEFAULT '',
                timestamp TIMESTAMPTZ DEFAULT NOW()
            );
        `);

        await client.query(`
            CREATE TABLE IF NOT EXISTS admins (
                id SERIAL PRIMARY KEY,
                username TEXT NOT NULL UNIQUE,
                password_hash TEXT NOT NULL,
                role TEXT DEFAULT 'admin',
                created_at TIMESTAMPTZ DEFAULT NOW(),
                last_login TIMESTAMPTZ
            );
        `);

        await client.query(`ALTER TABLE keys ADD COLUMN IF NOT EXISTS key_raw TEXT DEFAULT ''`);
        await client.query(`CREATE INDEX IF NOT EXISTS idx_keys_status ON keys(status)`);
        await client.query(`CREATE INDEX IF NOT EXISTS idx_keys_hwid ON keys(hwid)`);
        await client.query(`CREATE INDEX IF NOT EXISTS idx_keys_expires ON keys(expires_at)`);
        await client.query(`CREATE INDEX IF NOT EXISTS idx_logs_timestamp ON logs(timestamp)`);
        await client.query(`CREATE INDEX IF NOT EXISTS idx_logs_key ON logs(key_used)`);

        await seedDefaultAdmin(client);

        console.log('[DB] PostgreSQL connected and tables created');
    } finally {
        client.release();
    }
    return pool;
}

async function seedDefaultAdmin(client) {
    const bcrypt = require('bcrypt');
    const { rows } = await client.query('SELECT id FROM admins WHERE username = $1', ['samuel']);
    if (rows.length === 0) {
        const existing = await client.query('SELECT id FROM admins WHERE username = $1', ['admin']);
        if (existing.rows.length > 0) {
            const hash = await bcrypt.hash('samuel', 12);
            await client.query('UPDATE admins SET username = $1, password_hash = $2 WHERE username = $3', ['samuel', hash, 'admin']);
            console.log('[DB] Admin updated to samuel:samuel');
        } else {
            const hash = await bcrypt.hash('samuel', 12);
            await client.query('INSERT INTO admins (username, password_hash) VALUES ($1, $2)', ['samuel', hash]);
            console.log('[DB] Admin created (samuel:samuel)');
        }
    }
}

module.exports = { pool, initDatabase };
