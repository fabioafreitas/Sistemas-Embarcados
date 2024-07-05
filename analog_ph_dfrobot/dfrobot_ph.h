#ifndef _PH_SEN0169_V2_H_
#define _PH_SEN0169_V2_H_

//#define PH_SEN0169_DEBUG_MODE

#include "utils/data_model_util.h"

#ifndef PH_SEN0169V2_ADS_PIN
#define PH_SEN0169V2_ADS_PIN 1
#endif

/*
2.03v = 10800 ads signal = ph 4  \
                      ============>    ph(volts) = 15.2778 - 5.55556 x
1.49v = 7900 ads signal = ph 7   /

0.98v = 5250 ads signal = ph 10
*/
float computePH_SEN0169_V2(float voltage) {
  return 15.2778 - 5.55556*voltage;
}

SensorDataModel getPH_SEN0169_V2(Adafruit_ADS1115 ads) {
  SensorDataModel ph;
  ph.adsSignal = ads.readADC_SingleEnded(PH_SEN0169V2_ADS_PIN);
  ph.voltage = ads.computeVolts(ph.adsSignal);
  ph.valueCalibration1 = computePH_SEN0169_V2(ph.voltage);
  
  #ifdef ORP_SEN0464_DEBUG_MODE
  Serial.print("[PH - DFROBOT] voltage: "); Serial.print(ph.voltage, 3); Serial.print("V\t");
  Serial.print("\n\tads signal: "); Serial.println(ph.adsSignal, 2);
  Serial.print("ph: "); Serial.println(ph.valueCalibration1, 2);
  #endif
  
  return ph;
}



#endif /* _PH_SEN0169_V2_H_ */
