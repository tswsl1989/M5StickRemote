#ifndef HASSAPP_H
#define HASSAPPT_H

#include <WiFiClientSecure.h>

typedef struct {
  String entity;
  String label;
} HASSEntity;

int getState(WiFiClientSecure *wcs, const String &entityName);
bool toggleState(WiFiClientSecure *wcs, const String &entityName);
void drawHASSEntityScreen(int cs, const String label, bool notEntity);
void doHASSClient();
#endif
