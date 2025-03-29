const int PIN_LED = 2;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_LED, OUTPUT);

  Serial.println("Skriv inn delay: ");
}

void loop() {
  while (!Serial.available())
    ;
  int delay_led = Serial.parseInt();

  Serial.print("Delay: ");
  Serial.println(delay_led);

  Serial.println("Skriv inn ny delay: ");

  while (!Serial.available()) {
    digitalWrite(PIN_LED, HIGH);
    delay(delay_led);
    digitalWrite(PIN_LED, LOW);
    delay(delay_led);
  }
}
