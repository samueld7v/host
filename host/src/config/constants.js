module.exports = {
    KEY_STATUS: {
        ACTIVE: 'active',
        EXPIRED: 'expired',
        BANNED: 'banned',
        UNUSED: 'unused'
    },
    PLAN_TYPES: {
        TRIAL: 'trial',
        MONTHLY: 'monthly',
        QUARTERLY: 'quarterly',
        LIFETIME: 'lifetime'
    },
    DURATIONS: {
        trial: 1,
        monthly: 30,
        quarterly: 90,
        lifetime: 36500
    },
    RATE_LIMIT: {
        WINDOW_MS: 15 * 60 * 1000,
        MAX_LOGIN_ATTEMPTS: 5,
        MAX_API_CALLS: 100
    },
    CRYPTO: {
        KEY_LENGTH: 32,
        IV_LENGTH: 16,
        TAG_LENGTH: 16,
        SALT_ROUNDS: 12,
        HASH_ALGO: 'sha256'
    },
    JWT: {
        EXPIRY: '24h',
        ALGORITHM: 'HS256'
    }
};
