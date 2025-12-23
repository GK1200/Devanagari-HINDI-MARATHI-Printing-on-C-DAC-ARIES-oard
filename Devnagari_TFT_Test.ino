/*
 * ARIES v3.0 (C-DAC) ST7789 240x320
 * MULTI-lingual (MARATHI Hindi / English)
 * VEGA ET1031 @100MHz
 */
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
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <U8g2_for_Adafruit_GFX.h>


// ---------------- SPI CONFIG ----------------
SPIClass SPI(0);


// ---------------- TFT PINS ----------------
#define TFT_CS   10
#define TFT_DC    8
#define TFT_RST   9


// ---------------- DISPLAY OBJECTS ----------------
Adafruit_ST7789 tft(&SPI, TFT_CS, TFT_DC, TFT_RST);
U8G2_FOR_ADAFRUIT_GFX u8g2;


// ---------------- UTF-8 DECODER ----------------
uint16_t get_utf8_char(const char **s) {
  uint16_t c = (uint8_t)**s;
  if (!c) return 0;
  (*s)++;
  if (c < 128) return c;
  if ((c & 0xe0) == 0xc0) return ((c & 0x1f) << 6) | ((uint8_t)(*(*s)++) & 0x3f);
  if ((c & 0xf0) == 0xe0) {
    uint16_t res = (c & 0x0f) << 12;
    res |= ((uint8_t)(*(*s)++) & 0x3f) << 6;
    res |= ((uint8_t)(*(*s)++) & 0x3f);
    return res;
  }
  return 0;
}


// ---------------- FIXED DEVANAGARI DRAWING ----------------
uint16_t drawHindi(int16_t x, int16_t y, const char *str) {
  uint16_t e;
  uint16_t sum = 0;


  while ((e = get_utf8_char(&str)) != 0) {
    // 1. PRE-CORRECTION: Modify x and y directly to overlap matras
    switch(e) {
      case 0x0901: case 0x0902: x -= 14; y -= 2; break; // ँ, ं
      case 0x0903: x -= 14; break;                       // ः
      case 0x093e: x -= 12; break;                       // ा
      case 0x093f: x -= 16; break;                       // ि
      case 0x0940: x -= 12; break;                       // ी
      case 0x0941: x -= 15; y += 2; break;              // ु
      case 0x0942: x -= 12; y += 2; break;              // ू
      case 0x0943: x -= 16; y += 2; break;              // ृ
      case 0x0944: x -= 16; y += 2; break;              // ॄ
      case 0x0945: x -= 14; y -= 2; break;              // ॅ
      case 0x0947: case 0x0948: x -= 14; break;          // े, ै
      case 0x094b: case 0x094c: x -= 14; break;          // ो, ौ
      case 0x094d: x -= 10; break;                       // ्
    }


    // Draw the glyph at the current (corrected) coordinate
    uint16_t delta = u8g2.drawGlyph(x, y, e);


    // 2. POST-CORRECTION: Revert Y-shifts and fine-tune X-spacing
    switch(e) {
      case 0x0901: case 0x0902: x -= 6; y += 2; break;  // Revert y
      case 0x0941: x -= 3; y -= 2; break;              // Revert y
      case 0x0942: x -= 6; y -= 2; break;
      case 0x0943: case 0x0944: x -= 4; y -= 2; break;
      case 0x0945: x -= 6; y += 2; break;
      case 0x094d: x -= 8; break;                       // Halant fix
      case 0x093e: case 0x0940: x -= 2; break;          // Tighten spacing
      case 0x0947: case 0x0948: case 0x094b: case 0x094c: x -= 2; break;
    }


    x += delta;
    sum += delta;
  }
  return sum;
}


// ---------------- DEMO SETUP ----------------
void setup() {
  SPI.begin();
  tft.init(240, 320);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);
  tft.drawRect(2, 2, 316, 236, ST77XX_WHITE);


  u8g2.begin(tft);
  u8g2.setFont(u8g2_font_unifont_t_devanagari);
  u8g2.setFontMode(1);
  u8g2.setForegroundColor(ST77XX_WHITE);


  // -------- RENDER CONTENT --------
  drawHindi(110, 35, "मेरा भारत महान");
  tft.drawFastHLine(20, 45, 280, ST77XX_WHITE);

}


void loop() {}

