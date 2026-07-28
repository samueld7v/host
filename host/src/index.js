require('dotenv').config();
const express = require('express');
const cors = require('cors');
const helmet = require('helmet');
const morgan = require('morgan');
const path = require('path');
const { initDatabase } = require('./config/database');

const authRoutes = require('./routes/auth');
const adminRoutes = require('./routes/admin');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(helmet({
    contentSecurityPolicy: false,
    crossOriginResourcePolicy: { policy: 'cross-origin' }
}));
app.use(cors({
    origin: process.env.CORS_ORIGIN || '*',
    methods: ['GET', 'POST', 'PUT', 'DELETE'],
    allowedHeaders: ['Content-Type', 'Authorization', 'X-API-Key', 'X-Session-Token', 'X-Encrypt-Response']
}));
app.use(express.json({ limit: '1mb' }));
app.use(morgan('combined'));

app.use('/api/auth', authRoutes);
app.use('/api/admin', adminRoutes);

app.get('/api/health', (req, res) => {
    res.json({ status: 'healthy', timestamp: new Date().toISOString(), version: '2.0.0' });
});

app.get('/api/server-time', (req, res) => {
    res.json({ serverTime: Date.now(), serverTimeISO: new Date().toISOString() });
});

const panelPath = path.join(__dirname, '..', 'admin-panel');
app.use('/panel', express.static(panelPath));
app.get('/panel*', (req, res) => {
    res.sendFile(path.join(panelPath, 'index.html'));
});

app.use((err, req, res, next) => {
    console.error('[ERROR]', err);
    res.status(500).json({ error: 'Internal server error' });
});

initDatabase().then(() => {
    app.listen(PORT, '0.0.0.0', () => {
        console.log(`[API] Server running on port ${PORT}`);
        console.log(`[API] Admin panel: http://localhost:${PORT}/panel`);
        console.log(`[API] Health check: http://localhost:${PORT}/api/health`);
    });
}).catch(err => {
    console.error('[API] Failed to initialize database:', err);
    process.exit(1);
});

module.exports = app;
