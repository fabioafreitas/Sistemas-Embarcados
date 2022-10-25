# 1 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
/***************************************************

  DFRobot Gravity: Analog Dissolved Oxygen Sensor / Meter Kit for Arduino

  <https://www.dfrobot.com/wiki/index.php/Gravity:_Analog_Dissolved_Oxygen_Sensor_SKU:SEN0237>



 ***************************************************

  This example reads the concentration of dissolved oxygen in water.

  The saturated oxygen calibration is available by UART commends with NL & CR:

  calibration  ----  enter the calibration mode

  satcal       ----  calibrate the parameters with saturated oxygen value

  exit         ----  exit the calibration mode



  Created 2017-5-22

  By Jason <jason.ling@dfrobot.com@dfrobot.com>



  GNU Lesser General Public License.

  See <http://www.gnu.org/licenses/> for details.

  All above must be included in any redistribution

 ****************************************************/
# 20 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
/***********Notice and Trouble shooting***************

  1. This code is tested on Arduino Uno and Leonardo with Arduino IDE 1.0.5 r2 and 1.8.2.

  2. More details, please click this link: <https://www.dfrobot.com/wiki/index.php/Gravity:_Analog_Dissolved_Oxygen_Sensor_SKU:SEN0237>

****************************************************/
# 25 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
# 26 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 2
# 27 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 2



float temperature = 0;
int ThermistorPin = A1;

int Vo;
float Voo;

float doValue; //current dissolved oxygen value, unit; mg/L





char receivedBuffer[20 + 1]; // store the serial command
byte receivedBufferIndex = 0;


int analogBuffer[30 /* sum of sample point*/]; //store the analog value in the array, readed from ADC
int analogBufferTemp[30 /* sum of sample point*/];
int analogBufferIndex = 0, copyIndex = 0;



float SaturationDoVoltage, SaturationDoTemperature;
float averageVoltage;

const float SaturationValueTab[41] 
# 55 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                                  __attribute__((__progmem__)) 
# 55 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                                          = { //saturation dissolved oxygen concentrations at various temperatures
  14.46, 14.22, 13.82, 13.44, 13.09,
  12.74, 12.42, 12.11, 11.81, 11.53,
  11.26, 11.01, 10.77, 10.53, 10.30,
  10.08, 9.86, 9.66, 9.46, 9.27,
  9.08, 8.90, 8.73, 8.57, 8.41,
  8.25, 8.11, 7.96, 7.82, 7.69,
  7.56, 7.43, 7.30, 7.18, 7.07,
  6.95, 6.84, 6.73, 6.63, 6.53,
  6.41,
};

void setup()
{
  Serial.begin(115200);
  pinMode(A0 /*dissolved oxygen sensor analog output pin to arduino mainboard*/, 0x0);
  readDoCharacteristicValues(); //read Characteristic Values calibrated from the EEPROM
}

