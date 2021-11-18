//https://www.instructables.com/DC-Motor-Controller-With-Two-Relay/



const int relay1 = D2;
const int relay2 = D3;

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void frente() {
  digitalWrite(relay1, HIGH); digitalWrite(relay2, LOW);
  delay(3000);
  digitalWrite(relay1, LOW); digitalWrite(relay2, LOW);
}

void re() {
  digitalWrite(relay1, LOW); digitalWrite(relay2, HIGH);
  delay(3000);
  digitalWrite(relay1, LOW); digitalWrite(relay2, LOW);
}

void loop() {
  
}
