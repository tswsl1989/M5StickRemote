#include <M5StickC.h>
#include "settingsApp.h"
#include "config.h"

void settingsMenu() {
  int settingsID = 0;
  int refresh = 1;
  while (true) {
    M5.update();
    
    if (M5.BtnB.wasPressed()) {
      settingsID++;
      if (settingsID >= numSettings) {
        settingsID = 0;
      }
      refresh = 1;
    } else if (M5.BtnA.wasPressed()) {
      auto func = settings[settingsID].fn;
      if (func) {
        func();
      } else {
        return;
      }
      refresh = 1;
    }
  
    if (refresh) {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setTextColor(PURPLE, BLACK);
      M5.Lcd.drawCentreString(settings[settingsID].appName, 80, 30, 2);
      refresh = 0;
    }
    
    delay(50);
  }
}

void settingsBrightness() {
  int refresh = 1;
  
  int brightness = prefs.getUChar("brightness", 2);
  while (true) {
    M5.update();
    if (M5.BtnB.wasPressed()) {
      prefs.putUChar("brightness", brightness);
      return;
    }

    if (M5.BtnA.wasPressed()) {
      brightness++;
      if (brightness > 8) {
        brightness = 0;
      }
      M5.Axp.ScreenBreath(brightness+7);
      refresh = 1;
    }
    if (refresh) {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setTextColor(WHITE, BLACK);
      M5.Lcd.drawCentreString("Brightness", 80, 10, 2);
      M5.Lcd.drawCentreString(String(brightness), 80, 30, 2);
      refresh = 0;
    }
  }
}

void settingsRotate() {
  int refresh = 1;
  
  int rotate = prefs.getUChar("rotate", 3);
  while (true) {
    M5.update();
    if (M5.BtnB.wasPressed()) {
      prefs.putUChar("rotate", rotate);
      return;
    }

    if (M5.BtnA.wasPressed()) {
      if (rotate == 3 ) {
        rotate = 1;
      } else {
        rotate = 3;
      }
      M5.Lcd.setRotation(rotate);
      refresh = 1;
    }
    if (refresh) {
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setTextColor(WHITE, BLACK);
      M5.Lcd.drawCentreString("Rotation", 80, 10, 2);
      M5.Lcd.drawCentreString(String(rotate), 80, 30, 2);
      refresh = 0;
    }
  }
}
