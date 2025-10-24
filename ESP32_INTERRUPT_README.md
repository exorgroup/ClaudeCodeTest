# ESP32 SOS Signal with Hardware Timer Interrupts

An advanced Arduino sketch for ESP32 that sends an SOS distress signal using hardware timer interrupts for precise, non-blocking operation.

## Key Features

- **Non-blocking**: Main loop remains free for other tasks
- **Precise timing**: Uses ESP32 hardware timer (Timer 0)
- **Interrupt-driven**: SOS signal runs completely in background
- **State machine**: Pattern-based approach for easy modification
- **Production-ready**: Suitable for real applications with multitasking requirements

## Differences from Basic Version

| Feature | Basic (sos_signal.ino) | Interrupt (sos_signal_int.ino) |
|---------|------------------------|----------------------------------|
| **Timing** | delay() blocking calls | Hardware timer interrupts |
| **CPU Usage** | Blocks entire program | Runs in background |
| **Precision** | Good | Excellent |
| **Complexity** | Simple | Moderate |
| **Platform** | Any Arduino | ESP32 only |
| **Multitasking** | No | Yes |

## When to Use This Version

✅ **Use interrupt version when:**
- You need the main loop for other tasks (WiFi, sensors, display, etc.)
- Timing precision is critical
- Building a production system
- Running multiple concurrent tasks

❌ **Use basic version when:**
- Learning Arduino basics
- Simple standalone project
- Using Arduino Uno/Nano (no hardware timers)
- Simplicity is preferred

## Hardware Requirements

- **ESP32 board** (ESP32-WROOM-32, ESP32-DevKitC, etc.)
- LED or bulb
- 220Ω resistor (for LED) or relay module (for bulb)
- Connecting wires
- USB cable for programming

## Circuit Diagram

### For LED:
```
ESP32 Pin 3 (GPIO3) ----[220Ω Resistor]----[LED]----GND
                                             |
                                          (Long leg/+)
```

### For Bulb (with relay):
```
ESP32 Pin 3 (GPIO3) ----[Relay Module]----[Bulb]----Power Supply
```

## Installation

### 1. Install ESP32 Board Support

In Arduino IDE:
1. Go to `File > Preferences`
2. Add to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to `Tools > Board > Boards Manager`
4. Search for "ESP32" and install "ESP32 by Espressif Systems"

### 2. Upload the Sketch

1. Open `sos_signal_int.ino` in Arduino IDE
2. Select your ESP32 board: `Tools > Board > ESP32 Arduino > ESP32 Dev Module`
3. Select the correct port: `Tools > Port`
4. Click **Upload** button (→)

## How It Works

### Timer Interrupt System

```
Timer fires every 10ms
         ↓
    ISR checks elapsed time
         ↓
    Pattern state machine
         ↓
    Update LED state
```

### State Machine

The sketch uses a pattern array that defines the complete SOS sequence:

```cpp
Pattern sosPattern[] = {
  {200, true},   // Dot ON
  {200, false},  // Gap
  {200, true},   // Dot ON
  // ... etc
};
```

Each timer interrupt:
1. Increments state counter by 10ms
2. Checks if current pattern duration completed
3. Advances to next pattern state
4. Updates LED accordingly

### Interrupt Service Routine (ISR)

The `IRAM_ATTR` attribute ensures the ISR runs from RAM for faster execution:

```cpp
void IRAM_ATTR onTimer() {
  // Fast execution from RAM
  // Updates LED state based on pattern
}
```

## Configuration

### Timing Adjustment

Modify these constants to change signal speed:

```cpp
const int DOT_DURATION = 200;      // Dot length in ms
const int DASH_DURATION = 600;     // Dash length in ms (3x dot)
const int SYMBOL_GAP = 200;        // Gap between symbols
const int LETTER_GAP = 600;        // Gap between letters
const int SEQUENCE_GAP = 2000;     // Gap before repeating
```

### Timer Interval

Change interrupt frequency (trade-off between precision and overhead):

```cpp
const int TIMER_INTERVAL_MS = 10;  // Timer fires every 10ms
// Options: 1, 5, 10, 20, 50, 100ms
```

Lower values = more precise, but higher CPU overhead

### Pin Assignment

Change the output pin:

```cpp
const int BULB_PIN = 3;  // Change to your desired GPIO pin
```

**Note:** ESP32 GPIO pins to avoid: 0, 2, 6-11 (used for flash), 34-39 (input-only)

## Serial Monitor Output

Open Serial Monitor at **115200 baud** to see:
- Startup messages
- Pattern confirmation
- Real-time status updates every 5 seconds
- Current state, counter, and LED status

```
ESP32 SOS Signal with Timer Interrupts Started
Pattern: . . . - - - . . .
Timer interrupt configured and enabled
Timer fires every 10 ms
Running... State: 0, Counter: 150 ms, LED: ON
Running... State: 6, Counter: 420 ms, LED: ON
```

## Using the Main Loop

The beauty of this interrupt-based approach is the main loop is free:

```cpp
void loop() {
  // SOS runs in background via interrupts

  // Add your code here:
  // - Read sensors
  // - Handle WiFi/Bluetooth
  // - Update display
  // - Process user input
  // - etc.

  // Example: Read temperature sensor
  float temp = readTemperature();
  sendToServer(temp);

  delay(100);  // Your timing, independent of SOS
}
```

## Advanced Usage

### Pausing the SOS Signal

```cpp
// Pause
timerAlarmDisable(timer);

// Resume
timerAlarmEnable(timer);
```

### Changing Pattern Dynamically

Modify the `sosPattern` array at runtime (be careful with interrupts):

```cpp
// Disable timer first
timerAlarmDisable(timer);

// Modify pattern
sosPattern[0].duration = 100;  // Faster dots

// Re-enable
currentState = 0;
stateCounter = 0;
timerAlarmEnable(timer);
```

## Troubleshooting

**LED not blinking:**
- Check pin number (ESP32 uses GPIO numbers)
- Verify LED polarity
- Check Serial Monitor for error messages
- Try pin 2 (built-in LED on many ESP32 boards)

**Erratic timing:**
- Ensure timer prescaler is correct (80 for 1MHz)
- Check for other interrupts interfering
- Verify TIMER_INTERVAL_MS is reasonable (10-100ms)

**Upload fails:**
- Hold BOOT button during upload
- Check correct board selected
- Verify USB cable supports data (not just power)
- Try different USB port

**Serial Monitor shows garbage:**
- Ensure baud rate is 115200
- Some garbage at startup is normal (bootloader)

## Memory Usage

Interrupt-based version uses:
- **Flash**: ~200KB (ESP32 has 4MB)
- **RAM**: ~4KB (ESP32 has 520KB)
- **CPU**: <1% when idle

Plenty of resources left for your application!

## Safety Notes

- ESP32 GPIO pins output 3.3V (not 5V like Arduino Uno)
- Maximum current per pin: 40mA
- For high-power bulbs, **always use a relay or transistor**
- Never connect mains voltage directly to ESP32
- Use proper insulation and enclosures

## Files

- `sos_signal_int.ino` - The ESP32 interrupt-based sketch
- `ESP32_INTERRUPT_README.md` - This file

## Further Reading

- [ESP32 Hardware Timers](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/timer.html)
- [ESP32 Arduino Core Documentation](https://docs.espressif.com/projects/arduino-esp32/en/latest/)
- [Interrupt Service Routines Best Practices](https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/)
