int a = 9;

void setup() {
  pinMode(a, OUTPUT);
}

void loop() {
  digitalWrite(a, HIGH);
  delay(1000);
  digitalWrite(a, LOW);
  delay(1000);
}
