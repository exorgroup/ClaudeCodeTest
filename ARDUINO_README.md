# Arduino SOS Signal

An Arduino sketch that sends an SOS distress signal using an LED or bulb connected to pin 3.

## SOS Pattern

The SOS signal in Morse code is:
- **S**: . . . (three dots)
- **O**: - - - (three dashes)
- **S**: . . . (three dots)

Complete pattern: **. . . - - - . . .**

## Hardware Requirements

- Arduino board (Uno, Nano, Mega, etc.)
- LED or bulb
- 220Ω resistor (for LED) or appropriate relay/transistor (for bulb)
- Connecting wires
- Breadboard (optional)

## Circuit Diagram

### For LED:
```
Arduino Pin 3 ----[220Ω Resistor]----[LED]----GND
                                      |
                                    (Long leg/+)
```

### For Bulb (with relay):
```
Arduino Pin 3 ----[Relay Module]----[Bulb]----Power Supply
```

## Installation

1. Open Arduino IDE
2. Open the `sos_signal.ino` file
3. Select your Arduino board: `Tools > Board`
4. Select the correct port: `Tools > Port`
5. Click **Upload** button (→)

## Timing Configuration

The sketch uses the following timing (can be adjusted in the code):

| Parameter | Duration | Description |
|-----------|----------|-------------|
| Dot | 200ms | Short pulse |
| Dash | 600ms | Long pulse (3x dot) |
| Symbol Gap | 200ms | Gap between dots/dashes |
| Letter Gap | 600ms | Gap between S and O |
| Sequence Gap | 2000ms | Gap before repeating SOS |

## Customization

You can modify the timing by changing these constants in the sketch:

```cpp
const int DOT_DURATION = 200;   // Change dot duration
const int DASH_DURATION = 600;  // Change dash duration
const int SYMBOL_GAP = 200;     // Change gap between symbols
const int LETTER_GAP = 600;     // Change gap between letters
const int SEQUENCE_GAP = 2000;  // Change gap between sequences
```

To use a different pin, change:
```cpp
const int BULB_PIN = 3;  // Change to your desired pin number
```

## Serial Monitor

The sketch outputs debug information to the Serial Monitor (9600 baud):
- Opens: `Tools > Serial Monitor`
- Shows the SOS pattern being sent in real-time
- Displays dots (.) and dashes (-) as they're transmitted

## Troubleshooting

**LED not lighting:**
- Check wiring connections
- Verify correct pin number (pin 3)
- Check LED polarity (long leg to resistor, short leg to GND)
- Test with a simple blink sketch first

**Using a bulb:**
- Bulbs require more current than Arduino can provide
- Use a relay module or transistor to control the bulb
- Ensure proper power supply for the bulb

**Signal too fast/slow:**
- Adjust the timing constants in the code
- Upload the modified sketch

## Files

- `sos_signal.ino` - The Arduino sketch file

## Safety Notes

- Do not exceed the current rating of your Arduino pin (max 40mA)
- For high-power bulbs, always use a relay or transistor
- Ensure proper insulation when working with mains voltage
- Never connect mains voltage directly to Arduino pins
