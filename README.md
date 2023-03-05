# Indoor Proximity Localization using ESP32
## Using ESP32 (peripheral) features to locally locate nearby and relevant devices (advertisers).

##### In arduino, Only RSSI is scanned and the sent to Ubidots cloud. MAC Address couldnt be sent as the scanned devices' addresses are in raw format and Ubidots can only receive one data-point or "dot" per unit time. 
##### In Micropython, RSSI and UUID are taken from the scan (will be later sent to Ubidots cloud). The advantages of using python is that we only send the data of devices using the Nordic UART service where the device acts as a peripheral using BLE, thus eliminating other devices that would be unnecessary.

The raw data is cleaned and then mapped to non-negative values and run through a neural network implementing the sigmoid function. 
