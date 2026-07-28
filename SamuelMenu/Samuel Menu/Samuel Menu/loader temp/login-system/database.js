const path = require('path');
const fs = require('fs');
const bcrypt = require('bcryptjs');

const DATA_DIR = path.join(__dirname, 'data');
fs.mkdirSync(DATA_DIR, { recursive: true });

const DB_PATH = path.join(DATA_DIR, 'database.json');

function load() {
  try { return JSON.parse(fs.readFileSync(DB_PATH, 'utf8')); }
  catch { return { users: [], licenses: [], nextUserId: 1, nextLicenseId: 1 }; }
}

function save(data) {
  fs.writeFileSync(DB_PATH, JSON.stringify(data, null, 2));
}

const db = { _data: load(), _save() { save(this._data); } };

const User = {
  create(username, password, email = null) {
    const hash = bcrypt.hashSync(password, 10);
    const user = {
      id: db._data.nextUserId++,
      username,
      password: hash,
      email,
      license_key: null,
      hwid: null,
      created_at: new Date().toISOString(),
      last_login: null,
      is_banned: false
    };
    db._data.users.push(user);
    db._save();
    return user;
  },

  findByUsername(username) {
    return db._data.users.find(u => u.username === username) || null;
  },

  findById(id) {
    return db._data.users.find(u => u.id === id) || null;
  },

  verifyPassword(user, password) {
    return bcrypt.compareSync(password, user.password);
  },

  updateLicenseKey(userId, licenseKey) {
    const user = db._data.users.find(u => u.id === userId);
    if (user) { user.license_key = licenseKey; db._save(); }
  },

  updateHwid(userId, hwid) {
    const user = db._data.users.find(u => u.id === userId);
    if (user) { user.hwid = hwid; db._save(); }
  },

  updateLastLogin(userId) {
    const user = db._data.users.find(u => u.id === userId);
    if (user) { user.last_login = new Date().toISOString(); db._save(); }
  },

  ban(userId) {
    const user = db._data.users.find(u => u.id === userId);
    if (user) { user.is_banned = true; db._save(); }
  },

  getProfile(userId) {
    const user = db._data.users.find(u => u.id === userId);
    if (!user) return null;
    const lic = db._data.licenses.find(l => l.key === user.license_key);
    return {
      id: user.id,
      username: user.username,
      email: user.email,
      license_key: user.license_key,
      hwid: user.hwid,
      created_at: user.created_at,
      last_login: user.last_login,
      license_key_id: lic ? lic.key : null,
      product: lic ? lic.product : 'HyperX-External-FiveM',
      status: lic ? lic.status : 'inactive',
      expires_at: lic ? lic.expires_at : null
    };
  }
};

const License = {
  create(key, product = 'HyperX-External-FiveM', expiresAt = null) {
    const lic = { key, product, status: 'active', expires_at: expiresAt, created_at: new Date().toISOString() };
    db._data.licenses.push(lic);
    db._save();
    return lic;
  },

  findByKey(key) {
    return db._data.licenses.find(l => l.key === key) || null;
  },

  assignToUser(key, userId) {
    const lic = db._data.licenses.find(l => l.key === key);
    if (lic) { lic.user_id = userId; db._save(); }
  },

  findByUser(userId) {
    const user = db._data.users.find(u => u.id === userId);
    if (!user) return null;
    return db._data.licenses.find(l => l.key === user.license_key) || null;
  }
};

module.exports = { User, License, db };
