## 2024-05-17 - Add focus-visible styles for keyboard navigation
**Learning:** Found that this project lacked any `:focus-visible` styles, leading to poor keyboard navigation UX since users couldn't see where their focus was. Applying a global `*:focus-visible` using the design system's `--primary-hover` variable creates an immediate and noticeable accessibility win without adding complexity.
**Action:** Always check for existing focus styles, particularly `:focus-visible` instead of `:focus` so that mouse users' experience is not impacted, while fully supporting keyboard navigators.
