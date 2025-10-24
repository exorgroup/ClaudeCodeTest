/*
 * SOS Signal Arduino Sketch for ESP32 - Interrupt-Based
 *
 * This sketch sends an SOS signal (... --- ...) using an LED/bulb connected to pin 3
 * Uses ESP32 hardware timer interrupts for precise timing without blocking
 *
 * SOS Pattern:
 * S = . . . (three dots)
 * O = - - - (three dashes)
 * S = . . . (three dots)
 *
 * Timing:
 * - Dot: 200ms ON
 * - Dash: 600ms ON (3x dot length)
 * - Gap between dots/dashes: 200ms OFF
 * - Gap between letters: 600ms OFF
 * - Gap between SOS sequences: 2000ms OFF
 *
 * Hardware: ESP32 (tested on ESP32-WROOM-32)
 * Timer: Hardware Timer 0
 */

const int BULB_PIN = 3;        // Pin connected to the bulb/LED

// Timing constants (in milliseconds)
const int DOT_DURATION = 200;
const int DASH_DURATION = 600;
const int SYMBOL_GAP = 200;
const int LETTER_GAP = 600;
const int SEQUENCE_GAP = 2000;

// Timer configuration
const int TIMER_INTERVAL_MS = 10;  // Timer fires every 10ms
hw_timer_t *timer = NULL;

// State machine variables (volatile because accessed in ISR)
volatile int currentState = 0;
volatile int stateCounter = 0;
volatile bool ledState = false;

// SOS Pattern definition
// Each element is: {duration_ms, led_state}
// Negative duration means it's a gap (LED off)
struct Pattern {
  int duration;  // Duration in ms
  bool ledOn;    // LED state
};

// Define the complete SOS pattern
const int PATTERN_LENGTH = 17;
Pattern sosPattern[PATTERN_LENGTH] = {
  // First S (. . .)
  {DOT_DURATION, true},      // 0: Dot ON
  {SYMBOL_GAP, false},       // 1: Gap
  {DOT_DURATION, true},      // 2: Dot ON
  {SYMBOL_GAP, false},       // 3: Gap
  {DOT_DURATION, true},      // 4: Dot ON
  {LETTER_GAP, false},       // 5: Letter gap

  // O (- - -)
  {DASH_DURATION, true},     // 6: Dash ON
  {SYMBOL_GAP, false},       // 7: Gap
  {DASH_DURATION, true},     // 8: Dash ON
  {SYMBOL_GAP, false},       // 9: Gap
  {DASH_DURATION, true},     // 10: Dash ON
  {LETTER_GAP, false},       // 11: Letter gap

  // Second S (. . .)
  {DOT_DURATION, true},      // 12: Dot ON
  {SYMBOL_GAP, false},       // 13: Gap
  {DOT_DURATION, true},      // 14: Dot ON
  {SYMBOL_GAP, false},       // 15: Gap
  {DOT_DURATION, true},      // 16: Dot ON
};

// Timer interrupt service routine
void IRAM_ATTR onTimer() {
  stateCounter += TIMER_INTERVAL_MS;

  // Check if current state duration has elapsed
  if (stateCounter >= sosPattern[currentState].duration) {
    // Move to next state
    currentState++;

    // If we've completed the pattern, add sequence gap and restart
    if (currentState >= PATTERN_LENGTH) {
      currentState = 0;
      stateCounter = -SEQUENCE_GAP;  // Wait before restarting
      digitalWrite(BULB_PIN, LOW);
      ledState = false;
      return;
    }

    // Reset counter for new state
    stateCounter = 0;

    // Update LED based on new state
    ledState = sosPattern[currentState].ledOn;
    digitalWrite(BULB_PIN, ledState ? HIGH : LOW);
  }
}

void setup() {
  // Initialize the bulb pin as an output
  pinMode(BULB_PIN, OUTPUT);
  digitalWrite(BULB_PIN, LOW);

  // Initialize serial for debugging
  Serial.begin(115200);
  Serial.println("ESP32 SOS Signal with Timer Interrupts Started");
  Serial.println("Pattern: . . . - - - . . .");

  // Configure timer
  // Timer 0, prescaler 80 (80MHz/80 = 1MHz = 1μs per tick)
  timer = timerBegin(0, 80, true);

  // Attach interrupt function to timer
  timerAttachInterrupt(timer, &onTimer, true);

  // Set timer alarm (fires every TIMER_INTERVAL_MS milliseconds)
  // 1000 microseconds = 1 millisecond, so multiply by TIMER_INTERVAL_MS
  timerAlarmWrite(timer, TIMER_INTERVAL_MS * 1000, true);

  // Enable timer
  timerAlarmEnable(timer);

  Serial.println("Timer interrupt configured and enabled");
  Serial.printf("Timer fires every %d ms\n", TIMER_INTERVAL_MS);
}

void loop() {
  // Main loop is free to do other tasks
  // The SOS signal runs completely in the background via interrupts

  // Optional: Print status every 5 seconds
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 5000) {
    lastPrint = millis();
    Serial.printf("Running... State: %d, Counter: %d ms, LED: %s\n",
                  currentState, stateCounter, ledState ? "ON" : "OFF");
  }

  // You can add other non-blocking code here
  // For example: reading sensors, handling WiFi, etc.
  delay(100);
}
