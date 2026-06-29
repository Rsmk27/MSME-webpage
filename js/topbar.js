class TopBar extends HTMLElement {
  connectedCallback() {
    this.innerHTML = `
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
  customElements.define('msme-topbar', TopBar);
}
