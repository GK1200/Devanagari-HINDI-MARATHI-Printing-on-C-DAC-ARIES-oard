# Devanagari-HINDI-MARATHI-Printing-on-C-DAC-ARIES-Board
GitHub repository structure for your Devanagari display project on the ARIES C-CDAC Board
# Devanagari Text Display on ARIES V3.0 RISC-V Board



A lightweight Devanagari script rendering engine optimized for low-memory microcontrollers, specifically designed for the **ARIES V3.0 RISC-V development board** by C-DAC. This project enables display of Hindi and Marathi text on ST7789 TFT displays with proper matra positioning and ligature support.

## Features

- ✅ Full Devanagari Unicode support (U+0900 to U+097F)
- ✅ Optimized for low-memory RISC-V processors
- ✅ Custom UTF-8 decoder for efficient character processing
- ✅ Accurate matra positioning with pre/post correction
- ✅ Support for Hindi and Marathi languages
- ✅ Works with 240x320 ST7789 TFT displays
- ✅ Memory-efficient font rendering using U8g2

##  Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Pin Configuration](#pin-configuration)
- [Installation](#installation)
- [Wiring Diagram](#wiring-diagram)
- [Usage](#usage)
- [API Reference](#api-reference)
- [Examples](#examples)
- [Acknowledgments](#acknowledgments)

## 🔧 Hardware Requirements

| Component | Specification | Quantity |
|-----------|--------------|----------|
| **ARIES V3.0 Board** | RISC-V RV32IMAC @ 50MHz, C-DAC | 1 |
| **ST7789 TFT Display** | 240x320 pixels, SPI Interface | 1 |
| **Jumper Wires** | Male-to-Female | 8 |
| **Breadboard** | (Optional) | 1 |
| **USB Cable** | Micro USB for programming | 1 |

### About ARIES V3.0

The ARIES (Accelerated RISC-V Indigenous Ecosystem Solutions) V2.0 is an indigenous RISC-V development board designed by C-DAC, India. It features:
- 32-bit RISC-V core (RV32IMAC)
- 50 MHz clock frequency
- 128 KB Flash, 64 KB SRAM
- Arduino-compatible headers
- Native SPI, I2C, UART interfaces

## 💻 Software Requirements

### Required Libraries

Install the following libraries through Arduino IDE Library Manager or manually:

1. **Adafruit GFX Library** (v1.11.9 or later)
   - Core graphics library for displays
   - [GitHub Repository](https://github.com/adafruit/Adafruit-GFX-Library)

2. **Adafruit ST7789 Library** (v1.10.3 or later)
   - Display driver for ST7789 TFT
   - [GitHub Repository](https://github.com/adafruit/Adafruit-ST7789-Library)

3. **U8g2_for_Adafruit_GFX** (v1.6.2 or later)
   - Font rendering with Devanagari support
   - [GitHub Repository] Oliver

### Development Environment

- **Arduino IDE** 2.0 or later
- **ARIES Board Support Package** (BSP) from C-DAC
  - Installation instructions: [C-DAC ARIES Support]

## Pin Configuration

### ST7789 Display to ARIES V3.0 Connections

| ST7789 Pin | ARIES V3.0 Pin | Function | Description |
|------------|----------------|----------|-------------|
| **VCC** | 3.3V | Power | Display power supply |
| **GND** | GND | Ground | Common ground |
| **CS** | GPIO 10 | Chip Select | SPI device selection |
| **DC** | GPIO 8 | Data/Command | Command/Data selection |
| **RST** | GPIO 9 | Reset | Display reset |
| **SDA** | GPIO 11 (MOSI) | MOSI | SPI data line |
| **SCL** | GPIO 13 (SCK) | Clock | SPI clock line |
| **BL** | 3.3V | Backlight | Display backlight |

### SPI Configuration

```cpp
SPIClass SPI(0);  // Hardware SPI channel 0
#define TFT_CS   10
#define TFT_DC    8
#define TFT_RST   9
```

## Wiring Diagram

```
ARIES V2.0 Board                    ST7789 TFT Display
┌─────────────────┐                ┌──────────────────┐
│                 │                │                  │
│  3.3V     ●─────┼────────────────┼───● VCC          │
│                 │                │                  │
│  GND      ●─────┼────────────────┼───● GND          │
│                 │                │                  │
│  GPIO 10  ●─────┼────────────────┼───● CS           │
│                 │                │                  │
│  GPIO 8   ●─────┼────────────────┼───● DC           │
│                 │                │                  │
│  GPIO 9   ●─────┼────────────────┼───● RST          │
│                 │                │                  │
│  GPIO 11  ●─────┼────────────────┼───● SDA (MOSI)  │
│  (MOSI)         │                │                  │
│                 │                │                  │
│  GPIO 13  ●─────┼────────────────┼───● SCL (SCK)    │
│  (SCK)          │                │                  │
│                 │                │                  │
│  3.3V     ●─────┼────────────────┼───● BL           │
│                 │                │                  │
└─────────────────┘                └──────────────────┘
```

##nstallation

### Step 1: Install ARIES Board Support

1. Open Arduino IDE
2. Go to **File → Preferences**
3. Add ARIES board URL to "Additional Board Manager URLs"
4. Go to **Tools → Board → Boards Manager**
5. Search for "ARIES" and install the package
6. Select **Tools → Board → ARIES V3.0**

### Step 2: Install Required Libraries

```bash
# Using Arduino IDE Library Manager:
# 1. Sketch → Include Library → Manage Libraries
# 2. Search and install each library:
#    - Adafruit GFX Library
#    - Adafruit ST7735 and ST7789 Library (VEGA Board)
#    - U8g2_for_Adafruit_GFX
```

Or install manually:
```bash
cd ~/Arduino/libraries/
git clone https://github.com/adafruit/Adafruit-GFX-Library.git
git clone https://github.com/adafruit/Adafruit-ST7789-Library.git
git clone https://github.com/olikraus/U8g2_for_Adafruit_GFX.git
```



### Custom Text Display

```cpp
void displayCustomText() {
  tft.fillScreen(ST77XX_BLACK);
  
  // Title
  drawHindi(80, 30, "मेरा भारत महान");
  
  // Subtitle
  drawHindi(60, 60, "स्वागत है");
  
  // Multiple lines
  drawHindi(40, 100, "हिंदी में लिखें");
  drawHindi(40, 130, "मराठी में लिखें");
}
```

##  API Reference

### Core Functions

#### `uint16_t drawHindi(int16_t x, int16_t y, const char *str)`

Renders Devanagari text at specified coordinates with automatic matra positioning.

**Parameters:**
- `x` - X coordinate (0-319)
- `y` - Y coordinate (0-239)
- `str` - UTF-8 encoded Devanagari string

**Returns:**
- Total width of rendered text in pixels

**Example:**
```cpp
uint16_t width = drawHindi(100, 50, "भारत");
```

#### `uint16_t get_utf8_char(const char **s)`

Decodes UTF-8 character and advances string pointer.

**Parameters:**
- `s` - Pointer to UTF-8 string pointer

**Returns:**
- Unicode codepoint (uint16_t)

### Display Configuration

```cpp
// Initialize display
void initDisplay() {
  SPI.begin();
  tft.init(240, 320);
  tft.setRotation(1);  // Landscape mode
  u8g2.begin(tft);
  u8g2.setFont(u8g2_font_unifont_t_devanagari);
}
```

##Examples

### Example 1: Simple Greeting

```cpp
void displayGreeting() {
  tft.fillScreen(ST77XX_BLACK);
  drawHindi(80, 50, "नमस्ते!");
  drawHindi(70, 90, "आपका स्वागत है");
}
```



### Example 2: Sensor Data Display

```cpp
void displaySensorData(float temp, float humidity) {
  char buffer[50];
  
  drawHindi(50, 60, "तापमान:");
  sprintf(buffer, "%.1f °C", temp);
  tft.setCursor(150, 60);
  tft.print(buffer);
  
  drawHindi(50, 100, "आर्द्रता:");
  sprintf(buffer, "%.1f %%", humidity);
  tft.setCursor(150, 100);
  tft.print(buffer);
}
```


**Problem:** Library not found errors

**Solutions:**
```bash
# Reinstall libraries
rm -rf ~/Arduino/libraries/Adafruit*
rm -rf ~/Arduino/libraries/U8g2*
# Then reinstall via Library Manager
```

### Memory Issues

**Problem:** Sketch too large for ARIES board

**Solutions:**
- Remove unused libraries from includes
- Optimize string constants



### Coding Standards

- Follow Arduino coding style
- Comment complex matra positioning logic
- Test on actual hardware before PR
- Update README for new feature

## Acknowledgments

- **C-DAC** for the indigenous ARIES V3.0 RISC-V board
- **Adafruit** for excellent graphics libraries
- **U8g2** project for Devanagari font support
- Indian open-source community for inspiration

#
---

