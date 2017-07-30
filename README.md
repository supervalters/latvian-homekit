# HomeKit Desk Lamp made with Raspberry Pi and Arduino

## Installation

### Raspberry Pi
I use Pi as HomeKit server using https://github.com/nfarina/homebridge installation is pretty straight forward.
After you've installed HomeBridge on Pi:
1. ```cd ~/.homebridge```
2. ```touch config.json```
3. ```nano config.json```
4. 
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