#include "BluetoothSerial.h"

// Check if Bluetooth configs are enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Definindo pinos do NodeMcu para driver Ponte H
// Pinos de controle motor A
int IN1 = 13;   // pwm signal motor 1
int IN2 = 12;   // direction motor 1 = horario, 0 = anti-horario

// Pinos de controle motor B
int IN3 = 14;   // pwm signal motor 2
int IN4 = 27;   // direction motor 2 = horario, 0 = anti-horario

void frente() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
}

void re() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
}

void direita() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void esquerda() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void parar() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}


BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Carrinho Bluetooth ESP32");
  Serial.println("The device started, now you can pair it with bluetooth!");
  //Define os pinos como saida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
 
void loop() {
  if(SerialBT.available()) {
    String cmd = SerialBT.readString();
    cmd.trim();
    if(cmd == "left") {
      Serial.println("esquerda");
      esquerda();
    }
    else if(cmd == "right") {
      Serial.println("direita");
      direita();
    }
    else if(cmd == "front") {
      Serial.println("frente");
      frente();
    }
    else if(cmd == "back") {
      Serial.println("re");
      re();
    }
    else {
      Serial.println("nada");
      parar();
    }
  }
}
