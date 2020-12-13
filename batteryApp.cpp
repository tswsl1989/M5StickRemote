#include <M5StickC.h>
#include "batteryApp.h"

void showBattery() {
  while(true) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(BLUE, BLACK);
    M5.Lcd.setCursor(0,0);
    M5.Lcd.setTextSize(1);
    M5.Lcd.print("Battery:  ");
    if (M5.Axp.GetWarningLeve()) {
      M5.Lcd.setTextColor(YELLOW, BLACK);
    } else {
      M5.Lcd.setTextColor(WHITE, BLACK);
    }
    M5.Lcd.printf("%4.3fV %7.3fmA\n\n", M5.Axp.GetBatVoltage(), M5.Axp.GetBatCurrent());
    
    M5.Lcd.setTextColor(BLUE, BLACK);  
    M5.Lcd.print("USB:      ");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("%4.3fV %7.3fmA\n\n", M5.Axp.GetVBusVoltage(), M5.Axp.GetVBusCurrent());
    
    M5.Lcd.setTextColor(BLUE, BLACK);
    M5.Lcd.print("Ext, 5V:  ");
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.printf("%4.3fV %7.3fmA\n\n", M5.Axp.GetVinVoltage(), M5.Axp.GetVinCurrent());
    
    float temp = M5.Axp.GetTempInAXP192();
    M5.Lcd.print("Temp:     ");
    if (temp > 50) {
      M5.Lcd.setTextColor(RED, BLACK);
    } else if (temp > 40) {
      M5.Lcd.setTextColor(YELLOW, BLACK);
    } else {
      M5.Lcd.setTextColor(WHITE, BLACK);
    }
    M5.Lcd.printf(" %02.1fC\n", temp);
    M5.update();
    delay(250);
    if (M5.BtnA.wasPressed() or M5.BtnB.wasPressed()) {
      return;
    }
  }
}
