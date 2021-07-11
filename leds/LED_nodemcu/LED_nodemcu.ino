// Neste caso não é necessário resistor, pois o nodemcu trabalha com 3.3v

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
