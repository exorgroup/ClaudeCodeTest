# Master & Toy Control System

This project contains two components:
1. A web application for master-toy communication between browser windows
2. An Arduino sketch for SOS signal transmission

## Web Application Features

- **Master Page**: Control panel with 3 toggle buttons (Red, Blue, Green)
- **Toy Page**: Display with 3 circles that fill/unfill based on button presses
- **Device ID Pairing**: Only pages with matching device IDs communicate with each other
- **Open Button**: Toy page can trigger a message display on the master page
- **Real-time Sync**: Changes are instantly reflected across paired windows
- **State Persistence**: Device IDs and circle states are saved and restored on page reload

## How to Use the Web Application

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

## Arduino Component

This project includes two Arduino sketches for hardware integration.

### SOS Signal Arduino Sketches

Two versions available:

**1. Basic Version (sos_signal.ino)**
- Works on any Arduino (Uno, Nano, Mega, etc.)
- Simple delay-based timing
- Perfect for learning and standalone projects

**2. Interrupt-Based Version (sos_signal_int.ino)**
- ESP32 only
- Hardware timer interrupts for precision
- Non-blocking - main loop free for other tasks
- Production-ready for multitasking applications

Both versions:
- Send SOS distress signal (. . . - - - . . .)
- Connected to pin 3
- Configurable timing for dots and dashes
- Continuous transmission

See [ARDUINO_README.md](ARDUINO_README.md) for basic version documentation.
See [ESP32_INTERRUPT_README.md](ESP32_INTERRUPT_README.md) for interrupt version documentation.

## Files

### Web Application
- `master.html` - Control page with toggle buttons and Open message display
- `toy.html` - Display page with circles and Open button trigger

### Arduino
- `sos_signal.ino` - Basic Arduino sketch (any Arduino board)
- `sos_signal_int.ino` - Interrupt-based sketch (ESP32 only)
- `ARDUINO_README.md` - Basic version setup and usage documentation
- `ESP32_INTERRUPT_README.md` - Interrupt version detailed documentation

### Documentation
- `README.md` - This file

## Browser Compatibility

Works in all modern browsers that support:
- localStorage
- Storage events
- ES6 JavaScript features
