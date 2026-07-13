describe('TopBar Custom Element', () => {
  beforeEach(() => {
    // Clear DOM before each test
    document.body.innerHTML = '';

    // Require the component file which will define the custom element
    jest.resetModules();
    require('./topbar.js');

    // Add the custom element to the DOM
    document.body.innerHTML = '<msme-topbar></msme-topbar>';
  });

  it('renders the topbar container', () => {
    const topbar = document.querySelector('msme-topbar');
    const header = topbar.querySelector('header.topbar');
    expect(header).not.toBeNull();
  });

  it('contains the hamburger button', () => {
    const topbar = document.querySelector('msme-topbar');
    const hamburger = topbar.querySelector('#hamburger');
    expect(hamburger).not.toBeNull();
    expect(hamburger.classList.contains('hamburger')).toBe(true);
    expect(hamburger.getAttribute('aria-label')).toBe('Toggle menu');
  });

  it('contains the logo section with correct text', () => {
    const topbar = document.querySelector('msme-topbar');
    const logoLink = topbar.querySelector('a.topbar-logo');
    expect(logoLink).not.toBeNull();
    expect(logoLink.getAttribute('href')).toBe('index.html');

    const logoIcon = logoLink.querySelector('.logo-icon');
    expect(logoIcon.textContent).toBe('M');

    const logoText = logoLink.querySelector('.logo-text');
    expect(logoText.textContent).toBe('MSME Docs');

    const logoSub = logoLink.querySelector('.logo-sub');
    expect(logoSub.textContent).toBe('Embedded Systems Workshop');
  });

  it('contains the workshop badge', () => {
    const topbar = document.querySelector('msme-topbar');
    const badge = topbar.querySelector('.topbar-badge');
    expect(badge).not.toBeNull();
    expect(badge.textContent).toContain('Workshop');
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

  it('defines msme-topbar if not already defined', () => {
    customElements.get = jest.fn().mockReturnValue(undefined);
    customElements.define = jest.fn();

    require('./topbar.js');

    expect(customElements.get).toHaveBeenCalledWith('msme-topbar');
    expect(customElements.define).toHaveBeenCalledWith('msme-topbar', expect.any(Function));
  });

  it('does not define msme-topbar if already defined', () => {
    customElements.get = jest.fn().mockReturnValue(class {});
    customElements.define = jest.fn();

    require('./topbar.js');

    expect(customElements.get).toHaveBeenCalledWith('msme-topbar');
    expect(customElements.define).not.toHaveBeenCalled();
  });
});
