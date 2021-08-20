#include <Arduino.h>

int pHSense = A0;
float adc_resolution = 1024.0;

void setup()
{
    Serial.begin(9600);
    delay(100);
    Serial.println("cimpleo pH Sense");
}


void ph() {
  int numSamples = 10;
  int buf[numSamples], temp;
  unsigned long int avgValue;
  for (int i = 0; i < numSamples; i++) {
    buf[i] = analogRead(pHSense);
    delay(30);
  }
  
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  
  avgValue = 0;
  // numSamples deve ser maior ou igual a 3
  for (int i = 2; i < numSamples-2; i++)
  avgValue += buf[i];
  float pHVol = (float)( (5.0 / 1024.0) * (avgValue/(numSamples-4)) );

  /*
   * Montei a equação da reta a partir dos seguintes pontos
   * Tensão (V)   x    Soluções com PH
   *    3,02                4
   *    2,50                7
   *    2,02                10
   */   
  float phValue = -6 * pHVol + 22.12;
  Serial.print("PH = ");
  Serial.println(phValue);
}

void loop()
{
    ph();
    delay(3000);
    Serial.println();
}
