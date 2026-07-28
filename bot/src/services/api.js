const axios = require('axios');

const API_BASE = process.env.API_URL || 'http://localhost:3000/api';
const API_KEY = process.env.API_SECRET_KEY;

const api = axios.create({
    baseURL: API_BASE,
    headers: {
        'Content-Type': 'application/json',
        'X-API-Key': API_KEY
    },
    timeout: 10000
});

async function getStats() {
    const res = await api.get('/admin/stats', {
        headers: { Authorization: `Bearer ${getAdminToken()}` }
    });
    return res.data;
}

async function generateKeys(duration, planType, count, prefix = '') {
    const res = await api.post('/admin/keys/generate',
        { duration, plan_type: planType, count, prefix },
        { headers: { Authorization: `Bearer ${getAdminToken()}` } }
    );
    return res.data;
}

async function resetHwid(key) {
    const res = await api.post('/admin/keys/reset-hwid', { key },
        { headers: { Authorization: `Bearer ${getAdminToken()}` } });
    return res.data;
}

async function banKey(key) {
    const res = await api.post('/admin/keys/ban', { key },
        { headers: { Authorization: `Bearer ${getAdminToken()}` } });
    return res.data;
}

async function deleteKey(key) {
    const res = await api.post('/admin/keys/delete', { key },
        { headers: { Authorization: `Bearer ${getAdminToken()}` } });
    return res.data;
}

async function getKeyInfo(key) {
    const res = await api.get(`/admin/keys/info/${encodeURIComponent(key)}`,
        { headers: { Authorization: `Bearer ${getAdminToken()}` } });
    return res.data;
}

async function banHwid(hwid, reason) {
    const res = await api.post('/admin/hwid/ban', { hwid, reason },
        { headers: { Authorization: `Bearer ${getAdminToken()}` } });
    return res.data;
}

function getAdminToken() {
    return process.env.ADMIN_JWT || '';
}

module.exports = { getStats, generateKeys, resetHwid, banKey, deleteKey, getKeyInfo, banHwid };
