# HomeKit Desk Lamp made with Raspberry Pi and Arduino

## Description
Homemade HomeKit device using a lot of cables but giving that joy when you create something with your own hands. A small demo here: 

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/YJR_WMAwMMw/0.jpg)](https://www.youtube.com/watch?v=YJR_WMAwMMw)

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
    "username": "CC:22:3D:E3:CE:30",
    "port": 51826,
    "pin": "031-45-154"
  },
  "platforms": [],
  "accessories": [
    {
      "accessory": "Http",
      "name": "Desk Lamp",
      "on_url": "http://192.168.2.202:80/?on",
      "off_url": "http://192.168.2.202:80/?off",
      "http_method": "GET"
    }
  ]
}
```
5. Run HomeBridge. There could be some problems with running HomeBridge globally on Pi, so I run it using this ```/opt/node/lib/node_modules/homebridge/bin/homebridge```


### Arduino
I've uploaded Arduino INO file to this repository. My Arduino setup:
- Arduino Uno 
- HR911105A Ethernet Shield (In the beginning tried with ESP8266, but it was too much hustle)
- SRD-05VDC-SL-C relay module connected on pin 2
- A desk lamp connected to relay module