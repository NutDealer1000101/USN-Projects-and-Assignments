const int PIN_BUT_1 = 2;
const int PIN_BUT_2 = 3;
const int PIN_LED = 4;

const int debounce_time = 200;

volatile int delay_time = 1024 * 2;

void setup() {
  Serial.begin(9600);

  pinMode(PIN_BUT_1, INPUT_PULLUP);
  pinMode(PIN_BUT_2, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_BUT_1), BlinkFaster, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_BUT_2), BlinkSlower, RISING);

  Serial.print("Delay = ");
  Serial.println(delay_time);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  delay(delay_time);
  digitalWrite(PIN_LED, LOW);
  delay(delay_time);
}

void BlinkFaster() {
  static size_t lastInterupt = 0;
  if (millis() < lastInterupt + debounce_time) return;
  lastInterupt = millis();

  delay_time /= 2;
  if (delay_time == 0) delay_time = 1;

  Serial.print("Knapp trykket 1! Ny delay = ");
  Serial.println(delay_time);
}

void BlinkSlower() {
  static size_t lastInterupt = 0;
  if (millis() < lastInterupt + debounce_time) return;
  lastInterupt = millis();

  delay_time *= 2;

  Serial.print("Knapp trykket 2! Ny delay = ");
  Serial.println(delay_time);
}