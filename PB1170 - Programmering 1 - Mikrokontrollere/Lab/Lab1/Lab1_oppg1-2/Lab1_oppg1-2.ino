const int PIN_LED_B = 3;
const int PIN_LED_Y = 4;
const int PIN_LED_R = 5;

const int PIN_POT = A0;
const int minDelay = 50;
const int maxDelay = 2000;

void ToggleLEDs(bool b, bool y, bool r) {
  digitalWrite(PIN_LED_B, b);
  digitalWrite(PIN_LED_Y, y);
  digitalWrite(PIN_LED_R, r);
}

void setup() {
  Serial.begin(9600);
  
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(PIN_LED_Y, OUTPUT);
  pinMode(PIN_LED_R, OUTPUT);

  pinMode(PIN_POT, INPUT);
}

void loop() {
  int potVal = analogRead(PIN_POT);
  int blinkDelay = map(potVal, 0, 1023, minDelay, maxDelay);

  ToggleLEDs(0, 0, 1);
  delay(3 * blinkDelay);

  ToggleLEDs(0, 1, 1);
  delay(blinkDelay);

  ToggleLEDs(1, 0, 0);
  delay(3 * blinkDelay);
  
  ToggleLEDs(0, 1, 0);
  delay(blinkDelay);
}
