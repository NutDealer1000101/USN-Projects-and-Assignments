const int PIN_LED = 2;
const int blink_delay = 200;

void setup() {
  pinMode(PIN_LED, OUTPUT);

  for (int i = 0; i < 15; i++) {
    digitalWrite(PIN_LED, HIGH);
    delay(blink_delay);
    digitalWrite(PIN_LED, LOW);
    delay(blink_delay);
  }

  digitalWrite(PIN_LED, LOW);  
}

void loop() {}
