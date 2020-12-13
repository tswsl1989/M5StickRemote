#include <M5StickC.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "config.h"
#include "cert.h" // Should define char * containing root certificate to trust
#include "HASSApp.h"

const String uAgent = "M5StickHASSClient/1.0";
const String AuthHeader = "Bearer " + hassToken;

// Not a header, but the IDE doesn't like .inc
#include "HASSEntities.h"

int getState(WiFiClientSecure *wcs, const String &entityName) {
  HTTPClient client;
  if (!client.begin(*wcs, serverName, 443, "/api/states/"+entityName, true)) {
    return -1;
  }
  client.setUserAgent(uAgent);
  client.addHeader("Authorization", AuthHeader);
  int s = client.GET();

  bool eState = false;
  if (s < 0) {
    return -1;
  } else {
    DynamicJsonDocument jd(1024);
    String resp = client.getString();
    //Serial.println(resp);
    DeserializationError err = deserializeJson(jd, resp);
    if (err) {
      Serial.println(err.c_str());
      return -1;
    }
    //serializeJsonPretty(jd, Serial);
    const char *es = jd["state"];
    //Serial.println(es);
    //M5.Lcd.println(es);
    if (strcmp(es, "off") == 0) {
      return 0;
    } else if (strcmp(es, "on") == 0) {
      return 1;
    } else {
      M5.Lcd.print("Odd state: ");
      M5.Lcd.print(es);
      delay(1000); 
      return -1;
    }
  }
  // Shouldn't get here, so return error
  return -1;
}

bool toggleState(WiFiClientSecure *wcs, const String &entityName) {
  HTTPClient client;
  if (!client.begin(*wcs, serverName, 443, "/api/services/homeassistant/toggle", true)) {
    return -1;
  }
  client.setUserAgent(uAgent);
  client.addHeader("Authorization", AuthHeader);
  String payload = "{\"entity_id\": \"" + entityName + "\"}";
  int s = client.POST(payload);
  if (s < 0) {
    return -1;
  } else {
    return getState(wcs, entityName);
  }
  return -1;
}

void drawHASSEntityScreen(int cs, const String label, bool notEntity) {
    M5.Lcd.fillScreen(BLACK);
    if (cs == 1) {
      M5.Lcd.setTextColor(GREEN, BLACK);
    } else if (cs == 0) {
      M5.Lcd.setTextColor(RED, BLACK);
    } else if (cs < 0) {
      if (notEntity) {
        M5.Lcd.setTextColor(BLUE, BLACK);
      } else {
        M5.Lcd.setTextColor(PURPLE, BLACK);
      }
    }
    M5.Lcd.drawCentreString(label, 80, 30, 2);
}

void doHASSClient() {
  WiFiClientSecure *wcs = new WiFiClientSecure;
  if (!wcs) {
    Serial.println("Unable to set up secure client");
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.print("Unable to set up secure client");
    delay(5000);
    return;
  }
  wcs->setCACert(cert);

  int currE = 0;
  while (true) {
    int cs = -1;
    cs = getState(wcs, HASSEntities[currE].entity);
    drawHASSEntityScreen(cs, HASSEntities[currE].label, HASSEntities[currE].entity == "");
    while (true) {
      M5.update();
      if (M5.BtnA.wasPressed()) {
        if (HASSEntities[currE].entity == "") {
          return;
        } else {
          cs = toggleState(wcs, HASSEntities[currE].entity);
          drawHASSEntityScreen(cs, HASSEntities[currE].label, false);
        }
      }
      if (M5.BtnB.pressedFor(2000)) {
        return;
      }
      if (M5.BtnB.wasPressed()) {
        currE++;
        if (currE >= numHASSEntities) {
          currE = 0;
        }
        break;
      }
    }
  }
}
