# Simple Web Application - Master & Toy Pages

A two-page web application demonstrating real-time state synchronization between browser windows using vanilla JavaScript.

## Features

- **Master Page**: Control panel with 3 toggle buttons (Red, Blue, Green)
- **Toy Page**: Display with 3 circles that fill/unfill based on button presses
- **Device ID Pairing**: Only pages with matching device IDs communicate with each other
- **Open Button**: Toy page can trigger a message display on the master page
- **Real-time Sync**: Changes are instantly reflected across paired windows
- **State Persistence**: Device IDs and circle states are saved and restored on page reload

## How to Use

### Basic Setup

1. Open `master.html` in your browser
2. Open `toy.html` in another browser window or tab
3. Enter the **same Device ID** in both pages (e.g., "device1")
4. The pages are now paired and will communicate with each other

### Using the Master Page

- Click the **Red**, **Blue**, or **Green** buttons to toggle the corresponding circles on the toy page
- Click again to toggle them off
- The status bar shows the current state of all three colors

### Using the Toy Page

- Watch the circles fill/unfill as buttons are pressed on the master page
- Click the **Open** button to display a violet "Open" message on the master page for 5 seconds

### Multiple Pairs

You can run multiple independent master-toy pairs simultaneously:
- Master #1 (ID: "pair1") ↔ Toy #1 (ID: "pair1")
- Master #2 (ID: "pair2") ↔ Toy #2 (ID: "pair2")
- Each pair operates independently without interference

## Running the Application

### Option 1: Direct File Access
Simply open the HTML files directly in your browser (file:// protocol)

### Option 2: Local Server (Recommended)
```bash
# Using Python 3
python3 -m http.server 8000

# Then open in browser:
# http://localhost:8000/master.html
# http://localhost:8000/toy.html
```

## Technical Details

- **Pure vanilla JavaScript** - No frameworks or dependencies
- **localStorage** - For state persistence across page reloads
- **Storage Events** - For real-time cross-window communication
- **Device-specific keys** - All localStorage keys include device ID for isolation
- **No build tools required** - Just open the HTML files directly

### How Communication Works

1. Master page updates state → saves to `localStorage` with device ID
2. Browser fires `storage` event to all other tabs/windows
3. Toy page receives event → checks if device ID matches → updates circles
4. Same process works in reverse for the Open button

## Files

- `master.html` - Control page with toggle buttons and Open message display
- `toy.html` - Display page with circles and Open button trigger
- `README.md` - This file

## Browser Compatibility

Works in all modern browsers that support:
- localStorage
- Storage events
- ES6 JavaScript features
