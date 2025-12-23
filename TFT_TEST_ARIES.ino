/*
 * ST7789 TFT Display Test for ARIES v3.0 Board
 * Using VEGA_ST7735_and_ST7789 Library
 *
 * Display connections:
 * VCC  -> 3.3V
 * GND  -> GND
 * CS   -> GPIO-10
 * SCK  -> SCLK0
 * MOSI -> MOSI0
 * DC   -> GPIO-8
 * RST  -> GPIO-9
 */

#include <SPI.h>
#include <Adafruit_GFX.h> // instasll from Arduino directly from libraray manager search this one 
#include <Adafruit_ST7789.h> // vegas Update the header file for the ARIES Board SPI PIn initialization in Header file of the Main library or add zip of attached lbrary frommy git lin i have provided modified files for the C-DAC ARIES Board which work directly

// ---------------- SPI CONFIG ----------------
SPIClass SPI(0);   // Using SPI0

// ---------------- TFT PINS ----------------
#define TFT_CS   10
#define TFT_DC   8
#define TFT_RST  9

// ---------------- DISPLAY OBJECT ----------------
Adafruit_ST7789 tft(&SPI, TFT_CS, TFT_DC, TFT_RST);

// ---------------- SCREEN SIZE (ROTATION 1) ----------------
const int SCREEN_W = 320;
const int SCREEN_H = 240;

// ---------------- CENTER TEXT FUNCTION ----------------
void drawCenterText(const char *text, int y, uint16_t color, uint8_t size) {
  int16_t x1, y1;
  uint16_t w, h;

  tft.setTextSize(size);
  tft.setTextColor(color);
  tft.getTextBounds(text, 0, y, &x1, &y1, &w, &h);
  int x = (SCREEN_W - w) / 2;
  tft.setCursor(x, y);
  tft.println(text);
}

void setup() {
  Serial.begin(115200);
  delay(200);

  Serial.println("====================================");
  Serial.println("ARIES v3.0 - ST7789 Display Test");
  Serial.println("====================================");

  // ---------------- DISPLAY INIT ----------------
  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  // ---------------- BORDER ----------------
  tft.drawRect(2, 2, SCREEN_W - 4, SCREEN_H - 4, ST77XX_MAGENTA);
  tft.drawRect(4, 4, SCREEN_W - 8, SCREEN_H - 8, ST77XX_MAGENTA);

  int y = 20;

  // ---------------- TEXT CONTENT (CENTERED) ----------------
  drawCenterText("HELLO", y, ST77XX_RED, 3);
  y += 40;

  drawCenterText("ARIES v3.0", y, ST77XX_GREEN, 2);   
  y += 22;

  drawCenterText("VEGA ET1031", y, ST77XX_YELLOW, 2);
  y += 22;

  drawCenterText("THEJAS32", y, ST77XX_CYAN, 2);
  y += 22;

  drawCenterText("Made in India", y, ST77XX_WHITE, 2);
  y += 22;

  drawCenterText("C-DAC", y, ST77XX_ORANGE, 2);
  y += 28;

  drawCenterText("Display OK!", y, ST77XX_GREEN, 2);

  // ---------------- DECORATION ----------------
  int cx = SCREEN_W / 2;
  int cy = SCREEN_H - 35;

  tft.drawCircle(cx, cy, 30, ST77XX_BLUE);
  tft.drawCircle(cx, cy, 28, ST77XX_BLUE);
  tft.fillCircle(cx, cy, 8, ST77XX_RED);

  Serial.println("Display initialized successfully!");
}

void loop() {
  delay(1000);
}



