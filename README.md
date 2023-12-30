# Miniature Apple IIe with working screen
The Miniature Apple IIe project was inspired by this [1/3rd scale Raspberry Pi Zero Mac](https://www.instructables.com/Making-a-Tiny-Mac-From-a-Raspberry-Pi-Zero/) and many other attempts at making Pi-based Apple computers, including many Apple II's.  I found the screen on the working Mac model to be too small to really be usable and, while certainly impressive, generally unnecessary to trigger all of the nostalgia endorphins.  This project attempts to create a simple-to-build and cost-effect (less than $20) Apple IIe that can be used to display some sweet, sweet nostalgia (hello, Oregon Trail) or as a platform for more advanced projects.  In addition to being cheap ($5), the XIAO ESP32C23 microcontroller has BLE and Wifi so it could serve up some pretty impressive content.

## Materials
* 3D-printed Apple IIe case (will upload files)
  * [Beige PLA](https://www.amazon.com/gp/product/B09TR8N5T2/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
  * [Brown PLA](https://www.amazon.com/gp/product/B0991VV5SX/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1)
  * Originally based on (Mini Apple ][)[https://www.thingiverse.com/thing:3643947] but heavily modified to support the electronics.
* XIAO ST7789V2 LCD Display [Seeed Studio](https://www.seeedstudio.com/1-69inch-240-280-Resolution-IPS-LCD-Display-Module-p-5755.html) | [GitHub](https://github.com/limengdu/XIAO_ST7789V2_LCD_Display/) | [Buy on Digikey](https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/104990802/21526011)
* XIAO ESP32C23 Microcontroller [Seeed Studio](https://www.seeedstudio.com/Seeed-XIAO-ESP32C3-p-5431.html) | [Buy on digikey](https://www.digikey.com/en/products/detail/seeed-technology-co-ltd/113991054/16652880)

## Connecting the LCD to the Microcontroller
| LCD | Microcontroller | Color* |
|-----|-----|--------|
| VCC | 3V3 | Purple |
| GND | GND | White  |
| DIN | D10 | Green  |
| CLK | D8  | Orange |
| CS  | D1  | Yellow |
| DC  | D3  | Blue   |
| RST | D0  | Brown  |
| BL  | D6  | Gray   |

*=Be sure to verify color codes against the actual cable.

## Programming
1. Follow the instructions on [Seeed's Wiki](https://wiki.seeedstudio.com/XIAO_ESP32C3_Getting_Started/) to set up the Arduino development environment.
2. Clone this repo and open one of the files from the Controller path in Arduino Studio
3. Select the appropiate board (probably XIAO ESP32C3) and port (probably a COMn port)
4. Upload the INO to the controller.   

## Custom Graphics
Loading raster graphics onto the unit is not terribly elegant but should be straightforward with the included python script.
1. Create a 260x240 pixel image
2. Convert the image to 16-bit 5-6-5 depth and export as hex using the included Python script  For example:
```
ImageConvert.py OregonTrail/oregon1.png
```
3. Open the result (out.txt) and paste into graphics.cpp, cleaning up syntax (commas, brackets, etc)

## Additional References
- https://github.com/limengdu/XIAO_ST7789V2_LCD_Display/blob/main/st7789v2.h
