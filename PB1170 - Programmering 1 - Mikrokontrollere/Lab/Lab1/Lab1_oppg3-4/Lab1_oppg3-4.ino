const int PIN_LED_R = 5;

const int PIN_BUTTON = 6;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
}

void loop() {
  bool buttonVal = digitalRead(PIN_BUTTON);
  Serial.print("Knapp: ");
  Serial.println(buttonVal);

  digitalWrite(PIN_LED_R, buttonVal);
}
