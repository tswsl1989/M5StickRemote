#include <M5StickC.h>
#include <ArduinoOTA.h>
#include <ESPmDNS.h>
#include "OTA.h"

void drawOTADefaultScreen() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.drawCentreString("OTA Enabled", 80, 20, 2);
  M5.Lcd.drawCentreString("Host: " + ArduinoOTA.getHostname(), 80, 40, 2);
}

void doOTA() {
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_SPIFFS
      type = "filesystem";
    }
    
    // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextColor(BLUE, BLACK);
    M5.Lcd.setCursor(0,0, 2);
    M5.Lcd.drawCentreString("OTA Update: " + type, 80, 10, 2);
    M5.Lcd.setTextColor(WHITE, BLACK);
    M5.Lcd.setCursor(0, 28, 2);
    M5.Lcd.fillRect(0, 28, 160, 20, BLACK);
    M5.Lcd.drawRect(5, 30, 150, 14, WHITE);
  });
  ArduinoOTA.onEnd([]() {
    M5.Lcd.setTextColor(GREEN, BLACK);
    M5.Lcd.drawCentreString("Update Complete", 80, 60, 2);
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
      M5.Lcd.fillRect(5, 32, (progress / (total / 150)), 10, GREEN);
  });
  ArduinoOTA.onError([](ota_error_t error) {
      drawOTADefaultScreen();
      M5.Lcd.setTextColor(RED, BLACK);
      if (error == OTA_AUTH_ERROR) M5.Lcd.drawCentreString("Auth Failed", 80, 60, 2);
      else if (error == OTA_BEGIN_ERROR) M5.Lcd.drawCentreString("Begin Failed", 80, 60, 2);
      else if (error == OTA_CONNECT_ERROR) M5.Lcd.drawCentreString("Connect Failed", 80, 60, 2);
      else if (error == OTA_RECEIVE_ERROR) M5.Lcd.drawCentreString("Receive Failed", 80, 60, 2);
      else if (error == OTA_END_ERROR) M5.Lcd.drawCentreString("End Failed", 80, 60, 2);
  });
  ArduinoOTA.setHostname("M5StickC");
  ArduinoOTA.begin();

  drawOTADefaultScreen();

  while (true) {
    M5.update();
    ArduinoOTA.handle();
    if (M5.BtnB.wasPressed()) {
      ArduinoOTA.end();
      return;
    }
  }
}
