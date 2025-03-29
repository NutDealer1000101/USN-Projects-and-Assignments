int abs1(int n) {
  //return abs(n);
  return n < 0 ? -n : n;
}

void abs2(int* pn) {
  *pn = abs1(*pn);
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  int tall1 = -2;
  int tall2 = -7;

  tall1 = abs1(tall1);
  abs2(&tall2);

  Serial.print(tall1);
  Serial.print(tall2);
}