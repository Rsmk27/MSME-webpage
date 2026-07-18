describe('Sidebar Custom Element', () => {
  beforeEach(() => {
    // Clear DOM before each test
    document.body.innerHTML = '';

    // Reset location using pushState
    window.history.pushState({}, '', '/');

    // Require the component file which will define the custom element
    jest.resetModules();
    require('./sidebar.js');
  });

  it('renders the sidebar container', () => {
    document.body.innerHTML = '<msme-sidebar></msme-sidebar>';
    const sidebar = document.querySelector('msme-sidebar');
    const nav = sidebar.querySelector('nav');
    expect(nav).not.toBeNull();
  });

  it('contains expected sections', () => {
    document.body.innerHTML = '<msme-sidebar></msme-sidebar>';
    const sidebar = document.querySelector('msme-sidebar');
    const sections = sidebar.querySelectorAll('.sidebar-section-title');
    const sectionTitles = Array.from(sections).map(s => s.textContent);

    expect(sectionTitles).toContain('Navigation');
    expect(sectionTitles).toContain('Setup & Tools');
    expect(sectionTitles).toContain('Programming');
    expect(sectionTitles).toContain('Advanced Topics');
    expect(sectionTitles).toContain('Workshop');
  });

  it('sets active class for index.html when path is empty or /', () => {
    window.history.pushState({}, '', '/');
    document.body.innerHTML = '<msme-sidebar></msme-sidebar>';
    const sidebar = document.querySelector('msme-sidebar');

    const activeLink = sidebar.querySelector('.active');
    expect(activeLink).not.toBeNull();
    expect(activeLink.getAttribute('href')).toBe('index.html');
  });

  it('sets active class for hardware.html when path is /hardware.html', () => {
    window.history.pushState({}, '', '/hardware.html');
    document.body.innerHTML = '<msme-sidebar></msme-sidebar>';
    const sidebar = document.querySelector('msme-sidebar');

    const activeLink = sidebar.querySelector('.active');
    expect(activeLink).not.toBeNull();
    expect(activeLink.getAttribute('href')).toBe('hardware.html');
  });
});

describe('Custom Element Registration', () => {
  let originalGet;
  let originalDefine;

  beforeEach(() => {
    originalGet = customElements.get;
    originalDefine = customElements.define;
    jest.resetModules();
  });

  afterEach(() => {
    customElements.get = originalGet;
    customElements.define = originalDefine;
  });

  it('defines msme-sidebar if not already defined', () => {
    customElements.get = jest.fn().mockReturnValue(undefined);
    customElements.define = jest.fn();

    require('./sidebar.js');

    expect(customElements.get).toHaveBeenCalledWith('msme-sidebar');
    expect(customElements.define).toHaveBeenCalledWith('msme-sidebar', expect.any(Function));
  });

  it('does not define msme-sidebar if already defined', () => {
    customElements.get = jest.fn().mockReturnValue(class {});
    customElements.define = jest.fn();

    require('./sidebar.js');

    expect(customElements.get).toHaveBeenCalledWith('msme-sidebar');
    expect(customElements.define).not.toHaveBeenCalled();
  });
});
