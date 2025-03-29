const int PIN_LED = 2;
const int PIN_BUZ = 3;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUZ, OUTPUT);

  Serial.println("Velg LED (1) eller Buzzer (2): ");
}

void loop() {
  static int modus = 0;
  static int delay_led, freq_buz;

  digitalWrite(PIN_LED, LOW);
  noTone(PIN_BUZ);

  if (Serial.available()) {
    int forrige_modus = modus;
    modus = Serial.parseInt();

    if (modus == 1) {
      delay_led = Serial.parseInt();
      Serial.println("Ny modus: LED");
      Serial.print("Ny delay for LED er ");
      Serial.println(delay_led);

    } else if (modus == 2) {
      freq_buz = Serial.parseInt();
      Serial.println("Ny modus: Buzzer");
      Serial.print("Ny frekvens for Buzzer er ");
      Serial.println(freq_buz);

    } else {
      Serial.println("Ugyldig modus.");
      modus = forrige_modus;
    }

    Serial.println("");
    Serial.println("Velg LED (1) eller Buzzer (2): ");
  }

  if (modus == 1) {
    digitalWrite(PIN_LED, HIGH);
    delay(delay_led);
    digitalWrite(PIN_LED, LOW);
    delay(delay_led);

  } else if (modus == 2) {
    tone(PIN_BUZ, freq_buz);
    delay(1000);

  }
}
