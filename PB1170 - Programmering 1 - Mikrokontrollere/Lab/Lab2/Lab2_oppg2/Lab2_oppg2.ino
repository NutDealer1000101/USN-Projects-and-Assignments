const int PIN_BUZ = 5;

const int PIN_BUT_1 = 2;
const int PIN_BUT_2 = 3;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BUZ, OUTPUT);
  pinMode(PIN_BUT_1, INPUT_PULLUP);
  pinMode(PIN_BUT_2, INPUT_PULLUP);
}

void loop() {
  if (!digitalRead(PIN_BUT_1)) {
    //Lang
    Serial.print("-");
    tone(PIN_BUZ, 500);
    delay(400);
    noTone(PIN_BUZ);
    while(!digitalRead(PIN_BUT_1));
  }
  else if (!digitalRead(PIN_BUT_2)) {
    //Kort
    Serial.print(".");
    tone(PIN_BUZ, 500);
    delay(200);
    noTone(PIN_BUZ);
    while(!digitalRead(PIN_BUT_2));
  }
}
