#include <U8g2lib.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.drawStr(0,  7, "Hello world!");
  u8g2.drawStr(0, 17, "OLED screen TEST");
  u8g2.drawStr(0, 27, "with U8g2lib");
  u8g2.sendBuffer();
}

void loop() {
  // put your main code here, to run repeatedly:

}
