//Oppgave 1
const int ledPin = 13;
const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int buttonPin3 = 18;

const int debounce_delay = 200;

enum possibleStates{on, blink, off, emergency};
const int numberOfStates = 4;
possibleStates state = on;

const int interval = 600;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(buttonPin1), incState, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonPin2), decState, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonPin3), doEmergency, RISING);

  Serial.begin(9600);
}

void loop() {
  static unsigned long lastChange = 0;

  Serial.println(state);
  static bool ledState = HIGH;
  switch(state){
    case on:
      ledState = HIGH;
      break;
    case blink:
      if(millis()>= lastChange + interval){
        ledState = !ledState;
        lastChange = millis();
      }
      break;
    case off:
    case emergency:
      ledState = LOW;
      break;
    default:
      Serial.println("Ugyldig state");
  }
  
  digitalWrite(ledPin, ledState);
}

void incState(){
  static size_t lastInterrupt = 0;
  if (millis() < lastInterrupt + debounce_delay) return;
  lastInterrupt = millis();

  switch (state) {
  case on:
    state = blink;
    break;
  case blink:
    state = off;
    break;
  case off:
    state = on;
    break;
  case emergency:
    break;
  default:
    break;
  }
}

void decState() {
  static size_t lastInterrupt = 0;
  if (millis() < lastInterrupt + debounce_delay) return;
  lastInterrupt = millis();

  switch (state) {
  case on:
    state = off;
    break;
  case blink:
    state = on;
    break;
  case off:
    state = blink;
    break;
  case emergency:
    break;
  default:
    break;
  }
}

void doEmergency() {
  static size_t lastInterrupt = 0;
  if (millis() < lastInterrupt + debounce_delay) return;
  lastInterrupt = millis();

  state = emergency;
}