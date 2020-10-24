int led = D3;
int led2 = D8;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  digitalWrite(led, HIGH);
  digitalWrite(led2, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
  digitalWrite(led2, LOW);
  delay(2000);
}
