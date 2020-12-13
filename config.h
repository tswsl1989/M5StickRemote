#ifndef CONFIG_H
#define CONFIG_H
#include <M5StickC.h>

#include <WiFi.h>
#include <WiFiMulti.h>

extern WiFiMulti wifiMulti;

#include <Preferences.h>
extern Preferences prefs;

#define numNetworks 3
extern const char *WiFiSSID[numNetworks];
extern const char *WiFiPSK[numNetworks];

extern const String hassToken;
extern const String serverName;

#endif
