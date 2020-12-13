#ifndef SETTINGSAPP_H
#define SETTINGSAPP_H

// Functionally identical to App in apps.h, but avoids the circular dependency
typedef struct {
  char *appName;
  void (*fn)();
} Settings;

void settingsMenu();
void settingsBrightness();
void settingsRotate();

const int numSettings = 3;
const Settings settings[numSettings] = {
  {"Brightness", settingsBrightness},
  {"Rotation", settingsRotate},
  {"Exit", 0}
};
#endif
