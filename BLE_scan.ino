#include <iostream>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 5; //In seconds
BLEScan* pBLEScan;
String readString;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      String MAC [500];
      int rssi[500];
      int MAC_size = sizeof(MAC) / sizeof(MAC);

      // storing scanned MACs and RSSIs in seperate arrays for easier access
      for (int s = 0  ; s < MAC_size; s++) {
        MAC[s] = advertisedDevice.getAddress().toString().c_str();
        rssi[s] = advertisedDevice.getRSSI();
        Serial.print("MAC Address: ");
        Serial.println(MAC[s]);
        Serial.print("RSSI: ");
        Serial.println(rssi[s]);
        delay(100);
      }
    }
};

void setup() {
  Serial.begin(115200);
  Serial.println("Waiting for input...");
  BLEDevice::init("ESP32");
  pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but gets results faster
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  // less or equal setInterval value
}

void loop() {
//  if (Serial.available()) {
    String input;
    String new_sc = "new scan";
    String halt = "stop scan";
    input = Serial.readString();
    input.trim();

//    if (input.equalsIgnoreCase(start)) {
      Serial.println("Scan Started");
      unsigned long start = micros();
      BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
      unsigned long end = micros();
      unsigned long delta = end - start;
      Serial.println("Scan done!");
      Serial.print("Scan Time Elapsed:  ");
      long delta_s = (long) (delta / 1000) % 1000;
      Serial.print(delta_s);
      Serial.println(" seconds");
      pBLEScan->clearResults();   // delete results fromBLEScan buffer to release memory
//    }
//  }
  delay(5500);
}
