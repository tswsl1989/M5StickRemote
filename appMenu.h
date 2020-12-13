#ifndef APPMENU_H
#define APPMENU_H

typedef struct {
  char *appName;
  void (*fn)();
} App;

void mainMenu();
void confirmOff();

#include "HASSApp.h"
#include "batteryApp.h"
#include "settingsApp.h"
#include "wifiApp.h"
#include "OTA.h"

const int numApps = 6;
const App apps[numApps] = {
  {"Home Assistant", doHASSClient},
  {"WiFi", showWiFi},
  {"Battery", showBattery},
  {"Settings", settingsMenu},
  {"OTA Update", doOTA},
  {"Power", confirmOff}
};
#endif
