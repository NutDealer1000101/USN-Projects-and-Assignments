const int PIN_LED = 2;
const int PIN_BUT_1 = 3;
const int PIN_BUT_2 = 4;
const int PIN_BUZ = 5;

#define CODE_LENGTH 2
const int code[CODE_LENGTH] = { 1, 2 };

void setup() {
  Serial.begin(9600);

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUT_1, INPUT_PULLUP);
  pinMode(PIN_BUT_2, INPUT_PULLUP);
  pinMode(PIN_BUZ, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED, LOW);
  int buttonPresses[2];

  for (int i = 0; i < CODE_LENGTH; i++) {
    while (digitalRead(PIN_BUT_1) && digitalRead(PIN_BUT_2));

    buttonPresses[i] = !digitalRead(PIN_BUT_1) ? 1 : 2;

    Serial.print("Knapp ");
    Serial.print(buttonPresses[i]);
    Serial.println(" trykket.");

    while (!(digitalRead(PIN_BUT_1) && digitalRead(PIN_BUT_2)));
  }

  bool correct = true;
  for (int i = 0; i < CODE_LENGTH; i++) {
    if (buttonPresses[i] != code[i]) {
      correct = false;
      break;
    }
  }

  if (correct) {
    Serial.println("Riktig kode.");

    digitalWrite(PIN_LED, HIGH);

    tone(PIN_BUZ, 500);
    delay(100);
    noTone(PIN_BUZ);
    delay(100);
    tone(PIN_BUZ, 500);
    delay(100);
    noTone(PIN_BUZ);
    delay(100);
    tone(PIN_BUZ, 500);
    delay(100);
    noTone(PIN_BUZ);

    digitalWrite(PIN_LED, LOW);
  } else {
    Serial.println("Feil kode.");

    tone(PIN_BUZ, 500);
    delay(200);
    tone(PIN_BUZ, 100);
    delay(300);
    noTone(PIN_BUZ);
  }
}