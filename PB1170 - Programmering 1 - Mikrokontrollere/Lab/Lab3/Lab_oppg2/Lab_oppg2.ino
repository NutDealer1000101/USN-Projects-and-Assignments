const int ledPin = 2;
const int buttonPin = 3;
const int potPin = A0;

const int minInterval = 0;
const int maxInterval = 10000;

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(potPin, INPUT);
}

void loop() {
  static unsigned long lastChange = 0;
  static bool ledState = LOW;

  int interval = map(analogRead(potPin), 0, 1023, minInterval, maxInterval);
  Serial.print("Interval: ");
  Serial.print(interval);
  Serial.println("ms.");

  if (millis() >= lastChange + interval) {
    //bytte verdi på ledstate
    ledState = !ledState;
    lastChange = millis();
  }

  if (!digitalRead(buttonPin)) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, ledState);
  }
}
