#include "config.h"
#include "appMenu.h"

WiFiMulti wifiMulti;

void setup() {
  M5.begin();
  prefs.begin("MStickC");
  for (int n=0; n < numNetworks; n++) {
    wifiMulti.addAP(WiFiSSID[n], WiFiPSK[n]);
  }
  M5.Lcd.setRotation(prefs.getUChar("rotate", 3));
  M5.Axp.ScreenBreath(prefs.getUChar("brightness", 2)+7);
  M5.Lcd.fillScreen(BLACK);
  
  wifiMulti.run();
  if (wifiMulti.run() == WL_CONNECTED) {
    M5.Lcd.setTextColor(GREEN, BLACK);
    M5.Lcd.drawCentreString("Connected to:", 80, 20, 2);
    M5.Lcd.drawCentreString(WiFi.SSID(), 80, 40, 2);
  } else {
    M5.Lcd.setTextColor(RED, BLACK);
    M5.Lcd.drawCentreString("Unable to Connect", 80, 30, 2);
  }
  delay(1000);
}

void loop() {
  mainMenu();
}
