#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

#ifdef LED_BUILTIN
#undef LED_BUILTIN
#endif
#define LED_BUILTIN 8
#define PIN_PIXS 10
#define PIX_NUM 64

Adafruit_NeoPixel pixels(PIX_NUM, PIN_PIXS, NEO_GRB + NEO_KHZ800);

void inline initBoard() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pixels.begin();
  pixels.setBrightness(80);
  pixels.clear();
}

void inline colorBlink(uint32_t c) {
  pixels.fill(c);
  pixels.show();
  delay(1000);
}

void inline pixelsCheck() {
  uint32_t colors[] = {0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00,
                       0x00FFFF, 0xFF00FF, 0xFFFFFF};
  for (auto c : colors) {
    colorBlink(c);
  }
}

void setup() { initBoard(); }

void loop() {
  pixelsCheck();
  for (uint16_t i = 0; i < 1024 * 10; i++) {
    pixels.rainbow(i * 30, -1, 255, 255);
    pixels.show();
  }
}
