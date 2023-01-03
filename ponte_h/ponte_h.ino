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
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  delay(20);
 /*
 //Gira o Motor A no sentido horario
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, LOW);
 delay(2000); //aguarda 2s
 
 //Para o motor A
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 delay(500);//aguarda 500 ms

  //Gira o Motor A no sentido anti-horario
 digitalWrite(IN1, LOW);
 digitalWrite(IN2, HIGH);
 delay(2000); //aguarda 2s
 
 //Para o motor A
 digitalWrite(IN1, HIGH);
 digitalWrite(IN2, HIGH);
 delay(500); //aguarda 500 ms

 

 //Gira o Motor B no sentido horario
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, LOW);
 delay(2000); //aguarda 2s
 
 //Para o motor B
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
 delay(500);//aguarda 500 ms
 
 //Gira o Motor B no sentido anti-horario
 digitalWrite(IN3, LOW);
 digitalWrite(IN4, HIGH);
 delay(2000);//aguarda 2s
 
 //Para o motor B
 digitalWrite(IN3, HIGH);
 digitalWrite(IN4, HIGH);
 delay(500); //aguarda 500ms
 */
}
