/*
 * SOS Signal Arduino Sketch
 *
 * This sketch sends an SOS signal (... --- ...) using an LED/bulb connected to pin 3
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
 */

const int BULB_PIN = 3;        // Pin connected to the bulb/LED
const int DOT_DURATION = 200;   // Duration of a dot in milliseconds
const int DASH_DURATION = 600;  // Duration of a dash in milliseconds (3x dot)
const int SYMBOL_GAP = 200;     // Gap between dots and dashes
const int LETTER_GAP = 600;     // Gap between letters
const int SEQUENCE_GAP = 2000;  // Gap between SOS sequences

void setup() {
  // Initialize the bulb pin as an output
  pinMode(BULB_PIN, OUTPUT);
  digitalWrite(BULB_PIN, LOW);

  // Optional: Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("SOS Signal Started");
}

void loop() {
  sendSOS();
  delay(SEQUENCE_GAP);
}

// Send complete SOS signal
void sendSOS() {
  Serial.println("Sending SOS...");

  // Send S (. . .)
  sendS();
  delay(LETTER_GAP);

  // Send O (- - -)
  sendO();
  delay(LETTER_GAP);

  // Send S (. . .)
  sendS();
}

// Send letter S: three dots (. . .)
void sendS() {
  Serial.print("S: ");
  for (int i = 0; i < 3; i++) {
    sendDot();
    if (i < 2) {
      delay(SYMBOL_GAP);
    }
  }
  Serial.println();
}

// Send letter O: three dashes (- - -)
void sendO() {
  Serial.print("O: ");
  for (int i = 0; i < 3; i++) {
    sendDash();
    if (i < 2) {
      delay(SYMBOL_GAP);
    }
  }
  Serial.println();
}

// Send a dot (.)
void sendDot() {
  Serial.print(". ");
  digitalWrite(BULB_PIN, HIGH);
  delay(DOT_DURATION);
  digitalWrite(BULB_PIN, LOW);
}

// Send a dash (-)
void sendDash() {
  Serial.print("- ");
  digitalWrite(BULB_PIN, HIGH);
  delay(DASH_DURATION);
  digitalWrite(BULB_PIN, LOW);
}
