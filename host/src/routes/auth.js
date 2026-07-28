const express = require('express');
const router = express.Router();
const KeyManager = require('../models/KeyManager');
const { rateLimiter, hwidRateLimiter, validateRequest, encryptPayload, decryptPayload } = require('../middleware/security');

router.post('/handshake', rateLimiter(20), hwidRateLimiter, async (req, res) => {
    try {
        const clientPayload = req.body;
        const payload = clientPayload?.encrypted ? decryptPayload(clientPayload.encrypted) : clientPayload;
        if (!payload?.key || !payload?.hwid) {
            await KeyManager.logAction({ key: payload?.key || 'unknown', hwid: payload?.hwid || 'unknown', ip: req.ip, action: 'auth', status: 'failed', details: 'Missing key or hwid' });
            return res.status(400).json({ error: 'Missing key or hwid', ok: false });
        }
        const result = await KeyManager.validateKey(payload.key, payload.hwid, req.ip);
        if (!result.valid) {
            return res.status(401).json({ error: result.reason, ok: false });
        }
        const key = result.key;
        const jwt = require('jsonwebtoken');
        const sessionToken = jwt.sign(
            { kid: key.id, exp: Math.floor(Date.now() / 1000) + 3600 },
            process.env.JWT_SECRET || 'jwt-secret-change-me'
        );
        res.json({
            ok: true,
            sessionToken,
            expiresAt: key.expires_at,
            planType: key.plan_type,
            serverTime: new Date().toISOString()
        });
    } catch (err) {
        console.error('[AUTH]', err);
        res.status(500).json({ error: 'Internal error', ok: false });
    }
});

router.post('/verify', async (req, res) => {
    try {
        const token = req.headers['x-session-token'];
        if (!token) return res.status(401).json({ valid: false, error: 'No session token' });
        const jwt = require('jsonwebtoken');
        const decoded = jwt.verify(token, process.env.JWT_SECRET || 'jwt-secret-change-me');
        const record = await KeyManager.getKeyInfo(decoded.kid);
        if (!record || record.status === 'banned' || new Date(record.expires_at) < new Date()) {
            return res.json({ valid: false, error: 'Session expired or key invalid' });
        }
        const timeLeft = new Date(record.expires_at) - new Date();
        res.json({ valid: true, expiresAt: record.expires_at, timeLeftMs: timeLeft, planType: record.plan_type });
    } catch {
        res.status(401).json({ valid: false, error: 'Invalid token' });
    }
});

router.post('/encrypted-handshake', rateLimiter(20), hwidRateLimiter, async (req, res) => {
    try {
        const payload = decryptPayload(req.body?.encrypted);
        if (!payload?.key || !payload?.hwid) {
            return res.status(400).json({ error: 'Invalid encrypted payload' });
        }
        const result = await KeyManager.validateKey(payload.key, payload.hwid, req.ip);
        if (!result.valid) return res.status(401).json({ error: result.reason });
        const jwt = require('jsonwebtoken');
        const sessionToken = jwt.sign({ kid: result.key.id }, process.env.JWT_SECRET || 'jwt-secret-change-me', { expiresIn: '1h' });
        res.json({
            encrypted: encryptPayload({ ok: true, sessionToken, expiresAt: result.key.expires_at })
        });
    } catch (err) {
        console.error('[ENCRYPTED_AUTH]', err);
        res.status(500).json({ error: 'Internal error' });
    }
});

module.exports = router;
