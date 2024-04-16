#include <Encoder.h>

Encoder enc(28, 29);

int oldPosition = 0;
int count = 0;
int i = 0;
int newPosition = enc.read();

void checkEncoder() {
  int newPosition = enc.read();

  if (newPosition - oldPosition >= 4) {
    oldPosition = newPosition;  // update the encoder's position
    oneClickLeft();
  }

  if (newPosition - oldPosition <= -4) {
    oldPosition = newPosition;
    oneClickRight();
  }
}

void oneClickLeft() {
  count++;
  Serial.println(count);
}

void oneClickRight() {
  count--;
  Serial.println(count);
}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10  // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }

  display.display();
  delay(2000);  // Pause for 2 seconds

  display.clearDisplay();

  display.drawPixel(10, 10, SSD1306_WHITE);

  display.display();
  delay(2000);
  display.invertDisplay(true);
  delay(1000);
  display.invertDisplay(false);
  delay(1000);
}

void loop() {
  checkEncoder();
  display.display();
  display.drawLine(0, display.height() - 1, count, 0, SSD1306_WHITE);
}
