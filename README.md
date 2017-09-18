# Latvian HomeKit made with Raspberry Pi and Arduino

## Description
Homemade HomeKit device using a lot of cables but giving that joy when you create something with your own hands. A small demo here: 

[![HomeKit Demo](https://img.youtube.com/vi/YJR_WMAwMMw/0.jpg)](https://www.youtube.com/watch?v=YJR_WMAwMMw)

Screenshot from iPhone:

![HomeKit screenshot](http://screens.valters.me/jjGhfiBc9j.png)


## Hardware list
- Apple TV 3rd gen (Works as your HomeKit HUB)
- Router (I use ASUS RT-N12+)
- iPhone (for obvious reasons)
- Arduino Uno
- HR911105A Ethernet Shield
- DHT22 temperature sensor
- WS2812B RGB LED ring
- Keyestudio Single Channel Relay
- Raspberry Pi 3
- Lot of cables (ethernet and arduino)
- Soldering iron

## Installation

### Raspberry Pi
I use Pi as HomeKit server using https://github.com/nfarina/homebridge. Installation is pretty straight forward.
After you've installed HomeBridge on Pi:
1. ```cd ~/.homebridge```
2. ```touch config.json```
3. ```nano config.json```
4. Add this code to config.json (change the IP address to suit your local network)
```json
{
  "bridge": {
    "name": "Homebridge",
    "username": "CC:22:3D:E3:CE:31",
    "port": 51826, 
    "pin": "031-45-154"
  },
  "platforms": [],
  "accessories": [
    {
      "accessory": "Http",
      "name": "Desk Lamp",
      "on_url": "http://192.168.2.202:80/?lamp_on",
      "off_url": "http://192.168.2.202:80/?lamp_off",
      "http_method": "GET"
    },
    {
      "accessory": "HttpTemphum",
      "name": "Living Room Weather",
      "url": "http://192.168.2.202/?weather",
      "http_method": "GET"
    },
    {
      "accessory": "HttpTemphum",
      "name": "Outside Weather",
      "url": "http://192.168.2.202/?w_out",
      "http_method": "GET"
    },
    {
      "accessory": "HTTP-RGB",
      "name": "RGB",
      "switch": {
        "status": "http://192.168.2.202/?rgb_status",
        "powerOn": "http://192.168.2.202/?rgb_on",
        "powerOff": "http://192.168.2.202/?rgb_off"
      },
      "brightness": {
        "status": "http://192.168.2.202/?rgb_brightness",
        "url": "http://192.168.2.202/?rgb_light/%s"
      },
      "color": {
        "status": "http://192.168.2.202/?rgb_set",
        "url": "http://192.168.2.202/?rgb_hue/%s",
        "brightness": true
      }
    }
  ]
}
```
5. Install ```$ npm install -g homebridge-http```
6. Install ```$ npm install -g homebridge-httptemperaturehumidity```
7. Install ```$ npm install -g homebridge-better-http-rgb```
8. Run HomeBridge ```$ homebridge```


### Arduino
I've uploaded Arduino INO file to this repository. My Arduino setup:
- Arduino Uno 
- HR911105A Ethernet Shield (In the beginning tried with ESP8266, but it was too much hustle)
- SRD-05VDC-SL-C relay module connected on pin 3
- DHT22 temperature and humidity module connected on pin 2 (inside) and on pin 4 (outside)
- A desk lamp connected to relay module