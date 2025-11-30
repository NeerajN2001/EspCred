# 📡 EspCred – ESP32 WiFi Credential Sender

This project provides a simple, secure, and user-friendly way to provision WiFi credentials (SSID and Password) to an ESP32 device using a dedicated Android application. It's ideal for IoT devices that need a quick and easy initial network setup without hardcoding or complex serial configurations.

# 📦 Project Structure

The main repository contains the following components:

<pre>
Main Folder/
 ├── EspCred_App/       → Android app project
 ├── EspCred_ESP_Code/  → ESP32 Arduino
 └── README.md          → This guide
</pre>

---

# 📱 How to Use the EspCred Android App

Follow these steps to configure your ESP32 device with your home WiFi network.

## 1. Install the APK
Copy the EspCred.apk file to your Android phone.  
Tap the file to install.   
If installation is blocked, you may need to enable installation from unknown sources:   
Settings → Apps → Install unknown apps → Allow (This usually only needs to be enabled once.)

## 2. Open the App
The application screen is simple, featuring two input fields and a button:   
- WiFi SSID  
- WiFi Password  
- Send Credentials button

## 3. Connect Your Phone to the ESP32 Setup WiFi
The ESP32 starts in Access Point (AP) mode, creating its own temporary network.  
On your phone, navigate to: Settings → WiFi.  
Connect to the network named: `ESP_Setup`  
The default password is: `12345678`

## 4. Enter Your Home WiFi Details
In the EspCred app, enter the actual `SSID` and `Password` for the network you want the ESP32 to connect to (e.g., your home router).

## 5. Press Send Credentials
Tap the Send Credentials button.  
You will see a confirmation message: `Credentials Sent!`  
The ESP32 will automatically reboot, erase the AP mode, and attempt to connect to the provided WiFi network.  
Verification: If successful, open your Arduino Serial Monitor (Baud Rate 115200) to see the connection log:

Connected to WiFi  
IP Address: xxx.xxx.xxx.xxx


## 6. Factory Reset (Erase Stored Credentials)
If you need to configure the ESP32 for a different network:  
Hold the ESP32's dedicated reset button `(GPIO 2 Default)` for 3 seconds.  
The stored credentials will be erased.  
The device will return to AP mode, and the Serial Monitor will show: `ESP_Setup started`

You can now repeat steps 3-5 to send new credentials.

---
  
# 🔧 ESP32 Code Upload Guide (For Beginners)
If you wish to compile and upload the EspCred_ESP_Code/ sketch yourself using the Arduino IDE, follow these instructions.

## 1. Install ESP32 Boards in Arduino IDE
- Open the Arduino IDE.  
- Go to Tools → Board → Boards Manager.  
- Search for: esp32  
- Install ESP32 by Espressif Systems.

## 2. Select the ESP32 Board
- Go to: Tools → Board → ESP32 Arduino.  
- Select: ESP32 Dev Module (or the specific board you are using).

## 3. Select the COM Port
- Go to: Tools → Port.
- Select the appropriate COM port (e.g., COMx).

## 4. If COM Port Not Found (Windows Fix)
If your ESP32 board uses a CP210x or CH340x USB-to-Serial converter and the COM port is missing, you may need to install the driver:
Go to: `Settings` → `Windows Update` → `Advanced options` → `Optional Updates` → `Driver updates`

Look for and install the driver, often listed as:
`Silicon Laboratories Inc. - Ports`

Install the driver → Reconnect the ESP32 → Restart Arduino IDE.  
The COM port should now appear.

## 5. Upload the Code
Click the Upload button in the Arduino IDE.  
**Note: If the Serial Monitor stalls at Connecting........, you may need to assist the board. Hold the `BOOT button` on the ESP32 board until the upload process begins, then release it. This is normal for some ESP32 development boards.**

## 6. Serial Monitor Settings
After uploading, open the Serial Monitor to view device logs:  
Go to: Tools → Serial Monitor.  
Set the Baud Rate to: 115200  
You will see logs detailing the current mode (AP/STA), credential receipt, and WiFi connection status.
