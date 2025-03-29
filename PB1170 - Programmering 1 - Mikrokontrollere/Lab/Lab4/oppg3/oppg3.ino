void SkrivStjerner(int antall, bool newline = true) {
  for (int i = 0; i < antall; i++) {
    Serial.print("*");
  }
  if (newline) Serial.println("");
}

void SkrivMangeStjerner(int antall) {
  for (int i = 1; i <= antall; i++) {
    SkrivStjerner(i);
  }
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Skriv inn antall linjer: ");

  while (!Serial.available())
    ;
  int antall = Serial.parseInt();

  SkrivMangeStjerner(antall);
}
