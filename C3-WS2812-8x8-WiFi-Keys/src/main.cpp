#include "LEDBoard.h"

long check1s = 0, check10ms = 0, check300ms = 0;
uint32_t fill_colors[] = {0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00,
                          0x00FFFF, 0xFF00FF, 0xFFFFFF};
uint8_t fill_index = 0;
uint8_t bright_index = 0;

void inline moveBrightness(int8_t offset) {
  auto count = sizeof(brightneessMap) / sizeof(brightneessMap[0]);
  int next = bright_index + offset;
  if (next < 0) {
    next = count - 1;
  }
  if (next >= count) {
    next = 0;
  }
  bright_index = next;
  pixels.setBrightness(brightneessMap[next]);
  pixels.show();
}

void inline moveFillColor(int8_t offset) {
  auto count = sizeof(fill_colors) / sizeof(fill_colors[0]);
  int next = fill_index + offset;
  if (next < 0) {
    next = count - 1;
  }
  if (next >= count) {
    next = 0;
  }
  fill_index = next;
  pixels.fill(fill_colors[next]);
  pixels.show();
}

void onButtonClick(void *p) {
  u32_t pin = (u32_t)p;
  switch (pin) {
  case PIN_KEY_UP:
    moveBrightness(1);
    break;
  case PIN_KEY_DOWN:
    moveBrightness(-1);
    break;
  case PIN_KEY_LEFT:
    moveFillColor(-1);
    break;
  case PIN_KEY_RIGHT:
    moveFillColor(1);
    break;
  }
}

void onButtonDoubleClick(void *p) {
  u32_t pin = (u32_t)p;
  switch (pin) {
  case PIN_KEY_UP:
    break;
  case PIN_KEY_DOWN:
    break;
  }
}

void setup() {
  initBoard();
  autoConfigWifi();
  startConfigTime();
  setupOTAConfig();
  setupButtons();
  moveFillColor(0);
}

void loop() {
  auto ms = millis();
  if (ms - check1s > 1000) {
    check1s = ms;
    ArduinoOTA.handle();
  }
  if (ms - check300ms > 300) {
    check300ms = ms;
  }
  if (ms - check10ms >= 10) {
    check10ms = ms;
    for (auto it : buttons) {
      it.second->tick();
    }
  }
}
