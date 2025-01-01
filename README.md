# ESP32 Project

## Hardware
| **Utility** | **Reference**          | **Caracteristique** | **Link**                                                              |
|-------------|------------------------|---------------------|-----------------------------------------------------------------------|
| e-Ink       | MF-17502-M009F         | 7.5 inch tri-color  | https://ae01.alicdn.com/kf/S6e59779706f84aafa0aebf99476e2c950.jpg     |
| ESP32       | FireBeetle 2 ESP32-C6  |                     | https://wiki.dfrobot.com/SKU_DFR1075_FireBeetle_2_Board_ESP32_C6      |
| Connector   | e-Paper HAT Revv2.3    |                     | https://www.waveshare.com/wiki/E-Paper_Driver_HAT                     |
| Connector   | GooDisplay DESPI-C02   |                     | https://www.good-display.com/product/516.html                         |

## Good Display PIN

| Display | Name | GPIO | Color      |
|---------|------|------|------------|
| 3v3     | D3   | 14   | ⬛ noir   |
| GND     | GND  | GND  | 🟫 marron |
| SDI     | MOSI | 22   | 🟦 bleu   |
| SCK     | SCK  | 23   | 🟨 jaune  |
| CS      | D7   | 18   | 🟧 orange |
| DC      | SCL  | 20   | 🟩 vert   |
| RES     | SDA  | 19   | ⬜ blanc  |
| BUSY    | D6   | 1    | 🟪 violet |

## E-Ink
| Code bar     | Reference      |
| 041184619565 | MF-17502-M009F | 

[Ink Cubic](http://www.en.inkcubic.com/products_detail/20.html)
[DJN Global](https://www.djnglobal.com/product/7-5-inch-800x480-graphic-e-paper-display/)

![](https://ae01.alicdn.com/kf/S6e59779706f84aafa0aebf99476e2c950.jpg)


## FireBeetle 2 ESP32-C6
![](https://dfimg.dfrobot.com/5d57611a3416442fa39bffca/wiki/1fa8b29bf6d340347ccdc39f4648b949.png)

## Other project pin
![](https://github.com/lmarzen/esp32-weather-epd/blob/main/showcase/wiring_diagram_despi-c02.png?raw=true)