void loop()
{
  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint > 30U) //every 30 milliseconds,read the analog value from the ADC
  {
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(A0 /*dissolved oxygen sensor analog output pin to arduino mainboard*/); //read the analog value and store into the buffer
    analogBufferIndex++;
    if (analogBufferIndex == 30 /* sum of sample point*/)
      analogBufferIndex = 0;
  }

  static unsigned long tempSampleTimepoint = millis();
  if (millis() - tempSampleTimepoint > 500U) // every 500 milliseconds, read the temperature
  {
    tempSampleTimepoint = millis();
    // temperature sensor code starts here
    // averaging is not necessary, but it gives more precise values
    float average = 0;
    for (int i = 0; i < 10; i++) {
      Vo = analogRead(ThermistorPin);
      average = average + Vo;
      delay(10);
    }
    Voo = average / 10;
    //following equation is found through thermistor calibration
    temperature = 72.75782 - 0.14694 * Vo + 0.0000326743 * Vo * Vo;
    // temperature sensor code ends here
  }

  static unsigned long printTimepoint = millis();
  if (millis() - printTimepoint > 1000U)
  {
    printTimepoint = millis();
    for (copyIndex = 0; copyIndex < 30 /* sum of sample point*/; copyIndex++)
    {
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
    }
    averageVoltage = getMedianNum(analogBufferTemp, 30 /* sum of sample point*/) * (float)5000 /*for arduino uno, the ADC reference is the AVCC, that is 5000mV(TYP)*/ / 1024.0; // read the value more stable by the median filtering algorithm
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 113 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 113 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                "  Voltage:"
# 113 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                ); &__c[0];}))
# 113 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                )));
    Serial.print(averageVoltage, 1);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 115 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 115 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                "  Temperature:"
# 115 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                ); &__c[0];}))
# 115 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                )));
    Serial.print(temperature, 1);
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 117 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 117 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                "^C"
# 117 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                ); &__c[0];}))
# 117 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                )));
    doValue = 
# 118 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
             (__extension__({ uint16_t __addr16 = (uint16_t)((uint16_t)(
# 118 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
             &SaturationValueTab[0] + (int)(SaturationDoTemperature)
# 118 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
             )); float __result; __asm__ __volatile__ ( "lpm %A0, Z+" "\n\t" "lpm %B0, Z+" "\n\t" "lpm %C0, Z+" "\n\t" "lpm %D0, Z" "\n\t" : "=r" (__result), "=z" (__addr16) : "1" (__addr16) ); __result; })) 
# 118 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                                                                                            * averageVoltage / SaturationDoVoltage ;
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 119 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 119 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                ",  DO Value:"
# 119 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                ); &__c[0];}))
# 119 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                )));
    Serial.print(doValue, 1);
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 121 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 121 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                  "mg/L"
# 121 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                  ); &__c[0];}))
# 121 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                  )));
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
# 161 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3 4
                                              __null
# 161 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                                                  )
    modeIndex = 1;
  else if (strstr(receivedBuffer, "EXIT") != 
# 163 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3 4
                                            __null
# 163 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                                                )
    modeIndex = 3;
  else if (strstr(receivedBuffer, "SATCAL") != 
# 165 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3 4
                                              __null
# 165 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
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
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 179 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 179 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                      "Command Error"
# 179 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                      ); &__c[0];}))
# 179 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                      )));
      break;

    case 1:
      enterCalibrationFlag = 1;
      doCalibrationFinishFlag = 0;
      Serial.println();
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 186 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 186 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                    ">>>Enter Calibration Mode<<<"
# 186 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                    ); &__c[0];}))
# 186 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                    )));
      Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 187 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                    (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 187 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                    ">>>Please put the probe into the saturation oxygen water! <<<"
# 187 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                    ); &__c[0];}))
# 187 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                    )));
      Serial.println();
      break;

    case 2:
      if (enterCalibrationFlag)
      {
        Serial.println();
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 195 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 195 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                      ">>>Saturation Calibration Finish!<<<"
# 195 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                      ); &__c[0];}))
# 195 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                      )));
        Serial.println();
        {int i = 0; byte *pp = (byte*)&(averageVoltage);for(; i < sizeof(averageVoltage); i++) EEPROM.write(12 /*the address of the Saturation Oxygen voltage stored in the EEPROM*/+i, pp[i]);};
        {int i = 0; byte *pp = (byte*)&(temperature);for(; i < sizeof(temperature); i++) EEPROM.write(16 /*the address of the Saturation Oxygen temperature stored in the EEPROM*/+i, pp[i]);};
        SaturationDoVoltage = averageVoltage;
        SaturationDoTemperature = temperature;
        doCalibrationFinishFlag = 1;
      }
      break;

    case 3:
      if (enterCalibrationFlag)
      {
        Serial.println();
        if (doCalibrationFinishFlag)
          Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 210 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 210 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                      ">>>Calibration Successful"
# 210 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                      ); &__c[0];}))
# 210 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                      )));
        else
          Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 212 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 212 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                      ">>>Calibration Failed"
# 212 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                      ); &__c[0];}))
# 212 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                      )));
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 213 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 213 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                      ",Exit Calibration Mode<<<"
# 213 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino" 3
                      ); &__c[0];}))
# 213 "c:\\Users\\fbioa\\Desktop\\Dissolved_oxygen\\Dissolved_oxygen.ino"
                      )));
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

void readDoCharacteristicValues(void)
{
  {int i = 0; byte *pp = (byte*)&(SaturationDoVoltage);for(; i < sizeof(SaturationDoVoltage); i++) pp[i]=EEPROM.read(12 /*the address of the Saturation Oxygen voltage stored in the EEPROM*/+i);};
  {int i = 0; byte *pp = (byte*)&(SaturationDoTemperature);for(; i < sizeof(SaturationDoTemperature); i++) pp[i]=EEPROM.read(16 /*the address of the Saturation Oxygen temperature stored in the EEPROM*/+i);};
  if (EEPROM.read(12 /*the address of the Saturation Oxygen voltage stored in the EEPROM*/) == 0xFF && EEPROM.read(12 /*the address of the Saturation Oxygen voltage stored in the EEPROM*/ + 1) == 0xFF && EEPROM.read(12 /*the address of the Saturation Oxygen voltage stored in the EEPROM*/ + 2) == 0xFF && EEPROM.read(12 /*the address of the Saturation Oxygen voltage stored in the EEPROM*/ + 3) == 0xFF)
  {
    SaturationDoVoltage = 1127.6; //default voltage:1127.6mv
    {int i = 0; byte *pp = (byte*)&(SaturationDoVoltage);for(; i < sizeof(SaturationDoVoltage); i++) EEPROM.write(12 /*the address of the Saturation Oxygen voltage stored in the EEPROM*/+i, pp[i]);};
  }
  if (EEPROM.read(16 /*the address of the Saturation Oxygen temperature stored in the EEPROM*/) == 0xFF && EEPROM.read(16 /*the address of the Saturation Oxygen temperature stored in the EEPROM*/ + 1) == 0xFF && EEPROM.read(16 /*the address of the Saturation Oxygen temperature stored in the EEPROM*/ + 2) == 0xFF && EEPROM.read(16 /*the address of the Saturation Oxygen temperature stored in the EEPROM*/ + 3) == 0xFF)
  {
    SaturationDoTemperature = 25; //default temperature is 25^C
    {int i = 0; byte *pp = (byte*)&(SaturationDoTemperature);for(; i < sizeof(SaturationDoTemperature); i++) EEPROM.write(16 /*the address of the Saturation Oxygen temperature stored in the EEPROM*/+i, pp[i]);};
  }
}
