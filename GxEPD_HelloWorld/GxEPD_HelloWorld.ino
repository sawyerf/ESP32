#include <GxEPD.h>

// select the display class to use, only one
// #include <GxGDEW075T8/GxGDEW075T8.h>      // 7.5" b/w
// #include <GxGDEW075T7/GxGDEW075T7.h>      // 7.5" b/w 800x480
// #include <GxGDEW075Z09/GxGDEW075Z09.h>    // 7.5" b/w/r
#include <GxGDEW075Z08/GxGDEW075Z08.h>  // 7.5" b/w/r 800x480
// #include <GxGDEY075Z08/GxGDEY075Z08.h>    // 7.5" b/w/r 800x480

#include GxEPD_BitmapExamples

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMonoBold9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeMonoBold24pt7b.h>

#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>

GxIO_Class io(SPI, /*CS=5*/ 18, /*DC=*/20, /*RST=*/19);
GxEPD_Class display(io, /*RST=*/19, /*BUSY=*/1);

void setup() {
  SPI.end();
  SPI.begin(23, 21, 22, 18);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  Serial.println("------------");
  Serial.println("setup");

  display.init(115200);  // enable diagnostic output on Serial

  // test 1
  Serial.println("3");
  display.drawPaged(drawHelloWorld);

  display.powerDown();

  digitalWrite(LED_BUILTIN, LOW);

  Serial.println("setup done");
}

void loop(){};

const char HelloWorld[] = "test";

void drawHelloWorld() {
  Serial.println("drawHelloWorld");
  display.eraseDisplay();
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby;
  uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  // center bounding box by transposition of origin:
  uint16_t x = ((display.width() - tbw) / 2) - tbx;
  uint16_t y = ((display.height() - tbh) / 2) - tby;
  display.fillScreen(GxEPD_WHITE);
  display.setCursor(x, y);
  display.print(HelloWorld);
  Serial.println("drawHelloWorld done");
}