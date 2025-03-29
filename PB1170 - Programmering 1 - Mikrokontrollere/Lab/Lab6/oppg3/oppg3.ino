#include <DHT.h>

const int PIN_BUT_1 = 2;
const int PIN_BUT_2 = 3;
const int PIN_DHT = 5;

const int debounce_delay = 200;

#define DHTTYPE DHT11
DHT dht(PIN_DHT, DHTTYPE);

struct TempHum {
  float temp;
  float hum;
};

#define TEMPHUM_ARRAY_SIZE 100
volatile unsigned int currentReadingArraySize = 0;
TempHum readings[TEMPHUM_ARRAY_SIZE];

volatile bool doReadValues = false;
volatile bool doPrintAvg = false;

void setup() {
  Serial.begin(9600);

  dht.begin();

  pinMode(PIN_BUT_1, INPUT_PULLUP);
  pinMode(PIN_BUT_2, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(PIN_BUT_1), ReadValues, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_BUT_2), PrintAverage, RISING);
}

void loop() {
  if (doReadValues) {
    doReadValues = false;
    
    if (currentReadingArraySize >= TEMPHUM_ARRAY_SIZE) return;

    float t = dht.readTemperature();
    float h = dht.readHumidity();
    //float t = 5.0f * (float)currentReadingArraySize;
    //float h = 3.0f * (float)currentReadingArraySize;
    readings[currentReadingArraySize] = { t, h };

    Serial.print("Index: ");
    Serial.print(currentReadingArraySize);
    Serial.print("\t temp: ");
    Serial.print(readings[currentReadingArraySize].temp);
    Serial.print("\t hum: ");
    Serial.println(readings[currentReadingArraySize].hum);

    currentReadingArraySize++;
  }
  if (doPrintAvg) {
    doPrintAvg = false;

    TempHum avg = CalcAvgTempHum(readings, currentReadingArraySize);

    Serial.print("Size: ");
    Serial.print(currentReadingArraySize);
    Serial.print("\tAvg. temp = ");
    Serial.print(avg.temp);
    Serial.print("\tAvg. hum = ");
    Serial.println(avg.hum);
  }
}

TempHum CalcAvgTempHum(TempHum values[], unsigned int length) {
  TempHum sum = { 0.0f, 0.0f };

  if (length != 0) {
    for (unsigned int i = 0; i < length; i++) {
      sum.temp += values[i].temp;
      sum.hum += values[i].hum;
    }
    sum.temp /= (float)length;
    sum.hum /= (float)length;
  }

  return sum;
}

void ReadValues() {
  static size_t lastInterrupt = 0;
  if (millis() < lastInterrupt + debounce_delay) return;
  lastInterrupt = millis();

  doReadValues = true;
}

void PrintAverage() {
  static size_t lastInterrupt = 0;
  if (millis() < lastInterrupt + debounce_delay) return;
  lastInterrupt = millis();

  doPrintAvg = true;
}