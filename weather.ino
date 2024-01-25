#include <Wire.h>
#include "SparkFunBME280.h"

BME280 bme280;

#include <Mhz19.h>

Mhz19 mhz19;

#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(115200);

  Wire.begin();
  bme280.setI2CAddress(0x76);
  if(bme280.beginI2C() == false) Serial.println("Sensor connect failed");

  Serial1.begin(9600);
  while(Serial1.available()){
    delay(2);
  }
  mhz19.begin(&Serial1);
  mhz19.setMeasuringRange(Mhz19MeasuringRange::Ppm_5000);
  mhz19.enableAutoBaseCalibration();
  
  u8g2.begin();

  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(0,  7, "CO2 Sensor");
  u8g2.drawStr(0, 17, "Preheating...");
  u8g2.sendBuffer();

  while (!mhz19.isReady()) {
    delay(50);
  }
}

void loop() {
  float temp = bme280.readTempC();
  float hum = bme280.readFloatHumidity();
  float press = bme280.readFloatPressure() / 100.0;

  auto carbonDioxide = mhz19.getCarbonDioxide();
  
  char buf[30];
  char s[7];

  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);

  dtostrf(temp, 5, 2, s);
  sprintf(buf, "%s C", s);
  u8g2.drawStr(0,  7, buf);

  dtostrf(hum, 5, 2, s);
  sprintf(buf, "%s %%", s);
  u8g2.drawStr(0, 17, buf);

  dtostrf(press, 6, 1, s);
  sprintf(buf, "%s hPa", s);
  u8g2.drawStr(0, 27, buf);

  u8g2.setFont(u8g2_font_crox4h_tf);
  sprintf(buf, "%4d ppm", (int)carbonDioxide);
  u8g2.drawStr(45, 15, buf);

  u8g2.sendBuffer();

  delay(5000);
}
