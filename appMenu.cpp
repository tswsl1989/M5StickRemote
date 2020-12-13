#include <M5StickC.h>
#include "appMenu.h"

void mainMenu() {
  static int currentApp = 0;
  int refresh = 1;
  while (true) {
    M5.update();
    
    if (M5.BtnA.wasPressed()) {
      apps[currentApp].fn();
      refresh = 1;
    }

    if (M5.BtnB.wasPressed()) {
      currentApp++;
      if (currentApp >= numApps) {
        currentApp = 0;
      }
      refresh = 1;
    } 
 
    if (refresh) {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setTextColor(BLUE, BLACK);
      M5.Lcd.drawCentreString(apps[currentApp].appName, 80, 30, 2);
      refresh = 0;
    }
    
    delay(50);
  }
}

void confirmOff() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(RED, BLACK);
  M5.Lcd.drawCentreString("Hold A to power off", 80, 20, 1);
  M5.Lcd.setTextColor(BLUE, BLACK);
  M5.Lcd.drawCentreString("Press B to return", 80, 50, 1);
  while (true) {
    M5.update();
    if (M5.BtnA.pressedFor(2000)) {
      // Shuts off power - cannot wake up from software
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setTextColor(RED, BLACK);
      M5.Lcd.drawCentreString("Powering off...", 80, 30, 1);
      delay(2000);
      M5.Axp.PowerOff();   
    }
    if (M5.BtnB.wasPressed()) {
      return;
    }
  }
}
