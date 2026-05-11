#ifndef HTML_H
#define HTML_H

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>SandSaaaand!!! — Control Dashboard</title>
<!-- Fonts -->
<link href="https://fonts.googleapis.com/css2?family=DM+Mono:wght@400;500&family=Syne:wght@400;600;700;800&family=DM+Sans:wght@300;400;500&display=swap" rel="stylesheet">

<!-- Firebase SDK -->
<script src="https://www.gstatic.com/firebasejs/9.22.2/firebase-app-compat.js"></script>
<script src="https://www.gstatic.com/firebasejs/9.22.2/firebase-database-compat.js"></script>

<style>
  :root {
    --bg: #0a0d12;
    --surface: #111520;
    --surface2: #161c2a;
    --border: rgba(255,255,255,0.07);
    --border2: rgba(255,255,255,0.12);
    --accent: #00e5a0;
    --accent2: #0ff;
    --amber: #ffb224;
    --red: #ff4d4d;
    --blue: #4da6ff;
    --purple: #a78bfa;
    --text: #e8edf5;
    --muted: #5a6580;
    --muted2: #8892aa;
    --mono: 'DM Mono', monospace;
    --sans: 'DM Sans', sans-serif;
    --display: 'Syne', sans-serif;
  }

  * { margin:0; padding:0; box-sizing:border-box; }
  html { font-size:14px; }
  body {
    background: var(--bg);
    color: var(--text);
    font-family: var(--sans);
    min-height: 100vh;
    overflow-x: hidden;
  }

  /* BACKGROUND GRID */
  body::before {
    content:'';
    position:fixed; inset:0;
    background-image:
      linear-gradient(rgba(0,229,160,0.025) 1px, transparent 1px),
      linear-gradient(90deg, rgba(0,229,160,0.025) 1px, transparent 1px);
    background-size: 40px 40px;
    pointer-events:none; z-index:0;
  }

  /* NAV */
  nav {
    position:fixed; top:0; left:0; right:0; z-index:100;
    background: rgba(10,13,18,0.92);
    backdrop-filter: blur(20px);
    border-bottom: 1px solid var(--border);
    height: 60px;
    display:flex; align-items:center; justify-content:space-between;
    padding: 0 24px;
  }
  .nav-logo {
    display:flex; align-items:center; gap:10px;
  }
  .nav-logo .logo-icon {
    width:32px; height:32px; border-radius:8px;
    background: linear-gradient(135deg, var(--accent), #00b37a);
    display:flex; align-items:center; justify-content:center;
    font-size:16px;
  }
  .nav-logo span {
    font-family: var(--display);
    font-weight:700; font-size:18px;
    letter-spacing:-0.5px;
  }
  .nav-logo small {
    font-family: var(--mono);
    font-size:10px; color:var(--muted);
    display:block; margin-top:-2px;
  }
  .nav-tabs {
    display:flex; gap:4px;
  }
  .nav-tab {
    padding:6px 14px; border-radius:6px;
    font-size:13px; font-weight:500;
    cursor:pointer; transition:all 0.2s;
    color:var(--muted2);
    border:1px solid transparent;
    background:none;
    font-family: var(--sans);
  }
  .nav-tab:hover { color:var(--text); background:var(--surface2); }
  .nav-tab.active {
    color:var(--accent);
    background: rgba(0,229,160,0.08);
    border-color: rgba(0,229,160,0.2);
  }
  .nav-status {
    display:flex; align-items:center; gap:8px;
    font-family: var(--mono); font-size:11px; color:var(--muted2);
  }
  .status-dot {
    width:8px; height:8px; border-radius:50%;
    background:var(--accent);
    box-shadow:0 0 8px var(--accent);
    animation: pulse 2s ease-in-out infinite;
  }
  .status-dot.offline { background:var(--red); box-shadow:0 0 8px var(--red); animation:none; }
  @keyframes pulse { 0%,100%{opacity:1} 50%{opacity:0.4} }

  /* LAYOUT */
  .page { display:none; padding:80px 24px 40px; max-width:1280px; margin:0 auto; position:relative; z-index:1; }
  .page.active { display:block; }

  /* PAGE HEADERS */
  .page-header { margin-bottom:28px; }
  .page-header h1 { font-family:var(--display); font-size:26px; font-weight:800; letter-spacing:-0.5px; }
  .page-header p { color:var(--muted2); font-size:13px; margin-top:4px; }

  /* GRID */
  .grid { display:grid; gap:16px; }
  .grid-4 { grid-template-columns: repeat(4, 1fr); }
  .grid-3 { grid-template-columns: repeat(3, 1fr); }
  .grid-2 { grid-template-columns: repeat(2, 1fr); }
  .grid-auto { grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); }

  /* CARDS */
  .card {
    background: var(--surface);
    border: 1px solid var(--border);
    border-radius:16px;
    padding:20px;
    position:relative;
    overflow:hidden;
  }
  .card::before {
    content:'';
    position:absolute; top:0; left:0; right:0; height:1px;
    background: linear-gradient(90deg, transparent, rgba(255,255,255,0.06), transparent);
  }
  .card-accent-green { border-top: 2px solid var(--accent); }
  .card-accent-amber { border-top: 2px solid var(--amber); }
  .card-accent-blue  { border-top: 2px solid var(--blue); }
  .card-accent-red   { border-top: 2px solid var(--red); }
  .card-accent-purple{ border-top: 2px solid var(--purple); }

  .card-label {
    font-family:var(--mono); font-size:10px; font-weight:500;
    letter-spacing:1.5px; text-transform:uppercase;
    color:var(--muted); margin-bottom:12px;
  }
  .card-value {
    font-family:var(--display); font-size:36px; font-weight:800;
    line-height:1; letter-spacing:-1px;
  }
  .card-value.green  { color:var(--accent); }
  .card-value.amber  { color:var(--amber); }
  .card-value.blue   { color:var(--blue); }
  .card-value.red    { color:var(--red); }
  .card-value.purple { color:var(--purple); }
  .card-sub {
    font-size:12px; color:var(--muted2); margin-top:6px;
    font-family:var(--mono);
  }
  .card-icon {
    position:absolute; top:16px; right:16px;
    font-size:22px; opacity:0.15;
  }

  /* STAT ROW */
  .stat-row {
    display:flex; justify-content:space-between;
    padding:10px 0; border-bottom:1px solid var(--border);
    align-items:center;
  }
  .stat-row:last-child { border-bottom:none; padding-bottom:0; }
  .stat-row:first-child { padding-top:0; }
  .stat-key { font-size:12px; color:var(--muted2); font-family:var(--mono); }
  .stat-val { font-size:13px; font-weight:500; font-family:var(--mono); }

  /* PROGRESS BAR */
  .prog-wrap { margin-top:14px; }
  .prog-header { display:flex; justify-content:space-between; margin-bottom:6px; }
  .prog-label { font-size:12px; color:var(--muted2); }
  .prog-pct { font-family:var(--mono); font-size:12px; font-weight:500; }
  .prog-bar {
    height:6px; border-radius:4px;
    background: var(--surface2);
    overflow:hidden;
  }
  .prog-fill {
    height:100%; border-radius:4px;
    transition: width 0.8s cubic-bezier(0.4,0,0.2,1);
  }
  .prog-fill.green  { background: linear-gradient(90deg, #00b37a, var(--accent)); }
  .prog-fill.amber  { background: linear-gradient(90deg, #cc8800, var(--amber)); }
  .prog-fill.blue   { background: linear-gradient(90deg, #2080d0, var(--blue)); }
  .prog-fill.red    { background: linear-gradient(90deg, #cc2222, var(--red)); }

  /* RING GAUGE */
  .ring-wrap { display:flex; flex-direction:column; align-items:center; padding:10px 0; }
  .ring-svg { width:140px; height:140px; }
  .ring-center { text-align:center; margin-top:-8px; }
  .ring-center .big { font-family:var(--display); font-size:28px; font-weight:800; }
  .ring-center .small { font-size:11px; color:var(--muted2); font-family:var(--mono); }

  /* TIMELINE / LOG */
  .log-entry {
    display:flex; gap:12px; padding:10px 0;
    border-bottom:1px solid var(--border);
    align-items:flex-start;
  }
  .log-entry:last-child { border-bottom:none; }
  .log-dot {
    width:8px; height:8px; border-radius:50%; flex-shrink:0; margin-top:4px;
  }
  .log-time { font-family:var(--mono); font-size:11px; color:var(--muted); white-space:nowrap; }
  .log-msg  { font-size:12px; color:var(--muted2); }
  .log-badge {
    font-family:var(--mono); font-size:10px; padding:2px 7px; border-radius:4px;
    font-weight:500; white-space:nowrap; margin-left:auto;
  }
  .badge-green  { background:rgba(0,229,160,0.12); color:var(--accent); }
  .badge-amber  { background:rgba(255,178,36,0.12); color:var(--amber); }
  .badge-red    { background:rgba(255,77,77,0.12);  color:var(--red); }
  .badge-blue   { background:rgba(77,166,255,0.12); color:var(--blue); }
  .badge-purple { background:rgba(167,139,250,0.12);color:var(--purple); }

  /* DIVIDER */
  .section-label {
    font-family:var(--mono); font-size:10px; letter-spacing:2px;
    text-transform:uppercase; color:var(--muted);
    margin: 20px 0 12px;
    display:flex; align-items:center; gap:8px;
  }
  .section-label::after {
    content:''; flex:1; height:1px; background:var(--border);
  }

  /* CONTROL BUTTON */
  .ctrl-btn {
    width:100%; padding:12px;
    border-radius:10px; border:1px solid var(--border2);
    background:var(--surface2); color:var(--text);
    font-family:var(--mono); font-size:12px; cursor:pointer;
    transition:all 0.2s; letter-spacing:0.5px;
  }
  .ctrl-btn:hover { background:var(--surface); border-color:var(--accent); color:var(--accent); }
  .ctrl-btn.danger:hover { border-color:var(--red); color:var(--red); }

  /* TOGGLE SWITCH */
  .toggle-wrap {
    display:flex; align-items:center; justify-content:space-between;
    padding:12px 0; border-bottom:1px solid var(--border);
  }
  .toggle-wrap:last-child { border-bottom:none; }
  .toggle-label { font-size:13px; }
  .toggle-sub { font-size:11px; color:var(--muted2); margin-top:2px; }
  .toggle {
    position:relative; width:44px; height:24px;
    flex-shrink:0;
  }
  .toggle input { opacity:0; width:0; height:0; position:absolute; }
  .toggle-track {
    position:absolute; inset:0;
    background:var(--surface2); border:1px solid var(--border2);
    border-radius:12px; cursor:pointer; transition:all 0.2s;
  }
  .toggle-thumb {
    position:absolute; top:3px; left:3px;
    width:16px; height:16px; border-radius:50%;
    background:var(--muted); transition:all 0.2s;
  }
  .toggle input:checked + .toggle-track { background:rgba(0,229,160,0.15); border-color:var(--accent); }
  .toggle input:checked + .toggle-track + .toggle-thumb { transform:translateX(20px); background:var(--accent); box-shadow:0 0 8px var(--accent); }

  /* CHART MINI BARS */
  .mini-chart { display:flex; align-items:flex-end; gap:3px; height:48px; margin-top:12px; }
  .mini-bar { flex:1; border-radius:3px 3px 0 0; transition:height 0.5s ease; opacity:0.7; }
  .mini-bar:hover { opacity:1; }

  /* ALERT BANNER */
  .alert {
    padding:12px 16px; border-radius:10px; font-size:12px;
    display:flex; align-items:center; gap:10px; margin-bottom:8px;
    font-family:var(--mono);
  }
  .alert-warn { background:rgba(255,178,36,0.08); border:1px solid rgba(255,178,36,0.2); color:var(--amber); }
  .alert-ok   { background:rgba(0,229,160,0.06); border:1px solid rgba(0,229,160,0.15); color:var(--accent); }
  .alert-err  { background:rgba(255,77,77,0.08); border:1px solid rgba(255,77,77,0.2); color:var(--red); }

  /* FIREBASE CONFIG MODAL */
  .modal-overlay {
    position:fixed; inset:0; z-index:200;
    background:rgba(0,0,0,0.85);
    display:flex; align-items:center; justify-content:center;
  }
  .modal {
    background:var(--surface); border:1px solid var(--border2);
    border-radius:20px; padding:32px; width:500px; max-width:95vw;
  }
  .modal h2 { font-family:var(--display); font-size:20px; font-weight:700; margin-bottom:4px; }
  .modal p { font-size:12px; color:var(--muted2); margin-bottom:20px; font-family:var(--mono); }
  .field { margin-bottom:12px; }
  .field label { display:block; font-size:11px; color:var(--muted2); font-family:var(--mono); margin-bottom:5px; letter-spacing:0.5px; }
  .field input {
    width:100%; padding:10px 12px; border-radius:8px;
    background:var(--surface2); border:1px solid var(--border2);
    color:var(--text); font-family:var(--mono); font-size:12px; outline:none;
    transition:border-color 0.2s;
  }
  .field input:focus { border-color:var(--accent); }
  .btn-primary {
    width:100%; padding:12px; border-radius:10px;
    background:var(--accent); color:#000; border:none;
    font-family:var(--display); font-size:14px; font-weight:700;
    cursor:pointer; margin-top:8px; transition:all 0.2s;
  }
  .btn-primary:hover { background:#00ffb8; }
  .btn-demo {
    width:100%; padding:10px; border-radius:10px; margin-top:8px;
    background:transparent; color:var(--muted2); border:1px solid var(--border);
    font-family:var(--mono); font-size:12px; cursor:pointer; transition:all 0.2s;
  }
  .btn-demo:hover { border-color:var(--border2); color:var(--text); }

  /* MACHINE STATUS BANNER */
  .machine-banner {
    background: var(--surface);
    border:1px solid var(--border);
    border-radius:16px; padding:20px 24px;
    display:flex; align-items:center; justify-content:space-between;
    margin-bottom:16px;
  }
  .machine-name { font-family:var(--display); font-size:22px; font-weight:800; }
  .machine-id { font-family:var(--mono); font-size:11px; color:var(--muted); margin-top:2px; }
  .machine-mode {
    padding:6px 16px; border-radius:8px;
    font-family:var(--mono); font-size:12px; font-weight:500;
  }
  .mode-cleaning { background:rgba(0,229,160,0.1); color:var(--accent); border:1px solid rgba(0,229,160,0.25); }
  .mode-charging { background:rgba(255,178,36,0.1); color:var(--amber); border:1px solid rgba(255,178,36,0.25); }
  .mode-idle     { background:rgba(90,101,128,0.2); color:var(--muted2); border:1px solid var(--border); }
  .mode-error    { background:rgba(255,77,77,0.1); color:var(--red); border:1px solid rgba(255,77,77,0.25); }

  /* RESPONSIVE */
  @media (max-width:900px) {
    .grid-4 { grid-template-columns: repeat(2,1fr); }
    .grid-3 { grid-template-columns: repeat(2,1fr); }
  }
  @media (max-width:600px) {
    .grid-4,.grid-3,.grid-2 { grid-template-columns: 1fr; }
    nav { padding:0 14px; }
    .page { padding:72px 14px 32px; }
    .nav-tabs { display:none; }
    .machine-banner { flex-direction:column; gap:12px; align-items:flex-start; }
  }
</style>
</head>
<body>

<!-- FIREBASE CONFIG MODAL -->
<div class="modal-overlay" id="configModal">
  <div class="modal">
    <h2>🔥 Firebase Setup</h2>
    <p>Enter your Firebase project credentials to connect the dashboard.</p>
    <div class="field"><label>API KEY</label><input type="text" id="fb-apiKey" placeholder="AIzaSy..."></div>
    <div class="field"><label>AUTH DOMAIN</label><input type="text" id="fb-authDomain" placeholder="your-app.firebaseapp.com"></div>
    <div class="field"><label>DATABASE URL</label><input type="text" id="fb-dbUrl" placeholder="https://your-app-default-rtdb.firebaseio.com"></div>
    <div class="field"><label>PROJECT ID</label><input type="text" id="fb-projectId" placeholder="your-app"></div>
    <button class="btn-primary" onclick="connectFirebase()">Connect to Firebase</button>
    <button class="btn-demo" onclick="useDemoMode()">Continue with Demo Data (no Firebase)</button>
  </div>
</div>

<!-- NAV -->
<nav>
  <div class="nav-logo">
    <div class="logo-icon">🫩</div>
    <div>
      <span>SandSaaaand!!!</span>
      <small>DAZZZBOARD v1.0</small>
    </div>
  </div>
  <div class="nav-tabs">
    <button class="nav-tab active" onclick="showPage('overview')">Overview</button>
    <button class="nav-tab" onclick="showPage('charging')">Charging</button>
    <button class="nav-tab" onclick="showPage('usage')">Usage</button>
    <button class="nav-tab" onclick="showPage('sensors')">Sensors</button>
    <button class="nav-tab" onclick="showPage('logs')">Logs</button>
    <button class="nav-tab" onclick="showPage('settings')">Settings</button>
  </div>
  <div class="nav-status">
    <div class="status-dot" id="connDot"></div>
    <span id="connLabel">CONNECTING...</span>
  </div>
</nav>

<!-- ===== PAGE: OVERVIEW ===== -->
<div class="page active" id="page-overview">
  <div class="page-header">
    <h1>Overview</h1>
    <p>Real-time machine status — <span id="lastUpdate" style="font-family:var(--mono)">--</span></p>
  </div>

  <!-- Machine Banner -->
  <div class="machine-banner">
    <div>
      <div class="machine-name">Sand Cleaning Machine</div>
      <div class="machine-id">ID: ESP32-SCM-001 &nbsp;|&nbsp; Firmware: 1.0.3</div>
    </div>
    <div style="display:flex;gap:10px;align-items:center">
      <div class="machine-mode mode-cleaning" id="machineMode">⚡ CLEANING</div>
      <div id="uptime-badge" style="font-family:var(--mono);font-size:11px;color:var(--muted2)">UP: 00:00:00</div>
    </div>
  </div>

  <!-- KPI Row -->
  <div class="grid grid-4" style="margin-bottom:16px">
    <div class="card card-accent-green">
      <div class="card-icon">🔋</div>
      <div class="card-label">Battery Level</div>
      <div class="card-value green" id="ov-battery">--</div>
      <div class="card-sub" id="ov-battery-sub">-- remaining</div>
      <div class="prog-wrap">
        <div class="prog-bar"><div class="prog-fill green" id="ov-battery-bar" style="width:0%"></div></div>
      </div>
    </div>
    <div class="card card-accent-amber">
      <div class="card-icon">⚡</div>
      <div class="card-label">Power Input</div>
      <div class="card-value amber" id="ov-power">--</div>
      <div class="card-sub" id="ov-power-sub">Not charging</div>
    </div>
    <div class="card card-accent-blue">
      <div class="card-icon">🕐</div>
      <div class="card-label">Session Time</div>
      <div class="card-value blue" id="ov-session">--</div>
      <div class="card-sub" id="ov-session-sub">current session</div>
    </div>
    <div class="card card-accent-purple">
      <div class="card-icon">📍</div>
      <div class="card-label">Area Cleaned</div>
      <div class="card-value purple" id="ov-area">--</div>
      <div class="card-sub" id="ov-area-sub">today</div>
    </div>
  </div>

  <!-- Row 2 -->
  <div class="grid grid-3">
    <!-- Health -->
    <div class="card">
      <div class="card-label">System Health</div>
      <div class="stat-row">
        <span class="stat-key">CPU Temp</span>
        <span class="stat-val" id="ov-cputemp" style="color:var(--accent)">--°C</span>
      </div>
      <div class="stat-row">
        <span class="stat-key">Battery Temp</span>
        <span class="stat-val" id="ov-battemp">--°C</span>
      </div>
      <div class="stat-row">
        <span class="stat-key">Motor Load</span>
        <span class="stat-val" id="ov-motorload">--%</span>
      </div>
      <div class="stat-row">
        <span class="stat-key">WiFi Signal</span>
        <span class="stat-val" id="ov-wifi">-- dBm</span>
      </div>
      <div class="stat-row">
        <span class="stat-key">Free Heap</span>
        <span class="stat-val" id="ov-heap">-- KB</span>
      </div>
    </div>

    <!-- Today Summary -->
    <div class="card">
      <div class="card-label">Today's Summary</div>
      <div class="stat-row">
        <span class="stat-key">Cleaning Cycles</span>
        <span class="stat-val" id="ov-cycles">--</span>
      </div>
      <div class="stat-row">
        <span class="stat-key">Total Run Time</span>
        <span class="stat-val" id="ov-runtime">--</span>
      </div>
      <div class="stat-row">
        <span class="stat-key">Charge Sessions</span>
        <span class="stat-val" id="ov-chargesessions">--</span>
      </div>
      <div class="stat-row">
        <span class="stat-key">Debris Collected</span>
        <span class="stat-val" id="ov-debris">-- g</span>
      </div>
      <div class="stat-row">
        <span class="stat-key">Distance Travelled</span>
        <span class="stat-val" id="ov-distance">-- m</span>
      </div>
    </div>

    <!-- Alerts -->
    <div class="card">
      <div class="card-label">Active Alerts</div>
      <div id="alertsContainer">
        <div class="alert alert-ok">✓ All systems nominal</div>
      </div>
    </div>
  </div>
</div>

<!-- ===== PAGE: CHARGING ===== -->
<div class="page" id="page-charging">
  <div class="page-header">
    <h1>Charging</h1>
    <p>Battery management and charging analytics</p>
  </div>

  <div class="grid grid-4" style="margin-bottom:16px">
    <div class="card card-accent-amber">
      <div class="card-icon">⚡</div>
      <div class="card-label">Input Power</div>
      <div class="card-value amber" id="ch-power">--</div>
      <div class="card-sub" id="ch-power-sub">0V / 0A</div>
    </div>
    <div class="card card-accent-green">
      <div class="card-icon">🔋</div>
      <div class="card-label">Charge Level</div>
      <div class="card-value green" id="ch-level">--</div>
      <div class="card-sub" id="ch-level-sub">-- mAh remaining</div>
    </div>
    <div class="card card-accent-blue">
      <div class="card-icon">⏱</div>
      <div class="card-label">Time to Full</div>
      <div class="card-value blue" id="ch-tofull">--</div>
      <div class="card-sub" id="ch-tofull-sub">estimated</div>
    </div>
    <div class="card card-accent-purple">
      <div class="card-icon">♻</div>
      <div class="card-label">Charge Cycles</div>
      <div class="card-value purple" id="ch-cycles">--</div>
      <div class="card-sub">total lifetime</div>
    </div>
  </div>

  <div class="grid grid-2">
    <!-- Charging Details -->
    <div class="card">
      <div class="card-label">Charging Session</div>
      <div class="stat-row"><span class="stat-key">Status</span><span class="stat-val" id="ch-status" style="color:var(--amber)">--</span></div>
      <div class="stat-row"><span class="stat-key">Voltage</span><span class="stat-val" id="ch-voltage">-- V</span></div>
      <div class="stat-row"><span class="stat-key">Current</span><span class="stat-val" id="ch-current">-- A</span></div>
      <div class="stat-row"><span class="stat-key">Session Started</span><span class="stat-val" id="ch-start">--</span></div>
      <div class="stat-row"><span class="stat-key">Session Duration</span><span class="stat-val" id="ch-duration">--</span></div>
      <div class="stat-row"><span class="stat-key">Energy Added</span><span class="stat-val" id="ch-energy">-- Wh</span></div>
      <div class="stat-row"><span class="stat-key">Charge Rate</span><span class="stat-val" id="ch-rate">--C</span></div>
    </div>

    <!-- Daily Stats -->
    <div class="card">
      <div class="card-label">Daily Charging Stats</div>
      <div class="stat-row"><span class="stat-key">Sessions Today</span><span class="stat-val" id="ch-today-sessions">--</span></div>
      <div class="stat-row"><span class="stat-key">Total Charge Time</span><span class="stat-val" id="ch-today-time">--</span></div>
      <div class="stat-row"><span class="stat-key">Energy Consumed</span><span class="stat-val" id="ch-today-energy">-- Wh</span></div>
      <div class="stat-row"><span class="stat-key">Avg Charge Duration</span><span class="stat-val" id="ch-avg-dur">--</span></div>
      <div class="stat-row"><span class="stat-key">First Charge</span><span class="stat-val" id="ch-first">--</span></div>
      <div class="stat-row"><span class="stat-key">Last Charge</span><span class="stat-val" id="ch-last">--</span></div>
      <div class="stat-row"><span class="stat-key">Battery Health</span><span class="stat-val" id="ch-health" style="color:var(--accent)">--%</span></div>
    </div>
  </div>

  <div class="section-label">Weekly Charging Time (hours/day)</div>
  <div class="card">
    <div style="display:flex;gap:4px;align-items:flex-end;height:80px" id="ch-weekly-chart">
      <!-- bars generated by JS -->
    </div>
    <div style="display:flex;gap:4px;margin-top:6px" id="ch-weekly-labels"></div>
  </div>
</div>

<!-- ===== PAGE: USAGE ===== -->
<div class="page" id="page-usage">
  <div class="page-header">
    <h1>Usage</h1>
    <p>Operation analytics and cleaning performance</p>
  </div>

  <div class="grid grid-4" style="margin-bottom:16px">
    <div class="card card-accent-green">
      <div class="card-icon">🕐</div>
      <div class="card-label">Total Usage</div>
      <div class="card-value green" id="us-total">--</div>
      <div class="card-sub">all time</div>
    </div>
    <div class="card card-accent-blue">
      <div class="card-icon">📊</div>
      <div class="card-label">Battery Used</div>
      <div class="card-value blue" id="us-batused">--%</div>
      <div class="card-sub" id="us-batused-sub">this session</div>
    </div>
    <div class="card card-accent-amber">
      <div class="card-icon">⏱</div>
      <div class="card-label">Session Length</div>
      <div class="card-value amber" id="us-session">--</div>
      <div class="card-sub">current session</div>
    </div>
    <div class="card card-accent-purple">
      <div class="card-icon">📈</div>
      <div class="card-label">Efficiency</div>
      <div class="card-value purple" id="us-efficiency">--%</div>
      <div class="card-sub">m² per Wh</div>
    </div>
  </div>

  <div class="grid grid-3">
    <!-- Battery Usage Ring -->
    <div class="card">
      <div class="card-label">Battery Discharge</div>
      <div class="ring-wrap">
        <svg class="ring-svg" viewBox="0 0 140 140">
          <circle cx="70" cy="70" r="56" fill="none" stroke="rgba(255,255,255,0.06)" stroke-width="10"/>
          <circle cx="70" cy="70" r="56" fill="none" stroke="#4da6ff" stroke-width="10"
            stroke-linecap="round"
            stroke-dasharray="352" id="usRingFill"
            stroke-dashoffset="352"
            transform="rotate(-90 70 70)"
            style="transition:stroke-dashoffset 1s ease"/>
        </svg>
        <div class="ring-center">
          <div class="big blue" id="us-ring-val">0%</div>
          <div class="small">used this session</div>
        </div>
      </div>
    </div>

    <!-- Usage Stats -->
    <div class="card">
      <div class="card-label">Session Details</div>
      <div class="stat-row"><span class="stat-key">Start Time</span><span class="stat-val" id="us-starttime">--</span></div>
      <div class="stat-row"><span class="stat-key">Current Duration</span><span class="stat-val" id="us-currdur">--</span></div>
      <div class="stat-row"><span class="stat-key">Battery Start</span><span class="stat-val" id="us-batstart">--%</span></div>
      <div class="stat-row"><span class="stat-key">Battery Now</span><span class="stat-val" id="us-batnow">--%</span></div>
      <div class="stat-row"><span class="stat-key">mAh Consumed</span><span class="stat-val" id="us-mahused">-- mAh</span></div>
      <div class="stat-row"><span class="stat-key">Avg Current Draw</span><span class="stat-val" id="us-avgcurrent">-- A</span></div>
    </div>

    <!-- Lifetime Stats -->
    <div class="card">
      <div class="card-label">Lifetime Stats</div>
      <div class="stat-row"><span class="stat-key">Total Sessions</span><span class="stat-val" id="us-totalsessions">--</span></div>
      <div class="stat-row"><span class="stat-key">Total Hours</span><span class="stat-val" id="us-totalhours">--</span></div>
      <div class="stat-row"><span class="stat-key">Total Distance</span><span class="stat-val" id="us-totaldist">-- km</span></div>
      <div class="stat-row"><span class="stat-key">Total Area</span><span class="stat-val" id="us-totalarea">-- m²</span></div>
      <div class="stat-row"><span class="stat-key">Avg Session</span><span class="stat-val" id="us-avgsession">--</span></div>
      <div class="stat-row"><span class="stat-key">Longest Session</span><span class="stat-val" id="us-longsession">--</span></div>
    </div>
  </div>

  <div class="section-label">Daily Usage (hours per day, last 7 days)</div>
  <div class="card">
    <div style="display:flex;gap:4px;align-items:flex-end;height:80px" id="us-weekly-chart"></div>
    <div style="display:flex;gap:4px;margin-top:6px" id="us-weekly-labels"></div>
  </div>
</div>

<!-- ===== PAGE: SENSORS ===== -->
<div class="page" id="page-sensors">
  <div class="page-header">
    <h1>Sensors</h1>
    <p>Live environmental and machine sensor readings</p>
  </div>

  <div class="grid grid-4" style="margin-bottom:16px">
    <div class="card card-accent-blue">
      <div class="card-icon">🌡</div>
      <div class="card-label">Ambient Temp</div>
      <div class="card-value blue" id="sn-airtemp">--°C</div>
      <div class="card-sub">outdoor air</div>
    </div>
    <div class="card card-accent-amber">
      <div class="card-icon">💧</div>
      <div class="card-label">Humidity</div>
      <div class="card-value amber" id="sn-humidity">--%</div>
      <div class="card-sub">relative humidity</div>
    </div>
    <div class="card card-accent-green">
      <div class="card-icon">🏖</div>
      <div class="card-label">Sand Moisture</div>
      <div class="card-value green" id="sn-sandmoist">--%</div>
      <div class="card-sub">capacitive sensor</div>
    </div>
    <div class="card card-accent-red">
      <div class="card-icon">🔊</div>
      <div class="card-label">Vibration</div>
      <div class="card-value red" id="sn-vibration">-- G</div>
      <div class="card-sub">IMU accelerometer</div>
    </div>
  </div>

  <div class="grid grid-3">
    <div class="card">
      <div class="card-label">Motor Sensors</div>
      <div class="stat-row"><span class="stat-key">Left Motor RPM</span><span class="stat-val" id="sn-lrpm">--</span></div>
      <div class="stat-row"><span class="stat-key">Right Motor RPM</span><span class="stat-val" id="sn-rrpm">--</span></div>
      <div class="stat-row"><span class="stat-key">Brush RPM</span><span class="stat-val" id="sn-brpm">--</span></div>
      <div class="stat-row"><span class="stat-key">Motor L Temp</span><span class="stat-val" id="sn-ltemp">--°C</span></div>
      <div class="stat-row"><span class="stat-key">Motor R Temp</span><span class="stat-val" id="sn-rtemp">--°C</span></div>
    </div>
    <div class="card">
      <div class="card-label">Distance Sensors (cm)</div>
      <div class="stat-row"><span class="stat-key">Front Obstacle</span><span class="stat-val" id="sn-front">-- cm</span></div>
      <div class="stat-row"><span class="stat-key">Rear Obstacle</span><span class="stat-val" id="sn-rear">-- cm</span></div>
      <div class="stat-row"><span class="stat-key">Left Side</span><span class="stat-val" id="sn-left">-- cm</span></div>
      <div class="stat-row"><span class="stat-key">Right Side</span><span class="stat-val" id="sn-right">-- cm</span></div>
      <div class="stat-row"><span class="stat-key">Cliff Left</span><span class="stat-val" id="sn-cliffl" style="color:var(--accent)">SAFE</span></div>
      <div class="stat-row"><span class="stat-key">Cliff Right</span><span class="stat-val" id="sn-cliffr" style="color:var(--accent)">SAFE</span></div>
    </div>
    <div class="card">
      <div class="card-label">Collection System</div>
      <div class="stat-row"><span class="stat-key">Bin Fill Level</span><span class="stat-val" id="sn-binfill">--%</span></div>
      <div class="stat-row"><span class="stat-key">Bin Weight</span><span class="stat-val" id="sn-binwt">-- g</span></div>
      <div class="stat-row"><span class="stat-key">Vacuum Pressure</span><span class="stat-val" id="sn-vacuum">-- Pa</span></div>
      <div class="stat-row"><span class="stat-key">Filter Status</span><span class="stat-val" id="sn-filter" style="color:var(--accent)">CLEAN</span></div>
      <div class="stat-row"><span class="stat-key">GPS Lat</span><span class="stat-val" id="sn-lat" style="font-size:11px">--</span></div>
      <div class="stat-row"><span class="stat-key">GPS Lon</span><span class="stat-val" id="sn-lon" style="font-size:11px">--</span></div>
    </div>
  </div>
</div>

<!-- ===== PAGE: LOGS ===== -->
<div class="page" id="page-logs">
  <div class="page-header">
    <h1>Event Logs</h1>
    <p>System events, errors, and activity history</p>
  </div>
  <div class="card">
    <div id="logContainer">
      <div class="log-entry">
        <div class="log-dot" style="background:var(--muted)"></div>
        <div>
          <div class="log-time">--:--:--</div>
          <div class="log-msg">Waiting for device data...</div>
        </div>
        <span class="log-badge badge-blue">INFO</span>
      </div>
    </div>
  </div>
</div>

<!-- ===== PAGE: SETTINGS ===== -->
<div class="page" id="page-settings">
  <div class="page-header">
    <h1>Settings</h1>
    <p>Machine configuration and remote controls</p>
  </div>

  <div class="grid grid-2">
    <div class="card">
      <div class="card-label">Machine Controls</div>
      <div style="display:grid;gap:8px;margin-top:4px">
        <button class="ctrl-btn" onclick="sendCmd('start')">▶ START CLEANING</button>
        <button class="ctrl-btn" onclick="sendCmd('stop')">⏹ STOP / PARK</button>
        <button class="ctrl-btn" onclick="sendCmd('return_to_charge')">🔋 RETURN TO CHARGER</button>
        <button class="ctrl-btn" onclick="sendCmd('calibrate')">⚙ CALIBRATE SENSORS</button>
        <button class="ctrl-btn danger" onclick="sendCmd('emergency_stop')">⛔ EMERGENCY STOP</button>
      </div>
    </div>

    <div class="card">
      <div class="card-label">Feature Toggles</div>
      <div class="toggle-wrap">
        <div><div class="toggle-label">Auto-Return on Low Battery</div><div class="toggle-sub">Return to charger below 20%</div></div>
        <label class="toggle"><input type="checkbox" checked onchange="setSetting('auto_return', this.checked)"><div class="toggle-track"></div><div class="toggle-thumb"></div></label>
      </div>
      <div class="toggle-wrap">
        <div><div class="toggle-label">Obstacle Avoidance</div><div class="toggle-sub">Ultrasonic sensors active</div></div>
        <label class="toggle"><input type="checkbox" checked onchange="setSetting('obstacle_avoid', this.checked)"><div class="toggle-track"></div><div class="toggle-thumb"></div></label>
      </div>
      <div class="toggle-wrap">
        <div><div class="toggle-label">Night Mode</div><div class="toggle-sub">Run during off-peak hours</div></div>
        <label class="toggle"><input type="checkbox" onchange="setSetting('night_mode', this.checked)"><div class="toggle-track"></div><div class="toggle-thumb"></div></label>
      </div>
      <div class="toggle-wrap">
        <div><div class="toggle-label">Turbo Cleaning</div><div class="toggle-sub">Higher RPM, more power draw</div></div>
        <label class="toggle"><input type="checkbox" onchange="setSetting('turbo', this.checked)"><div class="toggle-track"></div><div class="toggle-thumb"></div></label>
      </div>
    </div>

    <div class="card">
      <div class="card-label">Thresholds</div>
      <div class="stat-row"><span class="stat-key">Low Battery Alert</span><span class="stat-val">20%</span></div>
      <div class="stat-row"><span class="stat-key">Bin Full Alert</span><span class="stat-val">85%</span></div>
      <div class="stat-row"><span class="stat-key">Max Motor Temp</span><span class="stat-val">70°C</span></div>
      <div class="stat-row"><span class="stat-key">Charge Cutoff</span><span class="stat-val">4.2V</span></div>
    </div>

    <div class="card">
      <div class="card-label">Connection Info</div>
      <div class="stat-row"><span class="stat-key">Firebase Status</span><span class="stat-val" id="cfg-fbstatus" style="color:var(--accent)">--</span></div>
      <div class="stat-row"><span class="stat-key">Last Sync</span><span class="stat-val" id="cfg-lastsync">--</span></div>
      <div class="stat-row"><span class="stat-key">ESP32 IP</span><span class="stat-val" id="cfg-ip">--</span></div>
      <div class="stat-row"><span class="stat-key">MAC Address</span><span class="stat-val" id="cfg-mac">--</span></div>
      <div style="margin-top:14px">
        <button class="ctrl-btn" onclick="document.getElementById('configModal').style.display='flex'">🔥 Reconfigure Firebase</button>
      </div>
    </div>
  </div>
</div>

<script>
// ========== NAVIGATION ==========
function showPage(id) {
  document.querySelectorAll('.page').forEach(p => p.classList.remove('active'));
  document.querySelectorAll('.nav-tab').forEach(t => t.classList.remove('active'));
  document.getElementById('page-'+id).classList.add('active');
  event.target.classList.add('active');
}

// ========== FIREBASE ==========
let db = null;
let demoMode = false;

function connectFirebase() {
  const cfg = {
    apiKey: document.getElementById('fb-apiKey').value.trim(),
    authDomain: document.getElementById('fb-authDomain').value.trim(),
    databaseURL: document.getElementById('fb-dbUrl').value.trim(),
    projectId: document.getElementById('fb-projectId').value.trim(),
  };
  if (!cfg.databaseURL) { alert('Database URL is required.'); return; }
  try {
    if (!firebase.apps.length) firebase.initializeApp(cfg);
    db = firebase.database();
    document.getElementById('configModal').style.display = 'none';
    setConnected(true);
    document.getElementById('cfg-fbstatus').textContent = 'CONNECTED';
    startFirebaseListeners();
    addLog('Firebase connected successfully', 'INFO', 'green');
  } catch(e) {
    alert('Firebase error: ' + e.message);
  }
}

function useDemoMode() {
  demoMode = true;
  document.getElementById('configModal').style.display = 'none';
  setConnected(true);
  document.getElementById('cfg-fbstatus').textContent = 'DEMO MODE';
  addLog('Running in demo mode — simulated data', 'INFO', 'amber');
  startDemoMode();
}

function setConnected(online) {
  const dot = document.getElementById('connDot');
  const lbl = document.getElementById('connLabel');
  dot.className = 'status-dot' + (online ? '' : ' offline');
  lbl.textContent = online ? 'ONLINE' : 'OFFLINE';
}

// ========== FIREBASE LISTENERS ==========
function startFirebaseListeners() {
  const ref = db.ref('sandbot');
  ref.on('value', snap => {
    const d = snap.val();
    if (!d) return;
    updateDashboard(d);
    document.getElementById('cfg-lastsync').textContent = new Date().toLocaleTimeString();
  });
  ref.on('child_changed', (snap) => {
    addLog('Data updated: ' + snap.key, 'SYNC', 'blue');
  });
}

// ========== DASHBOARD UPDATE ==========
function updateDashboard(d) {
  const now = new Date().toLocaleTimeString();
  document.getElementById('lastUpdate').textContent = now;

  // Battery
  const bat = d.battery || {};
  const batPct = bat.percentage ?? 0;
  setVal('ov-battery', batPct + '%', 'green');
  setVal('ov-battery-sub', Math.round(batPct * 50) + ' min remaining');
  setWidth('ov-battery-bar', batPct);
  setVal('ch-level', batPct + '%');
  setVal('ch-level-sub', Math.round(batPct * 30) + ' mAh remaining');
  setVal('us-batnow', batPct + '%');
  setVal('us-ring-val', (100 - batPct) + '%', 'blue');
  setRing('usRingFill', 100 - batPct);

  // Power
  const pw = d.power || {};
  setVal('ov-power', pw.watts ? pw.watts + 'W' : '0W', 'amber');
  setVal('ov-power-sub', pw.charging ? 'Charging active' : 'Not charging');
  setVal('ch-power', pw.watts ? pw.watts + 'W' : '0W');
  setVal('ch-power-sub', (pw.voltage ?? 0) + 'V / ' + (pw.current ?? 0) + 'A');
  setVal('ch-voltage', (pw.voltage ?? '--') + ' V');
  setVal('ch-current', (pw.current ?? '--') + ' A');
  setVal('ch-status', pw.charging ? 'CHARGING' : 'IDLE', pw.charging ? 'amber' : null);

  // Session
  const sess = d.session || {};
  const dur = formatDuration(sess.duration_seconds ?? 0);
  setVal('ov-session', dur);
  setVal('us-session', dur);
  setVal('us-currdur', dur);
  setVal('us-starttime', sess.start_time ?? '--');
  setVal('us-batstart', (sess.battery_start ?? '--') + '%');
  setVal('us-mahused', (sess.mah_consumed ?? '--') + ' mAh');
  setVal('us-avgcurrent', (sess.avg_current ?? '--') + ' A');
  setVal('us-batused', (sess.battery_used_pct ?? '--') + '%');

  // Machine state
  const state = d.state ?? 'idle';
  setMachineMode(state);

  // System
  const sys = d.system || {};
  setVal('ov-cputemp', (sys.cpu_temp ?? '--') + '°C');
  setVal('ov-battemp', (sys.battery_temp ?? '--') + '°C');
  setVal('ov-motorload', (sys.motor_load ?? '--') + '%');
  setVal('ov-wifi', (sys.wifi_rssi ?? '--') + ' dBm');
  setVal('ov-heap', Math.round((sys.free_heap ?? 0) / 1024) + ' KB');
  setVal('cfg-ip', sys.ip ?? '--');
  setVal('cfg-mac', sys.mac ?? '--');

  // Today's stats
  const today = d.today || {};
  setVal('ov-cycles', today.cleaning_cycles ?? '--');
  setVal('ov-runtime', formatDuration((today.run_seconds ?? 0)));
  setVal('ov-chargesessions', today.charge_sessions ?? '--');
  setVal('ov-debris', (today.debris_grams ?? '--') + ' g');
  setVal('ov-distance', (today.distance_meters ?? '--') + ' m');
  setVal('ov-area', (today.area_m2 ?? '--') + ' m²');
  setVal('ov-area-sub', 'today');

  // Charging stats
  const chd = d.charging_daily || {};
  setVal('ch-today-sessions', chd.sessions ?? '--');
  setVal('ch-today-time', formatDuration((chd.total_seconds ?? 0)));
  setVal('ch-today-energy', (chd.energy_wh ?? '--') + ' Wh');
  setVal('ch-avg-dur', formatDuration((chd.avg_duration ?? 0)));
  setVal('ch-first', chd.first_charge ?? '--');
  setVal('ch-last', chd.last_charge ?? '--');
  setVal('ch-health', (d.battery?.health ?? '--') + '%');
  setVal('ch-cycles', d.battery?.lifetime_cycles ?? '--');
  setVal('ch-energy', (pw.session_energy_wh ?? '--') + ' Wh');
  setVal('ch-tofull', formatDuration(pw.time_to_full ?? 0));
  setVal('ch-duration', formatDuration(pw.session_seconds ?? 0));

  // Lifetime
  const lt = d.lifetime || {};
  setVal('us-total', formatDuration(lt.total_seconds ?? 0));
  setVal('us-totalsessions', lt.sessions ?? '--');
  setVal('us-totalhours', (Math.round((lt.total_seconds ?? 0) / 3600)) + ' hrs');
  setVal('us-totaldist', ((lt.distance_m ?? 0) / 1000).toFixed(2) + ' km');
  setVal('us-totalarea', (lt.area_m2 ?? '--') + ' m²');
  setVal('us-avgsession', formatDuration(lt.avg_session ?? 0));
  setVal('us-longsession', formatDuration(lt.longest_session ?? 0));
  setVal('us-efficiency', (lt.efficiency ?? '--') + '%');

  // Sensors
  const sn = d.sensors || {};
  setVal('sn-airtemp', (sn.air_temp ?? '--') + '°C');
  setVal('sn-humidity', (sn.humidity ?? '--') + '%');
  setVal('sn-sandmoist', (sn.sand_moisture ?? '--') + '%');
  setVal('sn-vibration', (sn.vibration_g ?? '--') + ' G');
  setVal('sn-lrpm', sn.motor_l_rpm ?? '--');
  setVal('sn-rrpm', sn.motor_r_rpm ?? '--');
  setVal('sn-brpm', sn.brush_rpm ?? '--');
  setVal('sn-ltemp', (sn.motor_l_temp ?? '--') + '°C');
  setVal('sn-rtemp', (sn.motor_r_temp ?? '--') + '°C');
  setVal('sn-front', (sn.dist_front ?? '--') + ' cm');
  setVal('sn-rear', (sn.dist_rear ?? '--') + ' cm');
  setVal('sn-left', (sn.dist_left ?? '--') + ' cm');
  setVal('sn-right', (sn.dist_right ?? '--') + ' cm');
  setVal('sn-binfill', (sn.bin_fill ?? '--') + '%');
  setVal('sn-binwt', (sn.bin_weight_g ?? '--') + ' g');
  setVal('sn-vacuum', (sn.vacuum_pressure ?? '--') + ' Pa');
  setVal('sn-lat', sn.gps_lat ? sn.gps_lat.toFixed(6) : '--');
  setVal('sn-lon', sn.gps_lon ? sn.gps_lon.toFixed(6) : '--');

  // Alerts
  buildAlerts(d);

  // Charts
  if (d.weekly_charging) buildChart('ch-weekly-chart', 'ch-weekly-labels', d.weekly_charging, '#ffb224');
  if (d.weekly_usage) buildChart('us-weekly-chart', 'us-weekly-labels', d.weekly_usage, '#00e5a0');
}

// ========== HELPERS ==========
function setVal(id, val, color) {
  const el = document.getElementById(id);
  if (!el) return;
  el.textContent = val;
  if (color) el.style.color = `var(--${color})`;
}
function setWidth(id, pct) {
  const el = document.getElementById(id);
  if (el) el.style.width = Math.min(100, pct) + '%';
}
function setRing(id, pct) {
  const el = document.getElementById(id);
  if (!el) return;
  const circumference = 352;
  el.setAttribute('stroke-dashoffset', circumference - (pct / 100 * circumference));
}
function formatDuration(seconds) {
  if (!seconds || isNaN(seconds)) return '--';
  const h = Math.floor(seconds / 3600);
  const m = Math.floor((seconds % 3600) / 60);
  const s = Math.floor(seconds % 60);
  if (h > 0) return `${h}h ${m}m`;
  if (m > 0) return `${m}m ${s}s`;
  return `${s}s`;
}
function setMachineMode(state) {
  const el = document.getElementById('machineMode');
  const map = {
    cleaning: ['⚡ CLEANING', 'mode-cleaning'],
    charging: ['🔋 CHARGING', 'mode-charging'],
    idle:     ['◉ IDLE',     'mode-idle'],
    error:    ['⚠ ERROR',    'mode-error'],
  };
  const [label, cls] = map[state] || map['idle'];
  el.textContent = label;
  el.className = 'machine-mode ' + cls;
}
function buildAlerts(d) {
  const cont = document.getElementById('alertsContainer');
  const alerts = [];
  if (d.battery?.percentage < 20) alerts.push(['⚠ Battery low: ' + d.battery.percentage + '%', 'alert-warn']);
  if (d.sensors?.bin_fill > 85) alerts.push(['⚠ Collection bin almost full', 'alert-warn']);
  if (d.state === 'error') alerts.push(['✕ Machine error detected', 'alert-err']);
  if (d.sensors?.dist_front < 10) alerts.push(['⚠ Obstacle detected ahead', 'alert-warn']);
  if (!alerts.length) alerts.push(['✓ All systems nominal', 'alert-ok']);
  cont.innerHTML = alerts.map(([msg, cls]) => `<div class="alert ${cls}">${msg}</div>`).join('');
}
function buildChart(chartId, labelId, data, color) {
  const maxVal = Math.max(...data.map(d => d.value), 1);
  const chartEl = document.getElementById(chartId);
  const labelEl = document.getElementById(labelId);
  if (!chartEl || !labelEl) return;
  chartEl.innerHTML = data.map(d =>
    `<div style="flex:1;background:${color};opacity:0.7;border-radius:3px 3px 0 0;height:${Math.max(4, (d.value/maxVal)*76)}px;transition:height 0.5s" title="${d.label}: ${d.value}"></div>`
  ).join('');
  labelEl.innerHTML = data.map(d =>
    `<div style="flex:1;text-align:center;font-family:var(--mono);font-size:10px;color:var(--muted)">${d.label}</div>`
  ).join('');
}

// ========== LOGS ==========
let logItems = [];
function addLog(msg, type, color) {
  const now = new Date().toLocaleTimeString();
  const colorMap = { green:'badge-green', amber:'badge-amber', red:'badge-red', blue:'badge-blue', purple:'badge-purple' };
  logItems.unshift({ time: now, msg, type, badgeCls: colorMap[color] || 'badge-blue' });
  if (logItems.length > 50) logItems.pop();
  const cont = document.getElementById('logContainer');
  const dotColor = { green:'var(--accent)', amber:'var(--amber)', red:'var(--red)', blue:'var(--blue)', purple:'var(--purple)' }[color] || 'var(--muted)';
  cont.innerHTML = logItems.map(l =>
    `<div class="log-entry"><div class="log-dot" style="background:${dotColor}"></div><div><div class="log-time">${l.time}</div><div class="log-msg">${l.msg}</div></div><span class="log-badge ${l.badgeCls}">${l.type}</span></div>`
  ).join('');
}

// ========== COMMANDS ==========
function sendCmd(cmd) {
  addLog('Command sent: ' + cmd.toUpperCase(), 'CMD', 'purple');
  if (db) {
    db.ref('sandbot/commands').push({ cmd, timestamp: Date.now() });
  }
}
function setSetting(key, val) {
  addLog(`Setting "${key}" = ${val}`, 'CONFIG', 'blue');
  if (db) db.ref('sandbot/settings/' + key).set(val);
}

// ========== UPTIME COUNTER ==========
let uptimeSeconds = 0;
setInterval(() => {
  uptimeSeconds++;
  const h = String(Math.floor(uptimeSeconds/3600)).padStart(2,'0');
  const m = String(Math.floor((uptimeSeconds%3600)/60)).padStart(2,'0');
  const s = String(uptimeSeconds%60).padStart(2,'0');
  const el = document.getElementById('uptime-badge');
  if (el) el.textContent = `UP: ${h}:${m}:${s}`;
}, 1000);

// ========== DEMO MODE ==========
function startDemoMode() {
  const days = ['Mon','Tue','Wed','Thu','Fri','Sat','Sun'];
  let tick = 0;
  function generateDemoData() {
    tick++;
    const bat = Math.max(15, 85 - (tick % 80));
    const charging = bat < 25;
    const data = {
      state: charging ? 'charging' : (tick % 30 < 3 ? 'idle' : 'cleaning'),
      battery: { percentage: bat, health: 92, lifetime_cycles: 47 },
      power: { watts: charging ? 18 : 0, voltage: charging ? 12.6 : 0, current: charging ? 1.43 : 0, charging, session_energy_wh: 12, time_to_full: charging ? 3600 : 0, session_seconds: tick * 30 },
      session: { duration_seconds: tick * 30, start_time: '09:32 AM', battery_start: 88, battery_used_pct: 88 - bat, mah_consumed: (88-bat)*30, avg_current: 0.8 },
      system: { cpu_temp: 42 + Math.sin(tick*0.1)*3, battery_temp: 35 + Math.sin(tick*0.05)*2, motor_load: charging ? 0 : 55 + Math.sin(tick*0.2)*15, wifi_rssi: -58, free_heap: 220000, ip: '192.168.1.107', mac: 'A4:CF:12:3E:88:D2' },
      today: { cleaning_cycles: 3 + Math.floor(tick/40), run_seconds: tick*30, charge_sessions: 1, debris_grams: 142, distance_meters: tick*2, area_m2: tick*0.5 },
      charging_daily: { sessions: 1, total_seconds: 5400, energy_wh: 24, avg_duration: 5400, first_charge: '07:15 AM', last_charge: '08:45 AM' },
      lifetime: { total_seconds: 284400, sessions: 89, distance_m: 14200, area_m2: 8500, avg_session: 3196, longest_session: 7200, efficiency: 87 },
      sensors: {
        air_temp: 28 + Math.sin(tick*0.05)*3, humidity: 72 + Math.sin(tick*0.03)*8, sand_moisture: 18 + Math.sin(tick*0.07)*5, vibration_g: (0.3+Math.random()*0.2).toFixed(2),
        motor_l_rpm: charging ? 0 : 2800 + Math.sin(tick*0.3)*100, motor_r_rpm: charging ? 0 : 2820 + Math.sin(tick*0.32)*100, brush_rpm: charging ? 0 : 1400 + Math.sin(tick*0.25)*50,
        motor_l_temp: 44+Math.sin(tick*0.08)*4, motor_r_temp: 46+Math.sin(tick*0.09)*4,
        dist_front: 80 + Math.sin(tick*0.4)*40, dist_rear: 120, dist_left: 60 + Math.sin(tick*0.2)*20, dist_right: 65,
        bin_fill: Math.min(90, 20 + tick*0.3), bin_weight_g: Math.min(500, 80 + tick*1.2), vacuum_pressure: 1200, filter: 'CLEAN',
        gps_lat: 14.5995 + tick*0.00001, gps_lon: 120.9842 + tick*0.00001,
      },
      weekly_charging: days.map(l => ({ label: l, value: +(1+Math.random()*2.5).toFixed(1) })),
      weekly_usage:    days.map(l => ({ label: l, value: +(2+Math.random()*5).toFixed(1) })),
    };
    updateDashboard(data);
    document.getElementById('cfg-lastsync').textContent = new Date().toLocaleTimeString();
    if (tick % 5 === 0) {
      const msgs = ['Cleaning path updated', 'Battery level normal', 'Obstacle avoided', 'Debris collected', 'Coverage 68%', 'Motor temp nominal'];
      const colors = ['green','blue','amber','green','blue','green'];
      const types = ['STATUS','INFO','WARN','STATUS','INFO','STATUS'];
      const i = tick % msgs.length;
      addLog(msgs[i], types[i], colors[i]);
    }
  }
  generateDemoData();
  setInterval(generateDemoData, 2000);
}

// ========== INIT ==========
document.getElementById('connDot').className = 'status-dot offline';
document.getElementById('connLabel').textContent = 'DISCONNECTED';
</script>
</body>
</html>
)rawliteral";

#endif
