const int PIN_LED = 4;

const int PIN_BUT_1 = 2;
const int PIN_BUT_2 = 3;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUT_1, INPUT_PULLUP);
  pinMode(PIN_BUT_2, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(PIN_BUT_1) && !digitalRead(PIN_BUT_2)) {
    //Begge
    digitalWrite(PIN_LED, HIGH);
  }
  else if (digitalRead(PIN_BUT_1) && digitalRead(PIN_BUT_2)) {
    //Ingen
    digitalWrite(PIN_LED, LOW);
  }
  else {
    //En
    digitalWrite(PIN_LED, HIGH);
    delay(100);
    digitalWrite(PIN_LED, LOW);
    delay(100);
  }
}
