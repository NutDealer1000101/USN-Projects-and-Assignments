const int PIN_POT = A0;

#define buflen 10

void ReadPot(int* buf, size_t bufsize) {
  if (buf == nullptr) return;

  for (int i = 0; i < bufsize; i++) {
    int potVal = analogRead(PIN_POT);
    Serial.print("Read ");
    Serial.println(potVal);

    buf[i] = potVal;

    delay(1000);
  }
}

void PrintArray(int* arr, size_t arrlen, bool newline = true) {
  if (arr == nullptr) return;

  Serial.print("[");
  int i = 0;
  for (; i < arrlen - 1; i++) {
    Serial.print(arr[i]);
    Serial.print(", ");
  }
  Serial.print(arr[i]);
  Serial.print("]");

  if (newline) Serial.println("");
}


void setup() {
  Serial.begin(9600);

  pinMode(PIN_POT, INPUT);
}

void loop() {
  int buf[buflen];

  ReadPot(buf, buflen);

  Serial.print("buf = ");
  PrintArray(buf, buflen);
  
  delay(5000);
}