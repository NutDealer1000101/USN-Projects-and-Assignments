#include <IRremote.h>
#include <Unistep2.h>

const int stepsPerRevolution = 4096;
Unistep2 stepper(22, 23, 24, 25, stepsPerRevolution, 1000);

const int PIN_BUZ = 5;

#define IR_RECEIVE_PIN 2

const int correctCode[] = { 1, 2, 3, 4 };
const int codeLength = sizeof(correctCode) / sizeof(correctCode[0]);

int userInput[codeLength];  // Lagrer inputs
int inputIndex = 0;         // Tracker posisjonen til userinput


void setup() {
  Serial.begin(9600);

  pinMode(PIN_BUZ, OUTPUT);

  IrReceiver.begin(IR_RECEIVE_PIN);

  for (int i = 0; i < codeLength; i++) {
    userInput[i] = -1;
  }
}

void loop() {
  stepper.run();

  static bool lockState = true;
  static long long lockOpenTime = 0;
  static long long lockCloseTime = 0;

  if (!lockState && stepper.stepsToGo() == 0 && millis() > lockOpenTime + 10000) {
    stepper.move(-stepsPerRevolution / 2);
    lockCloseTime = millis();
    lockState = true;
  }

  int button = ReadIR();
  if (button != -1 && lockState && stepper.stepsToGo() == 0) {
    Serial.print("Input: ");
    Serial.println(button);
    userInput[inputIndex++] = button;

    if (inputIndex == codeLength) {
      Serial.print("Kode = ");
      for (int i = 0; i < codeLength; i++) {
        Serial.print(userInput[i]);
      }
      Serial.println("");

      if (CheckCode()) {
        Serial.println("Riktig!");
        lockState = false;
        stepper.move(stepsPerRevolution / 2);
        lockOpenTime = millis();
      } else {
        Serial.println("FEIL!!!!");
        IrReceiver.stopTimer();
        tone(PIN_BUZ, 200);
        delay(500);
        noTone(PIN_BUZ);
        IrReceiver.restartTimer();
      }
      inputIndex = 0;
    }
  }
}

// Funksjon for å sjekke at koden er riktig:
bool CheckCode() {
  for (int i = 0; i < codeLength; i++) {
    if (userInput[i] != correctCode[i]) {
      return false;
    }
  }
  return true;
}

int ReadIR() {
  static int lastButton = -1;
  static unsigned long lastPressTime = 0;
  const unsigned long debounceTime = 300;

  if (IrReceiver.decode()) {
    int val = IrReceiver.decodedIRData.command;
    int button = IrButtonMap(val);

    if (button != lastButton || millis() - lastPressTime > debounceTime) {
      lastButton = button;
      lastPressTime = millis();
      IrReceiver.resume();
      return button;
    }

    IrReceiver.resume();
  }

  return -1;
}

int IrButtonMap(int val) {
  switch (val) {
    case 12:
      return 1;
    case 24:
      return 2;
    case 94:
      return 3;
    case 8:
      return 4;
    case 28:
      return 5;
    case 90:
      return 6;
    case 66:
      return 7;
    case 82:
      return 8;
    case 74:
      return 9;
    case 22:
      return 0;
    default:
      return -1;
  }
}