const int PIN_LED = 4;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  int delay_ms = 20;
  while (delay_ms < 5000) {
    Serial.print("Current delay (ms): ");
    Serial.println(delay_ms);

    digitalWrite(PIN_LED, HIGH);
    delay(delay_ms);
    digitalWrite(PIN_LED, LOW);
    delay(delay_ms);

    delay_ms = delay_ms + 250;
  }
}
