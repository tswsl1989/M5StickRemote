#include <M5StickC.h>
#include <WiFi.h>
#include <WiFiMulti.h>

#include "wifiApp.h"
#include "config.h"

void showWiFi(){
  while (true) {
    M5.update();
    wifiMulti.run();
    M5.Lcd.fillScreen(BLACK);
    if (WiFi.isConnected()) {
      M5.Lcd.setTextColor(GREEN, BLACK);
      M5.Lcd.setTextSize(1);
      M5.Lcd.setCursor(0,0);
      M5.Lcd.print("Connected\n");
      M5.Lcd.setTextColor(WHITE, BLACK);
      M5.Lcd.print("\nSSID:    ");
      M5.Lcd.print(WiFi.SSID());
      M5.Lcd.print("\nRSSI:    ");
      M5.Lcd.print(WiFi.RSSI());
      M5.Lcd.print("\nIP:      ");
      M5.Lcd.print(WiFi.localIP());
      M5.Lcd.print("\nGateway: ");
      M5.Lcd.print(WiFi.gatewayIP());
      M5.Lcd.print("\nNetmask: ");
      M5.Lcd.print(WiFi.subnetMask());
      M5.Lcd.print("\nDNS:     ");
      M5.Lcd.print(WiFi.dnsIP());
    } else {
      M5.Lcd.setTextColor(RED, BLACK);
      M5.Lcd.setCursor(0,0);
      M5.Lcd.print("Unable to Connect");
      M5.Lcd.setTextColor(WHITE, BLACK);
    }
  
    M5.Lcd.setCursor(0,70);
    M5.Lcd.print("MAC: ");
    M5.Lcd.print(WiFi.macAddress());
  
    for (int i=0; i<10; i++) {
      if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed()) {
        return;
      }
      delay(50);
    }
  }
}
