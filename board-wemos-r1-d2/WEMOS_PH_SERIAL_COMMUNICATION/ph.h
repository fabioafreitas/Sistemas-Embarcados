#define CALIBRATION 23.00
#define BUFFER_SIZE 10

int phBuffer[BUFFER_SIZE];
const int analogInPin = A0;

void sortIntList(int* list, int listSize) {
  int temp;
  for (int i = 0; i < listSize-1; i++) {
    for (int j = i + 1; j < listSize; j++) {
      if (list[i] > list[j]) {
        temp = list[i];
        list[i] = list[j];
        list[j] = temp;
      }
    }
  }
}

float read_ph() {
  for (int i = 0; i < BUFFER_SIZE; i++) {
    phBuffer[i] = analogRead(analogInPin);
    delay(30);
  }
  sortIntList(phBuffer, BUFFER_SIZE);
  unsigned long int avgValue = 0;
  for (int i = 2; i < BUFFER_SIZE-2; i++) {
    avgValue += phBuffer[i];
  }
  float pHVol = (float)avgValue * 3.3 / 1024 / 6; //dividir por 3.3, pois estou usando um regulador de tensao 5v 3.3v
  float phValue = -5.70 * pHVol + CALIBRATION;
  //Serial.print("PH = ");
  //Serial.println(phValue);  
  return phValue;
}
 
