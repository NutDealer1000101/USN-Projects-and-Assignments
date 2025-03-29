const int PIN_LED = 13;
const int PIN_BUT_1 = 2;
const int PIN_BUT_2 = 3;
const int PIN_BUT_3 = 18;

const int PIN_POT = A15;

const int PIN_RGB_R = 22;
const int PIN_RGB_G = 23;
const int PIN_RGB_B = 24;

const int debounce_delay = 200;

enum possibleStates{on, blink, off, emergency};
const int numberOfStates = 4;
possibleStates blinkState = on;

const int interval = 600;

enum class RGB_STATE {
  R,
  G,
  B
};

void WriteRGB(RGB_STATE colorState, bool value) {
  colorState == RGB_STATE::R ? digitalWrite(PIN_RGB_R, value) : digitalWrite(PIN_RGB_R, LOW);
  colorState == RGB_STATE::G ? digitalWrite(PIN_RGB_G, value) : digitalWrite(PIN_RGB_G, LOW);
  colorState == RGB_STATE::B ? digitalWrite(PIN_RGB_B, value) : digitalWrite(PIN_RGB_B, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(PIN_POT, INPUT);
  pinMode(PIN_RGB_R, OUTPUT);
  pinMode(PIN_RGB_G, OUTPUT);
  pinMode(PIN_RGB_B, OUTPUT);

  pinMode(PIN_BUT_1, INPUT_PULLUP);
  pinMode(PIN_BUT_2, INPUT_PULLUP);
  pinMode(PIN_BUT_3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PIN_BUT_1), incState, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_BUT_2), decState, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_BUT_3), doEmergency, RISING);
}

void loop() {
  static unsigned long lastBlinkChange = 0;
  static RGB_STATE colorState = RGB_STATE::G;

  int potVal = analogRead(PIN_POT);
  Serial.print("Pot value = ");
  Serial.println(potVal);

  switch(colorState) {
  case RGB_STATE::R:
    if (potVal < 750) {
      colorState = RGB_STATE::B;
    }
    break;
  case RGB_STATE::G:
    if (potVal > 300) {
      colorState = RGB_STATE::B;
    }
    break;
  case RGB_STATE::B:
    if (potVal < 250) {
      colorState = RGB_STATE::G;
    }
    else if (potVal > 850) {
      colorState = RGB_STATE::R;
    }
    break;
  default:
    break;
  }

  static bool LEDstate = HIGH;
  switch(blinkState){
    case on:
      LEDstate = HIGH;
      break;
    case blink:
      if(millis()>= lastBlinkChange + interval){
        LEDstate = !LEDstate;
        lastBlinkChange = millis();
      }
      break;
    case off:
    case emergency:
      LEDstate = LOW;
      break;
    default:
      break;
  }

  WriteRGB(colorState, LEDstate);
}

void incState(){
  static size_t lastInterrupt = 0;
  if (millis() < lastInterrupt + debounce_delay) return;
  lastInterrupt = millis();

  switch (blinkState) {
  case on:
    blinkState = blink;
    break;
  case blink:
    blinkState = off;
    break;
  case off:
    blinkState = on;
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

  switch (blinkState) {
  case on:
    blinkState = off;
    break;
  case blink:
    blinkState = on;
    break;
  case off:
    blinkState = blink;
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

  blinkState = emergency;
}
