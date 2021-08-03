#include <iostream>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <WiFi.h>

const char* ssid = "Airbox-E026"; //Dr.Sabry's Network (tmp) // Airbox-E026
const char* password = "16944966"; //sabry12345 // 16944966

const uint16_t port = 9001;
const char * host = "192.168.1.107";

int scanTime = 5; //In seconds
BLEScan* pBLEScan;
String readString;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      bool b = true;
      WiFiClient client;
      if (!client.connect(host, port)) {
        Serial.println("Connection to host failed");
        delay(1000);
        return;
      }
      else {
        Serial.println("Connected to server successful!");
        client.print(advertisedDevice.getAddress().toString().c_str());
        client.print(advertisedDevice.getRSSI());
        delay(500);
        Serial.println("Data Sent. Disconnecting...");
        client.stop();
      }
      delay(5000);
    }
};

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  delay(500);
  BLEDevice::init("ESP32-1");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but gets results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(6500);
}
