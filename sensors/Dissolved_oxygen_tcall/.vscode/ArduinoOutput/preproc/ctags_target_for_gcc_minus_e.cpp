# 1 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\Dissolved_oxygen_tcall.ino"


# 4 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\Dissolved_oxygen_tcall.ino" 2
# 5 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\Dissolved_oxygen_tcall.ino" 2
# 6 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\Dissolved_oxygen_tcall.ino" 2






float temperature = 0;
float doValue; //current dissolved oxygen value, unit; mg/L


char receivedBuffer[20 + 1]; // store the serial command
byte receivedBufferIndex = 0;


int analogBuffer[30 /* sum of sample point*/]; //store the analog value in the array, readed from ADC
int analogBufferTemp[30 /* sum of sample point*/];
int analogBufferIndex = 0, copyIndex = 0;

float SaturationDoVoltage, SaturationDoTemperature;
float averageVoltage;

// const float SaturationValueTab[41] = {      //saturation dissolved oxygen concentrations at various temperatures
//   14.46, 14.22, 13.82, 13.44, 13.09,
//   12.74, 12.42, 12.11, 11.81, 11.53,
//   11.26, 11.01, 10.77, 10.53, 10.30,
//   10.08, 9.86,  9.66,  9.46,  9.27,
//   9.08,  8.90,  8.73,  8.57,  8.41,
//   8.25,  8.11,  7.96,  7.82,  7.69,
//   7.56,  7.43,  7.30,  7.18,  7.07,
//   6.95,  6.84,  6.73,  6.63,  6.53,
//   6.41,
// };

const float SaturationValueTab[41] = { //saturation dissolved oxygen concentrations at various temperatures
  15.26, 15.06, 14.86, 14.66, 14.46,
  14.22, 13.82, 13.44, 13.09, 12.74,
  12.42, 12.11, 11.81, 11.53, 11.26,
  11.01, 10.77, 10.53, 10.30, 10.08,
  9.86, 9.66, 9.46, 9.27, 9.08,
  8.90, 8.73, 8.57, 8.41, 8.25,
  8.11, 7.96, 7.82, 7.69, 7.56,
  7.43, 7.30, 7.18, 7.07, 6.95,
  6.84,
  };


void setup()
{
  Serial.begin(115200);
  initTemperatureDS18B20();
  initAnalogDigitalConverter();
}

void loop()
{
  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint > 30U) //every 30 milliseconds,read the analog value from the ADC
  {
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = ads.readADC_SingleEnded(2);
    analogBufferIndex++;
    if (analogBufferIndex == 30 /* sum of sample point*/)
      analogBufferIndex = 0;
  }

  static unsigned long tempSampleTimepoint = millis();
  if (millis() - tempSampleTimepoint > 500U) // every 500 milliseconds, read the temperature
  {
    tempSampleTimepoint = millis();
    float average = 0;
    for (int i = 0; i < 10; i++) {
      average = average + getTempDS18B20();
      delay(10);
    }
    temperature = average / 10;
  }

  static unsigned long printTimepoint = millis();
  if (millis() - printTimepoint > 1000U)
  {
    printTimepoint = millis();
    for (copyIndex = 0; copyIndex < 30 /* sum of sample point*/; copyIndex++)
    {
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    }
    averageVoltage = ads.computeVolts(getMedianNum(analogBufferTemp, 30 /* sum of sample point*/)) * 1000; //CONVERT IN MILIVOLTS MULTIPLY BY 1000
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("  Voltage:")))));
    Serial.print(averageVoltage, 1);
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("  Temperature:")))));
    Serial.print(temperature, 1);
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>(("^C")))));
    doValue = SaturationValueTab[(int)(SaturationDoTemperature)] * averageVoltage / SaturationDoVoltage ;
    Serial.print(((reinterpret_cast<const __FlashStringHelper *>((",  DO Value:")))));
    Serial.print(doValue, 1);
    Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("mg/L")))));
  }

  if (serialDataAvailable() > 0)
  {
    byte modeIndex = uartParse(); //parse the uart command received
    doCalibration(modeIndex); // If the correct calibration command is received, the calibration function should be called.
  }

}

