const hamburger = document.getElementById('hamburger');
const sidebar   = document.getElementById('sidebar');
const overlay   = document.getElementById('overlay');

if (sidebar) {
  // Create the nav element
  const nav = document.createElement('nav');
  if (typeof sidebarHTML !== 'undefined') {
    nav.innerHTML = sidebarHTML;
  }

  // Set active class based on current URL
  // In a real browser, window.location.pathname works, but in JSDOM testing it might be empty or 'blank'
  // so we safely handle it.
  let currentPath = '';
  if (typeof window !== 'undefined' && window.location && window.location.pathname) {
     currentPath = window.location.pathname.split('/').pop();
  }
  if (!currentPath || currentPath === 'blank') {
     currentPath = 'index.html';
  }

  const activeLink = nav.querySelector(`a[href="${currentPath}"]`);
  if (activeLink) {
    activeLink.classList.add('active');
  }

  sidebar.appendChild(nav);
}

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
