const https = require('https');
const querystring = require('querystring');

class KeyAuth {
  constructor(ownerid, appname, secret, version) {
    this.ownerid = ownerid;
    this.appname = appname;
    this.secret = secret;
    this.version = version;
    this.sessionid = null;
    this.apiurl = 'https://keyauth.win/api/1.2/';
  }

  _request(data) {
    return new Promise((resolve, reject) => {
      const postData = querystring.stringify({
        ...data,
        ownerid: this.ownerid,
        appname: this.appname,
        secret: this.secret,
        ver: this.version
      });

      const options = {
        hostname: 'keyauth.win',
        path: '/api/1.2/',
        method: 'POST',
        headers: {
          'Content-Type': 'application/x-www-form-urlencoded',
          'Content-Length': Buffer.byteLength(postData)
        }
      };

      const req = https.request(options, (res) => {
        let body = '';
        res.on('data', chunk => body += chunk);
        res.on('end', () => {
          try {
            resolve(JSON.parse(body));
          } catch {
            reject(new Error('Invalid response from KeyAuth'));
          }
        });
      });

      req.on('error', reject);
      req.write(postData);
      req.end();
    });
  }

  async init() {
    const res = await this._request({ type: 'init' });
    if (res.success) {
      this.sessionid = res.sessionid;
    }
    return res;
  }

  async login(username, password) {
    return this._request({ type: 'login', username, password, sessionid: this.sessionid });
  }

  async register(username, password, key) {
    return this._request({ type: 'register', username, password, key, sessionid: this.sessionid });
  }

  async license(key) {
    return this._request({ type: 'license', key, sessionid: this.sessionid });
  }

  async check() {
    return this._request({ type: 'check', sessionid: this.sessionid });
  }

  async getvar(varname) {
    return this._request({ type: 'getvar', var: varname, sessionid: this.sessionid });
  }

  async setvar(varname, value) {
    return this._request({ type: 'setvar', var: varname, value, sessionid: this.sessionid });
  }

  async fetchStats() {
    return this._request({ type: 'fetchStats', sessionid: this.sessionid });
  }

  async fetchOnline() {
    return this._request({ type: 'fetchOnline', sessionid: this.sessionid });
  }

  async logout() {
    return this._request({ type: 'logout', sessionid: this.sessionid });
  }
}

let keyauthInstance = null;

function getKeyAuth() {
  if (!keyauthInstance) {
    keyauthInstance = new KeyAuth(
      process.env.KEYAUTH_OWNERID,
      process.env.KEYAUTH_APPNAME,
      process.env.KEYAUTH_SECRET,
      process.env.KEYAUTH_VERSION
    );
  }
  return keyauthInstance;
}

module.exports = { KeyAuth, getKeyAuth };
