#include <UbiBuilder.h>
#include <UbiConstants.h>
#include <Ubidots.h>
#include <UbiHttp.h>
#include <UbiProtocol.h>
#include <UbiProtocolHandler.h>
#include <UbiTcp.h>
#include <UbiTypes.h>
#include <UbiUdp.h>
#include <UbiUtils.h>

#include <iostream>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <WiFi.h>
#include <Ubidots.h>

/* Network credentials*/
const char* UBIDOTS_TOKEN = "BBFF-yRZeguGTJQXLKQIx2cOzEkEsWTQhk0";
const char* WIFI_SSID = "Dr.Sabry's Network (tmp)"; //VodafoneMobileWiFi-A04C95
const char* WIFI_PASS = "$Drsabryhome01"; //9877350427
//Ubidots ubidots(UBIDOTS_TOKEN, UBI_TCP);
Ubidots ubidots(UBIDOTS_TOKEN, UBI_TCP);
// Ubidots ubidots(UBIDOTS_TOKEN, UBI_UDP);

/*Initializing scan variables*/
int scanTime = 2; //In seconds
BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {

      /* Sending to Ubidots*/
      bool foo = true;
      while (foo == true) {
        ubidots.add("Test MAC", advertisedDevice.getRSSI());
        bool bufferSent = false;
        bufferSent = ubidots.send();
        delay(7500);

        if (bufferSent) {
          Serial.println("Values sent by the device");
          ESP.restart();
        }
        else {
          ESP.restart();
        }


        /*           Printing MACs and resp RSSI
          Serial.print("MAC Address: ");
          Serial.println(advertisedDevice.getAddress().toString().c_str());
          Serial.print("RSSI: ");
          Serial.println(advertisedDevice.getRSSI());
          delay(200);
          String MAC = advertisedDevice.getAddress().toString().c_str();
          int rssi = advertisedDevice.getRSSI();
        */
      }
    }
};
void setup() {
  Serial.begin(115200);
  ubidots.wifiConnect(WIFI_SSID, WIFI_PASS);
  ubidots.setDebug(true);  // Uncomment to debug

  Serial.println("Starting Scan...");
  BLEDevice::init("ESP32");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but gets results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {

  Serial.println("Scan Started");
  BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
  Serial.println("Scan Done!");
  pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
  delay(7500);
}
