int boton = 8;
int motor = 3;

void setup() {
  pinMode(boton , INPUT);
  pinMode(motor , OUTPUT);
}

void loop() {
  int estadoBoton = digitalRead(boton);
  if (estadoBoton == 1){
    digitalWrite(motor , LOW);
  } else {
    digitalWrite(motor , HIGH);
  }
}
