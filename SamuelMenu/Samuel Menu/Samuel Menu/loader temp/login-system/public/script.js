const API = '/api';

let TOKEN = localStorage.getItem('hyperx_token');
let currentTab = 'login';

const $ = (s) => document.querySelector(s);
const $$ = (s) => document.querySelectorAll(s);

// --- UI Helpers ---
function showMsg(el, text, type) {
  el.textContent = text;
  el.className = 'msg ' + type;
}
function hideMsg(el) {
  el.className = 'msg hidden';
}
function setLoading(btn, loading) {
  btn.classList.toggle('loading', loading);
  btn.disabled = loading;
}

// --- API ---
async function api(path, data, method = 'POST') {
  const headers = { 'Content-Type': 'application/json' };
  if (TOKEN) headers['Authorization'] = 'Bearer ' + TOKEN;
  const res = await fetch(API + path, { method, headers, body: JSON.stringify(data) });
  const json = await res.json();
  if (!res.ok && !json.success) throw new Error(json.message || 'Request failed');
  return json;
}

// --- Tabs ---
$$('.tab').forEach(tab => {
  tab.addEventListener('click', () => {
    $$('.tab').forEach(t => t.classList.remove('active'));
    tab.classList.add('active');
    $$('.form').forEach(f => f.classList.add('hidden'));
    const form = document.getElementById(tab.dataset.tab + 'Form');
    if (form) form.classList.remove('hidden');
    currentTab = tab.dataset.tab;
    // Clear all messages
    $$('.msg').forEach(m => hideMsg(m));
  });
});

// --- Toggle Password ---
$$('.toggle-pass').forEach(btn => {
  btn.addEventListener('click', () => {
    const input = document.getElementById(btn.dataset.target);
    const type = input.type === 'password' ? 'text' : 'password';
    input.type = type;
    btn.querySelector('i').className = type === 'password' ? 'fas fa-eye' : 'fas fa-eye-slash';
  });
});

// --- Login ---
$('#loginBtn').addEventListener('click', async () => {
  const btn = $('#loginBtn');
  const msg = $('#loginMsg');
  const username = $('#loginUser').value.trim();
  const password = $('#loginPass').value;

  if (!username || !password) {
    showMsg(msg, 'Please fill in all fields', 'error');
    return;
  }

  setLoading(btn, true);
  hideMsg(msg);

  try {
    const res = await api('/auth/login', { username, password });
    TOKEN = res.token;
    localStorage.setItem('hyperx_token', TOKEN);
    showMsg(msg, 'Login successful!', 'success');
    setTimeout(showDashboard, 500);
  } catch (err) {
    showMsg(msg, err.message, 'error');
  } finally {
    setLoading(btn, false);
  }
});

// --- Register ---
$('#registerBtn').addEventListener('click', async () => {
  const btn = $('#registerBtn');
  const msg = $('#registerMsg');
  const username = $('#regUser').value.trim();
  const password = $('#regPass').value;
  const key = $('#regKey').value.trim();

  if (!username || !password) {
    showMsg(msg, 'Username and password required', 'error');
    return;
  }
  if (!key) {
    showMsg(msg, 'License key required for registration', 'error');
    return;
  }

  setLoading(btn, true);
  hideMsg(msg);

  try {
    const res = await api('/auth/register', { username, password, license_key: key });
    TOKEN = res.token;
    localStorage.setItem('hyperx_token', TOKEN);
    showMsg(msg, 'Account created!', 'success');
    setTimeout(showDashboard, 500);
  } catch (err) {
    showMsg(msg, err.message, 'error');
  } finally {
    setLoading(btn, false);
  }
});

// --- License Validation ---
$('#licenseBtn').addEventListener('click', async () => {
  const btn = $('#licenseBtn');
  const msg = $('#licenseMsg');
  const key = $('#licenseInput').value.trim();

  if (!key) {
    showMsg(msg, 'Please enter a license key', 'error');
    return;
  }

  setLoading(btn, true);
  hideMsg(msg);

  try {
    const res = await api('/auth/license', { key });
    showMsg(msg, res.message || 'Key is valid!', 'success');
  } catch (err) {
    showMsg(msg, err.message, 'error');
  } finally {
    setLoading(btn, false);
  }
});

