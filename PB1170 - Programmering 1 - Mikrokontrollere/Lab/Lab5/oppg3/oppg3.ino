#include <DHT.h>

#define DHTTYPE DHT11
const int DHTpin = 2;

DHT dht(DHTpin, DHTTYPE);

#define TEMP_BUFFER_SIZE 10

void ReadTempToBuf(float* buf, size_t bufsize) {
  if (buf == nullptr) return;

  for (size_t i = 0; i < bufsize; i++) {
    float temp = dht.readTemperature();

    Serial.print("Read ");
    Serial.print(temp);
    Serial.println("°C");

    buf[i] = temp;

    delay(1000);
  }
}

float AverageValueArray(float* buf, size_t bufsize) {
  if (buf == nullptr || bufsize == 0) return 0.0f;

  float sum = 0.0f;

  for (size_t i = 0; i < bufsize; i++) {
    sum += buf[i];
  }

  return sum / bufsize;
}

void PrintArray(float* arr, size_t arrsize, bool newline = true) {
  if (arr == nullptr) return;

  Serial.print("[");
  size_t i = 0;
  for (; i < arrsize - 1; i++) {
    Serial.print(arr[i]);
    Serial.print(", ");
  }
  Serial.print(arr[i]);
  Serial.print("]");

  if (newline) Serial.println("");
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  //Les verdier
  float buf[TEMP_BUFFER_SIZE];
  ReadTempToBuf(buf, TEMP_BUFFER_SIZE);

  //Skriv ut verdiene
  Serial.print("buf = ");
  PrintArray(buf, TEMP_BUFFER_SIZE);

  //Regn ut gjennomsnittet
  Serial.print("Gjennomsnittlig temperatur = ");
  Serial.print(AverageValueArray(buf, TEMP_BUFFER_SIZE));
  Serial.println("°C");
}

void loop() {}