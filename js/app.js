class MsmeTopbar extends HTMLElement {
  connectedCallback() {
    this.innerHTML = `
<!-- Top Bar -->
<header class="topbar">
  <button class="hamburger" id="hamburger" aria-label="Toggle menu">&#9776;</button>
  <a href="index.html" class="topbar-logo">
    <div class="logo-icon">M</div>
    <div>
      <span class="logo-text">MSME Docs</span>
      <span class="logo-sub">Embedded Systems Workshop</span>
    </div>
  </a>
  <div class="topbar-spacer"></div>
  <span class="topbar-badge">&#127979; Workshop</span>
</header>
    `;
  }
}

if (!customElements.get('msme-topbar')) {
  customElements.define('msme-topbar', MsmeTopbar);
}


const hamburger = document.getElementById('hamburger');
const sidebar   = document.getElementById('sidebar');
const overlay   = document.getElementById('overlay');

if (hamburger && sidebar && overlay) {
  hamburger.addEventListener('click', () => {
    sidebar.classList.toggle('open');
    overlay.classList.toggle('active');
  });
  overlay.addEventListener('click', () => {
    sidebar.classList.remove('open');
    overlay.classList.remove('active');
  });
}