boolean serialDataAvailable(void)
{
  char receivedChar;
  static unsigned long receivedTimeOut = millis();
  while ( Serial.available() > 0 )
  {
    if (millis() - receivedTimeOut > 500U)
    {
      receivedBufferIndex = 0;
      memset(receivedBuffer, 0, (20 + 1));
    }
    receivedTimeOut = millis();
    receivedChar = Serial.read();
    if (receivedChar == '\n' || receivedBufferIndex == 20)
    {
      receivedBufferIndex = 0;
      strupr(receivedBuffer);
      return true;
    } else {
      receivedBuffer[receivedBufferIndex] = receivedChar;
      receivedBufferIndex++;
    }
  }
  return false;
}

byte uartParse()
{
  byte modeIndex = 0;
  if (strstr(receivedBuffer, "CALIBRATION") != 
# 140 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\Dissolved_oxygen_tcall.ino" 3 4
                                              __null
# 140 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\Dissolved_oxygen_tcall.ino"
                                                  )
    modeIndex = 1;
  else if (strstr(receivedBuffer, "EXIT") != 
# 142 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\Dissolved_oxygen_tcall.ino" 3 4
                                            __null
# 142 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\Dissolved_oxygen_tcall.ino"
                                                )
    modeIndex = 3;
  else if (strstr(receivedBuffer, "SATCAL") != 
# 144 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\Dissolved_oxygen_tcall.ino" 3 4
                                              __null
# 144 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen_tcall\\Dissolved_oxygen_tcall.ino"
                                                  )
    modeIndex = 2;
  return modeIndex;
}

void doCalibration(byte mode)
{
  char *receivedBufferPtr;
  static boolean doCalibrationFinishFlag = 0, enterCalibrationFlag = 0;
  float voltageValueStore;
  switch (mode)
  {
    case 0:
      if (enterCalibrationFlag)
        Serial.println(((reinterpret_cast<const __FlashStringHelper *>(("Command Error")))));
      break;

    case 1:
      enterCalibrationFlag = 1;
      doCalibrationFinishFlag = 0;
      Serial.println();
      Serial.println(((reinterpret_cast<const __FlashStringHelper *>((">>>Enter Calibration Mode<<<")))));
      Serial.println(((reinterpret_cast<const __FlashStringHelper *>((">>>Please put the probe into the saturation oxygen water! <<<")))));
      Serial.println();
      break;

    case 2:
      if (enterCalibrationFlag)
      {
        Serial.println();
        Serial.println(((reinterpret_cast<const __FlashStringHelper *>((">>>Saturation Calibration Finish!<<<")))));
        Serial.println();
        SaturationDoVoltage = averageVoltage;
        SaturationDoTemperature = temperature;
        doCalibrationFinishFlag = 1;
        Serial.print("SaturationDoVoltage = ");
        Serial.println(averageVoltage);
        Serial.print("SaturationDoTemperature = ");
        Serial.println(temperature);
      }
      break;

    case 3:
      if (enterCalibrationFlag)
      {
        Serial.println();
        if (doCalibrationFinishFlag)
          Serial.print(((reinterpret_cast<const __FlashStringHelper *>((">>>Calibration Successful")))));
        else
          Serial.print(((reinterpret_cast<const __FlashStringHelper *>((">>>Calibration Failed")))));
        Serial.println(((reinterpret_cast<const __FlashStringHelper *>((",Exit Calibration Mode<<<")))));
        Serial.println();
        doCalibrationFinishFlag = 0;
        enterCalibrationFlag = 0;
      }
      break;
  }
}

int getMedianNum(int bArray[], int iFilterLen)
{
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
  {
    bTab[i] = bArray[i];
  }
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++)
  {
    for (i = 0; i < iFilterLen - j - 1; i++)
    {
      if (bTab[i] > bTab[i + 1])
      {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}
