# Indoor Localization using ESP32
## Using ESP32 BLE features to locally locate selected and relevant devices.
## Project implemented in both C++ and Python


##### In C++, Only RSSI is scanned and the sent to Ubidots cloud. MAC Address couldnt be sent as the scanned devices' addresses are in raw format and Ubidots can only receive one data-point or "dot"per unit time. 
##### In Micropython, RSSI and UUID are taken from the scan (will be later sent to Ubidots cloud). The advantages of using python is that we only send the data of devices using the Nordic UART service where the device acts as a peripheral using BLE, thus eliminating other devices that would be unnecessary.
