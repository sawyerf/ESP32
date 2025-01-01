# 🔌 ESP32 Project

## Hardware
| **Utility** | **Reference**          | **Caracteristique** | **Link**                   |
|-------------|------------------------|---------------------|----------------------------|
| e-Ink       | MF-17502-M009F         | 7.5 inch tri-color  | [Product Page][Screen DJN] |
| ESP32       | FireBeetle 2 ESP32-C6  |                     | [Wiki][ESP32 Wiki]         |
| Connector   | e-Paper HAT Revv2.3    |                     | [Doc][Conn WS]             |
| Connector   | GooDisplay DESPI-C02   |                     | [Product Page][Conn GD]    |

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
<img src="https://ae01.alicdn.com/kf/S6e59779706f84aafa0aebf99476e2c950.jpg" width="200" height="auto" align="right" />

| **Code bar** | **Reference**  |
|--------------|----------------|
| 041184619565 | MF-17502-M009F | 

### Source
- [Ink Cubic][Screen Cubic]
- [DJN Global][Screen DJN]

## FireBeetle 2 ESP32-C6
<img src="https://dfimg.dfrobot.com/5d57611a3416442fa39bffca/wiki/1fa8b29bf6d340347ccdc39f4648b949.png" width="300" height="auto" />

## Other project pin
<img src="https://github.com/lmarzen/esp32-weather-epd/blob/main/showcase/wiring_diagram_despi-c02.png?raw=true" width="300" height="auto" />

[ESP32 Wiki]: https://wiki.dfrobot.com/SKU_DFR1075_FireBeetle_2_Board_ESP32_C6
[Conn WS]: https://www.waveshare.com/wiki/E-Paper_Driver_HAT
[Conn GD]: https://www.good-display.com/product/516.html
[Screen Cubic]: http://www.en.inkcubic.com/products_detail/20.html
[Screen DJN]: https://www.djnglobal.com/product/7-5-inch-800x480-graphic-e-paper-display/