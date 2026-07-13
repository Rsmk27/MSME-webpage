describe('UI Interactions in app.js', () => {
  beforeEach(() => {
    document.body.innerHTML = `
      <div id="hamburger"></div>
      <msme-sidebar id="sidebar" class="sidebar"></msme-sidebar>
      <div id="overlay"></div>
    `;
    jest.resetModules();
    global.sidebarHTML = '';
    require('./sidebar.js');
    require('./app.js');
  });

  it('toggles sidebar and overlay when hamburger is clicked', () => {
    const hamburger = document.getElementById('hamburger');
    const sidebar = document.getElementById('sidebar');
    const overlay = document.getElementById('overlay');

    expect(sidebar.classList.contains('open')).toBe(false);
    expect(overlay.classList.contains('active')).toBe(false);

    hamburger.click();

    expect(sidebar.classList.contains('open')).toBe(true);
    expect(overlay.classList.contains('active')).toBe(true);

    hamburger.click();

    expect(sidebar.classList.contains('open')).toBe(false);
    expect(overlay.classList.contains('active')).toBe(false);
  });

  it('removes open and active classes when overlay is clicked', () => {
    const sidebar = document.getElementById('sidebar');
    const overlay = document.getElementById('overlay');

    sidebar.classList.add('open');
    overlay.classList.add('active');

    overlay.click();

    expect(sidebar.classList.contains('open')).toBe(false);
    expect(overlay.classList.contains('active')).toBe(false);
  });

  it('does not throw errors if elements are missing', () => {
    document.body.innerHTML = '';
    expect(() => {
      jest.resetModules();
      require('./sidebar.js');
      require('./app.js');
    }).not.toThrow();
  });
});
