require('dotenv').config();
const express = require('express');
const cors = require('cors');
const jwt = require('jsonwebtoken');
const path = require('path');
const { User, License } = require('./database');
const { getKeyAuth } = require('./keyauth');

const app = express();
const PORT = process.env.PORT || 3000;
const JWT_SECRET = process.env.JWT_SECRET || 'hyperx-dev-secret';

app.use(cors());
app.use(express.json());
app.use(express.static(path.join(__dirname, 'public')));

function generateToken(userId) {
  return jwt.sign({ userId }, JWT_SECRET, { expiresIn: '24h' });
}

function authMiddleware(req, res, next) {
  const token = req.headers.authorization?.split(' ')[1];
  if (!token) return res.status(401).json({ success: false, message: 'No token provided' });

  try {
    const decoded = jwt.verify(token, JWT_SECRET);
    const user = User.findById(decoded.userId);
    if (!user) return res.status(401).json({ success: false, message: 'User not found' });
    if (user.is_banned) return res.status(403).json({ success: false, message: 'Account is banned' });

    req.user = user;
    next();
  } catch {
    return res.status(401).json({ success: false, message: 'Invalid token' });
  }
}

app.post('/api/auth/init', async (req, res) => {
  try {
    if (process.env.KEYAUTH_OWNERID && process.env.KEYAUTH_OWNERID !== 'your_owner_id_here') {
      const ka = getKeyAuth();
      const result = await ka.init();
      return res.json({ success: true, keyauth: result.success, message: 'KeyAuth initialized' });
    }
    res.json({ success: true, keyauth: false, message: 'Running in local mode' });
  } catch {
    res.json({ success: true, keyauth: false, message: 'Running in local mode' });
  }
});

app.post('/api/auth/login', async (req, res) => {
  try {
    const { username, password } = req.body;
    if (!username || !password) {
      return res.status(400).json({ success: false, message: 'Username and password required' });
    }

    const user = User.findByUsername(username);
    if (!user) {
      return res.status(401).json({ success: false, message: 'Invalid username or password' });
    }

    if (!User.verifyPassword(user, password)) {
      return res.status(401).json({ success: false, message: 'Invalid username or password' });
    }

    if (user.is_banned) {
      return res.status(403).json({ success: false, message: 'Account is banned' });
    }

    User.updateLastLogin(user.id);
    const token = generateToken(user.id);
    const profile = User.getProfile(user.id);

    res.json({
      success: true,
      token,
      user: {
        id: profile.id,
        username: profile.username,
        license: profile.license_key_id,
        product: profile.product,
        status: profile.status,
        expires_at: profile.expires_at,
        created_at: profile.created_at,
        last_login: profile.last_login
      }
    });
  } catch (err) {
    console.error('Login error:', err);
    res.status(500).json({ success: false, message: 'Internal server error' });
  }
});

app.post('/api/auth/register', async (req, res) => {
  try {
    const { username, password, license_key } = req.body;
    if (!username || !password) {
      return res.status(400).json({ success: false, message: 'Username and password required' });
    }
    if (!license_key) {
      return res.status(400).json({ success: false, message: 'License key required for registration' });
    }

    const existing = User.findByUsername(username);
    if (existing) {
      return res.status(409).json({ success: false, message: 'Username already taken' });
    }

    let keyValid = false;

    if (process.env.KEYAUTH_OWNERID && process.env.KEYAUTH_OWNERID !== 'your_owner_id_here') {
      const ka = getKeyAuth();
      const licenseResult = await ka.license(license_key);
      if (!licenseResult.success) {
        return res.status(401).json({ success: false, message: 'Invalid license key' });
      }
      keyValid = true;
    } else {
      const existingLic = License.findByKey(license_key);
      if (!existingLic) {
        License.create(license_key);
      }
      const lic = License.findByKey(license_key);
      if (lic && lic.status === 'active' && !lic.user_id) {
        keyValid = true;
      } else if (lic && lic.user_id) {
        return res.status(401).json({ success: false, message: 'License key already in use' });
      } else {
        return res.status(401).json({ success: false, message: 'Invalid license key' });
      }
    }

    if (keyValid) {
      User.create(username, password);
      const user = User.findByUsername(username);
      User.updateLicenseKey(user.id, license_key);
      License.assignToUser(license_key, user.id);

      const token = generateToken(user.id);
      const profile = User.getProfile(user.id);

      res.json({
        success: true,
        token,
        user: {
          id: profile.id,
          username: profile.username,
          license: profile.license_key_id,
          product: profile.product,
          status: profile.status,
          created_at: profile.created_at
        }
      });
    } else {
      res.status(401).json({ success: false, message: 'Invalid license key' });
    }
  } catch (err) {
    console.error('Register error:', err);
    res.status(500).json({ success: false, message: 'Internal server error' });
  }
});

app.post('/api/auth/license', async (req, res) => {
  try {
    const { key } = req.body;
    if (!key) return res.status(400).json({ success: false, message: 'License key required' });

    if (process.env.KEYAUTH_OWNERID && process.env.KEYAUTH_OWNERID !== 'your_owner_id_here') {
      const ka = getKeyAuth();
      const result = await ka.license(key);
      if (result.success) {
        return res.json({ success: true, message: 'License key is valid', subscription: result.info });
      }
      return res.status(401).json({ success: false, message: result.message || 'Invalid license key' });
    }

    const lic = License.findByKey(key);
    if (lic && lic.status === 'active') {
      return res.json({ success: true, message: 'License key is valid' });
    }

    License.create(key);
    res.json({ success: true, message: 'License key created and valid (local mode)' });
  } catch (err) {
    console.error('License error:', err);
    res.status(500).json({ success: false, message: 'Internal server error' });
  }
});

app.get('/api/user/profile', authMiddleware, (req, res) => {
  const profile = User.getProfile(req.user.id);
  if (!profile) return res.status(404).json({ success: false, message: 'Profile not found' });

  res.json({
    success: true,
    user: {
      id: profile.id,
      username: profile.username,
      email: profile.email,
      license: profile.license_key_id,
      product: profile.product,
      status: profile.status,
      expires_at: profile.expires_at,
      hwid: profile.hwid,
      created_at: profile.created_at,
      last_login: profile.last_login
    }
  });
});

app.post('/api/user/logout', authMiddleware, (req, res) => {
  res.json({ success: true, message: 'Logged out' });
});

app.get('/api/products', authMiddleware, (req, res) => {
  res.json({
    success: true,
    products: [
      {
        id: 1,
        name: 'HyperX-External-FiveM',
        status: 'Undetected',
        owned: true,
        subscription: 'Lifetime',
        version: '1.0.0-Alpha'
      }
    ]
  });
});

app.listen(PORT, () => {
  console.log(`
  ╔══════════════════════════════════════╗
  ║       HYPERX LOGIN SYSTEM           ║
  ║      Server running on port ${PORT}      ║
  ║   http://localhost:${PORT}              ║
  ╚══════════════════════════════════════╝
  `);
});
