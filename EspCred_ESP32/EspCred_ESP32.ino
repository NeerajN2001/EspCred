#include "wifi_setup.h"

void setup() {
    Serial.begin(115200);
    delay(500);

    WiFiSetup();   // initialize WiFi provisioning
}

void loop() {
    // handle web server client requests and check reset button
    server.handleClient();
    checkResetButton();
}