// --- Dashboard ---
async function showDashboard() {
  try {
    const res = await api('/user/profile', {}, 'GET');
    const u = res.user;

    $('#dashUsername').textContent = u.username;
    $('#dashLicense').textContent = u.license || 'No license';
    $('#productName').textContent = u.product || 'HyperX-External-FiveM';
    $('#detailSub').textContent = u.status === 'active' ? 'Lifetime' : 'Inactive';
    $('#detailStatus').textContent = u.status === 'active' ? 'Active' : 'Inactive';
    $('#detailStatus').style.color = u.status === 'active' ? '#22c55e' : '#ef4444';
    $('#detailHwid').textContent = u.hwid || '-';
    $('#detailLastLogin').textContent = u.last_login ? new Date(u.last_login).toLocaleString() : '-';

    $('#authScreen').style.display = 'none';
    $('#dashScreen').classList.add('active');
  } catch (err) {
    localStorage.removeItem('hyperx_token');
    TOKEN = null;
    $('#authScreen').style.display = '';
    $('#dashScreen').classList.remove('active');
  }
}

// --- Logout ---
$('#logoutBtn').addEventListener('click', async () => {
  try { await api('/user/logout', {}); } catch {}
  localStorage.removeItem('hyperx_token');
  TOKEN = null;
  $('#authScreen').style.display = '';
  $('#dashScreen').classList.remove('active');
  $$('.msg').forEach(m => hideMsg(m));
});

// --- Inject / Bypass ---
$('#injectBtn').addEventListener('click', () => {
  const btn = $('#injectBtn');
  btn.textContent = 'Injecting...';
  btn.disabled = true;
  setTimeout(() => {
    btn.innerHTML = '<i class="fas fa-check"></i> Injected';
    btn.style.background = 'rgba(34,197,94,0.2)';
    btn.style.color = '#22c55e';
  }, 2000);
});

$('#bypassBtn').addEventListener('click', () => {
  const btn = $('#bypassBtn');
  btn.textContent = 'Bypassing...';
  btn.disabled = true;
  setTimeout(() => {
    btn.innerHTML = '<i class="fas fa-check"></i> Bypassed';
    btn.style.color = '#22c55e';
  }, 2000);
});

// --- Keyboard shortcuts ---
document.addEventListener('keydown', (e) => {
  if (e.key === 'Enter') {
    if (currentTab === 'login') $('#loginBtn').click();
    else if (currentTab === 'register') $('#registerBtn').click();
    else if (currentTab === 'key') $('#licenseBtn').click();
  }
});

// --- Particles ---
const canvas = document.getElementById('particles');
const ctx = canvas.getContext('2d');
let w, h, particles = [];

function resize() {
  w = canvas.width = window.innerWidth;
  h = canvas.height = window.innerHeight;
}
resize();
window.addEventListener('resize', resize);

class Particle {
  constructor() { this.reset(); }
  reset() {
    this.x = Math.random() * w;
    this.y = Math.random() * h;
    this.size = Math.random() * 2 + 0.5;
    this.speedX = (Math.random() - 0.5) * 0.3;
    this.speedY = (Math.random() - 0.5) * 0.3;
    this.opacity = Math.random() * 0.3 + 0.1;
  }
  update() {
    this.x += this.speedX;
    this.y += this.speedY;
    if (this.x < 0 || this.x > w || this.y < 0 || this.y > h) this.reset();
  }
  draw() {
    ctx.beginPath();
    ctx.arc(this.x, this.y, this.size, 0, Math.PI * 2);
    ctx.fillStyle = `rgba(255, 26, 38, ${this.opacity})`;
    ctx.fill();
  }
}

for (let i = 0; i < 80; i++) particles.push(new Particle());

function animate() {
  ctx.clearRect(0, 0, w, h);
  particles.forEach(p => { p.update(); p.draw(); });

  // Draw connections
  for (let i = 0; i < particles.length; i++) {
    for (let j = i + 1; j < particles.length; j++) {
      const dx = particles[i].x - particles[j].x;
      const dy = particles[i].y - particles[j].y;
      const dist = Math.sqrt(dx * dx + dy * dy);
      if (dist < 120) {
        ctx.beginPath();
        ctx.moveTo(particles[i].x, particles[i].y);
        ctx.lineTo(particles[j].x, particles[j].y);
        ctx.strokeStyle = `rgba(255, 26, 38, ${0.04 * (1 - dist / 120)})`;
        ctx.lineWidth = 0.5;
        ctx.stroke();
      }
    }
  }
  requestAnimationFrame(animate);
}
animate();

// --- Auto-login check ---
(async () => {
  if (TOKEN) {
    try {
      const res = await api('/user/profile', {}, 'GET');
      if (res.success) { showDashboard(); return; }
    } catch {}
    localStorage.removeItem('hyperx_token');
    TOKEN = null;
  }
})();
