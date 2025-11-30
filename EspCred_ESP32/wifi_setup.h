#ifndef WIFI_SETUP_H
#define WIFI_SETUP_H

#include <WiFi.h>
#include <WebServer.h>
#include <Preferences.h>

// AP settings
#define AP_SSID "ESP32_Setup"
#define AP_PASS "12345678"

// Reset button
#define RESET_PIN 2            // your GPIO
#define RESET_HOLD_TIME 3000   // 3 sec

extern WebServer server;
extern Preferences prefs;

void WiFiSetup();
void handleStatus();
void checkResetButton();

#endif
