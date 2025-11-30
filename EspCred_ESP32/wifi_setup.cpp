#include "wifi_setup.h"

WebServer server(80);
Preferences prefs;

unsigned long pressStart = 0;

// Root page (optional)
void handleRoot() {
    server.send(200, "text/html", "<h3>ESP32 Ready - Send WiFi Credentials</h3>");
}

// Receive WiFi credentials from mobile app
void handleSetCredentials() {
    String ssid = server.arg("ssid");
    String pass = server.arg("pass");

    Serial.println();
    Serial.println("Received WiFi Credentials:");
    Serial.println("SSID: " + ssid);
    Serial.println("PASS: " + pass);

    prefs.begin("wifi", false);
    prefs.putString("ssid", ssid);
    prefs.putString("pass", pass);
    prefs.end();

    server.send(200, "text/plain", "OK");

    delay(300);
    ESP.restart();
}

// Reset credentials via long press
void checkResetButton() {
    if (digitalRead(RESET_PIN) == LOW) {
        if (pressStart == 0) pressStart = millis();

        if (millis() - pressStart > RESET_HOLD_TIME) {
            Serial.println("Button reset → Clearing WiFi");

            prefs.begin("wifi", false);
            prefs.clear();
            prefs.end();

            delay(300);
            ESP.restart();
        }
    } else {
        pressStart = 0;
    }
}

void handleStatus() {
    String json = "{";
    json += "\"ip\":\"" + WiFi.localIP().toString() + "\",";
    json += "\"wifi\":\"" + String(WiFi.status() == WL_CONNECTED ? "connected" : "disconnected") + "\"";
    json += "}";
    server.send(200, "application/json", json);
}

bool connectStoredWiFi() {
    prefs.begin("wifi", true);
    String ssid = prefs.getString("ssid", "");
    String pass = prefs.getString("pass", "");
    prefs.end();

    if (ssid == "" || pass == "") {
        Serial.println("No saved WiFi credentials.");
        return false;
    }

    Serial.println("Trying saved WiFi:");
    Serial.println("SSID: " + ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), pass.c_str());

    for (int i = 0; i < 20; i++) {
        if (WiFi.status() == WL_CONNECTED) break;
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConnected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        return true;
    }

    Serial.println("\nFailed to connect.");
    return false;
}

void startAPMode() {
    Serial.println("Starting AP mode for provisioning...");

    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);

    Serial.print("AP SSID: "); Serial.println(AP_SSID);
    Serial.print("AP PASS: "); Serial.println(AP_PASS);

    server.on("/", handleRoot);
    server.on("/set", HTTP_POST, handleSetCredentials);
    server.on("/status", handleStatus);

    server.begin();
}

void WiFiSetup() {
    Serial.println("Starting WiFi Setup...");
    pinMode(RESET_PIN, INPUT_PULLUP);

    if (connectStoredWiFi()) {
        Serial.println("Using stored WiFi.");
        server.on("/status", handleStatus);
        server.begin();
        return;
    }

    startAPMode();
}
