class Sidebar extends HTMLElement {
  connectedCallback() {
    this.innerHTML = `
      <nav>
        <div class="sidebar-section">
          <div class="sidebar-section-title">Navigation</div>
          <ul>
            <li><a href="index.html"><span class="nav-icon">&#127968;</span> Home</a></li>
          </ul>
        </div>
        <div class="sidebar-section">
          <div class="sidebar-section-title">Setup &amp; Tools</div>
          <ul>
            <li><a href="getting-started.html"><span class="nav-icon">&#128640;</span> Getting Started</a></li>
            <li><a href="hardware.html"><span class="nav-icon">&#9881;</span> Hardware Reference</a></li>
          </ul>
        </div>
        <div class="sidebar-section">
          <div class="sidebar-section-title">Programming</div>
          <ul>
            <li><a href="programming.html"><span class="nav-icon">&#128187;</span> STM32 Programming</a></li>
            <li><a href="sensors.html"><span class="nav-icon">&#128268;</span> Sensors &amp; Interfaces</a></li>
          </ul>
        </div>
        <div class="sidebar-section">
          <div class="sidebar-section-title">Advanced Topics</div>
          <ul>
            <li><a href="iot.html"><span class="nav-icon">&#127760;</span> IoT &amp; Cloud</a></li>
            <li><a href="linux.html"><span class="nav-icon">&#128032;</span> Linux Tools</a></li>
          </ul>
        </div>
        <div class="sidebar-section">
          <div class="sidebar-section-title">Workshop</div>
          <ul>
            <li><a href="workshop.html"><span class="nav-icon">&#128203;</span> Workshop Materials</a></li>
            <li><a href="projects.html"><span class="nav-icon">&#129302;</span> Projects</a></li>
          </ul>
        </div>
      </nav>
    `;

    // Set active class based on current URL
    let currentPath = '';
    if (typeof window !== 'undefined' && window.location && window.location.pathname) {
       currentPath = window.location.pathname.split('/').pop();
    }
    if (!currentPath || currentPath === 'blank') {
       currentPath = 'index.html';
    }

    const activeLink = this.querySelector(`a[href="${currentPath}"]`);
    if (activeLink) {
      activeLink.classList.add('active');
    }
  }
}

if (!customElements.get('msme-sidebar')) {
  customElements.define('msme-sidebar', Sidebar);
}
