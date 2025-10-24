# Simple Vue Web Application

A two-page web application demonstrating real-time state synchronization between browser windows.

## Features

- **Master Page**: Control panel with 3 toggle buttons (Red, Blue, Green)
- **Toy Page**: Display with 3 circles that fill/unfill based on button presses
- **Real-time Sync**: Changes are instantly reflected across open windows
- **State Persistence**: Circle states are saved and restored on page reload

## How to Use

1. Open `master.html` in your browser
2. Open `toy.html` in another browser window or tab
3. Click the buttons on the master page and watch the circles fill/unfill on the toy page
4. Click again to toggle them off
5. Refresh either page - the state persists!

## Technical Details

- Built with Vue 3 (loaded from CDN)
- Uses localStorage for state persistence
- Uses storage events for cross-window communication
- No build tools required - just open the HTML files directly

## Files

- `master.html` - Control page with toggle buttons
- `toy.html` - Display page with circles
