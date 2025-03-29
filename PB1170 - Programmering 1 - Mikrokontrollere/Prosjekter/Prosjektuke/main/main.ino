/*
* Prosjektuke 2024
* Oppgave 1 - Smarthus
* Laget av Daniel Gulliksrud Nilssen, Samuel Olsson Dahl og Lukas Andersen
*/

#include <SPI.h>
#include <RFID.h>
#include <Servo.h>
#include <IRremote.h>
#include <Unistep2.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//LDR
const int PIN_LDR = A15;
const int PIN_LED_LDR = 7;

//Servo
const int PIN_SERVO = 13;

const uint32_t servo_open_time_total = 5000;
const uint32_t servo_led_on_time = 2000;
Servo servo;

//RFID og kode
#define SDA_DIO 9
#define RESET_DIO 8
const int PIN_LED_RFID = 6;

RFID RC522(SDA_DIO, RESET_DIO); //RFID-leseren bruker også pinne 50, 51 og 52
const int correctSerNum[5] = { 3, 31, 213, 39, 238 };  //Det riktige serienummeret til nøkkelkortet
const uint32_t RFID_read_interval = 1000;

//IR-mottaker og kode
#define IR_RECEIVE_PIN 2

const int correctCode[] = { 1, 2, 3, 4 }; 
const int codeLength = sizeof(correctCode) / sizeof(correctCode[0]);
int userInput[codeLength];
int inputIndex = 0; 

//Buzzer
const int PIN_BUZ = 5;

//Stepper
const int stepsPerRevolution = 4096;
Unistep2 stepper(22, 23, 24, 25, stepsPerRevolution, 1000);
const int lockOpenTimeTotal = 10000;


//LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);

  SPI.begin();
  RC522.init();

  servo.attach(PIN_SERVO);
  servo.write(0);

  IrReceiver.begin(IR_RECEIVE_PIN);

  lcd.init();
  lcd.backlight();

  pinMode(PIN_LDR, INPUT);
  pinMode(PIN_LED_LDR, OUTPUT);
  pinMode(PIN_LED_RFID, OUTPUT);
  pinMode(PIN_BUZ, OUTPUT);

  for (int i = 0; i < codeLength; i++) {
    userInput[i] = -1;
  }

  delay(1000);

  lcd.print("Ready!");
}

void loop() {
  UpdateLED();

  UpdateIR();

  stepper.run();

  UpdateRFID();
}

//Logikken til IR-mottaker og steppermotor
void UpdateIR() {
  static bool lockState = true;
  static long long lockOpenTime = 0;
  static long long lockCloseTime = 0;

  //Hvis låsen er åpen, stepperen er på plass og låsen har vært åpen lenge nok, låses den igjen
  if (!lockState && stepper.stepsToGo() == 0 && millis() > lockOpenTime + lockOpenTimeTotal) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door locked");

    stepper.move(-stepsPerRevolution / 2);
    lockCloseTime = millis();
    lockState = true;
  }

  //Leser knapp fra IR-mottakeren.
  //Hvis knappen er gyldig og stepperen er på plass, oppdateres koden med riktig verdi
  int button = ReadIR();
  if (button != -1 && lockState && stepper.stepsToGo() == 0) {
    Serial.print("Input: ");
    Serial.println(button);
    userInput[inputIndex++] = button;

    //Sjekker om hele koden er skrevet
    if (inputIndex == codeLength) {
      Serial.print("Kode = ");
      for (int i = 0; i < codeLength; i++) {
        Serial.print(userInput[i]);
      }
      Serial.println("");

      if (CheckCode()) {
        Serial.println("Riktig!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Door unlocked");

        lockState = false;
        stepper.move(stepsPerRevolution / 2);
        lockOpenTime = millis();
      } else {
        Serial.println("FEIL!!!!");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Wrong code!");

        //Timeren må stoppes pga. delt timer mellom buzzer og IR-mottaker
        IrReceiver.stopTimer();
        tone(PIN_BUZ, 200);
        delay(500);
        noTone(PIN_BUZ);
        IrReceiver.restartTimer();
      }
      inputIndex = 0;
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Reading code:");
      lcd.setCursor(0, 1);
      for (int i = 0; i < inputIndex; i++) {
        lcd.print(userInput[i]);
      }
    }
  }
}

//Funksjon for å sjekke at koden gitt av brukeren er riktig
bool CheckCode() {
  for (int i = 0; i < codeLength; i++) {
    if (userInput[i] != correctCode[i]) {
      return false;
    }
  }
  return true;
}

//Leser en verdi fra IR-fjernkontrollen
//Returnerer hvilken knapp som ble trykket (0-9)
//Hvis en udefinert knapp, eller ingen knapp er trykket returneres -1
int ReadIR() {
  static int lastButton = -1;
  static unsigned long lastPressTime = 0;
  const unsigned long debounceTime = 300;

  //Sjekker om det er et signal å lese av på IR-mottakeren
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

//Mapper verdiene lest fra IR-fjernkontrolleren til hvilken knapp som ble trykket
//Udefinerte verdier returnerer -1
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

//Logikken til RFID og servo
void UpdateRFID() {
  static int servoPos = 0;
  static uint32_t servoOpenTime = 0;
  static uint32_t LedLastOnTime = 0;

  if (millis() >= servoOpenTime + servo_open_time_total) {
    servoPos = 0;
  }
  servo.write(servoPos);

  if (millis() >= LedLastOnTime + servo_led_on_time) {
    digitalWrite(PIN_LED_RFID, LOW);
  }

  static uint32_t lastRead = 0;

  if (millis() >= lastRead + RFID_read_interval) {
    if (RC522.isCard()) {
      RC522.readCardSerial();
      Serial.print("Card detected: ");

      for (int i = 0; i < 5; i++) {
        Serial.print(RC522.serNum[i], DEC);
      }
      Serial.println();

      if (CheckSerNum()) {
        digitalWrite(PIN_LED_RFID, LOW);
        servoOpenTime = millis();
        servoPos = 180;

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access granted,");
        lcd.setCursor(0, 1);
        lcd.print("Welcome home!");
      } else {
        digitalWrite(PIN_LED_RFID, HIGH);
        LedLastOnTime = millis();

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access denied!");
      }
    }

    lastRead = millis();
  }
}

//Sjekker serienummeret til den avleste verdien fra RFID med det riktige serienummeret
bool CheckSerNum() {
  for (int i = 0; i < 5; i++) {
    if (RC522.serNum[i] != correctSerNum[i]) {
      return false;
      break;
    }
  }
  return true;
}

//Logikken til LDR og tilhørende LED
void UpdateLED() {
  int val = analogRead(PIN_LDR);

  if (val < 150) {
    digitalWrite(PIN_LED_LDR, HIGH);
  } else {
    digitalWrite(PIN_LED_LDR, LOW);
  }
}