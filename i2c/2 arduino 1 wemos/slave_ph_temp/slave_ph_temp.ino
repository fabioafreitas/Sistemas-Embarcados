#include <Wire.h>

#define PH_ANALOG_PIN A0
#define NTC_ANALOG_PIN A1

                               
void setup() {                   
  Wire.begin(0x01);                /* join i2c bus with address 8 */
  Wire.onReceive(receiveEvent); /* register receive event */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);           /* start serial for debug */   
  Serial.println("I2C Client - PH, Temp Sensors");                  
}
void loop() {
  delay(1000);
}


/*
 * Obtem os samples de um pino analogico e calcula a média dos valores
 * 
 */
int getSamplesMean(int analogPin) {
  int numSamples = 10;
  int buf[numSamples], temp;
  unsigned long int avgValue;

  // reading analog pin
  for (int i = 0; i < numSamples; i++) {
    buf[i] = analogRead(analogPin);
    delay(50);
  }

  // sorting
  for (int i = 0; i < numSamples-1; i++) {
    for (int j = i + 1; j < numSamples; j++) {
      if (buf[i] > buf[j]) {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
 

  // excluding lower and bigger values
  avgValue = 0;
  for (int i = 1; i < numSamples-1; i++) {
    avgValue += buf[i];
  }

  // mean
  avgValue = avgValue/(numSamples-2);

  return avgValue;
}



float ntcTempValue(int analogPin, bool verbose) {
  int avgValue = getSamplesMean(analogPin);
  float resistance = (10240000/avgValue) - 10000;
  
  // https://en.wikipedia.org/wiki/Steinhart%E2%80%93Hart_equation
  float temp = log(resistance);
  temp = 1 / (0.001129148 + (0.000234125 * temp) + (0.0000000876741 * temp * temp * temp));
  temp = temp - 273.15;

  if(verbose) {
    Serial.println("\nNTC Thermistor 10k");
    Serial.print("analog: ");
    Serial.print(avgValue);
    Serial.print("\tresistance: ");
    Serial.print(resistance);
    Serial.print("\ttemp: ");
    Serial.print(temp);
    Serial.println("ºC\n");
  }
  
  return temp;
}






/*
 * Montei a equação da reta a partir dos seguintes pontos
 * Tensão (V)   x    Soluções com PH
 *    3,02                4
 *    2,50                7
 *    2,02                10
 */
float phValue(int analogPin, bool verbose) {
  int avgValue = getSamplesMean(analogPin);
  
  // Conversão analog para volts
  float pHVol = (float)((5.0 / 1024.0) * avgValue);

  // Calculando pH   
  float ph = -6 * pHVol + 22.12;
  
  if(verbose) {
    Serial.println("\nPH-4502C");
    Serial.print("analog: ");
    Serial.print(avgValue);
    Serial.print("\tph: ");
    Serial.println(ph);
  }
  
  return ph;
}







void receiveEvent(int numBytes) {
  char data[20];
  for(int i = 0; Wire.available(); i++) {
    data[i] = Wire.read();
  }
  Serial.println(data);
}






void requestEvent() {
  float ph = phValue(PH_ANALOG_PIN, true);
  float temp = ntcTempValue(NTC_ANALOG_PIN, true);
  String i2cData = String(ph, 3)+";"+String(temp,2)+";";
  Serial.println("\nI2C - Send Data");
  Serial.print("data: ");
  Serial.println(i2cData);

  int len = i2cData.length()+1;
  char i2cDataBuffer[len];
  i2cData.toCharArray(i2cDataBuffer, len);
  Wire.write(i2cDataBuffer);
}
