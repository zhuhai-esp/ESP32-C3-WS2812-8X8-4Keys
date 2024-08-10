#ifndef __LED_SHOW_H__
#define __LED_SHOW_H__

#include "LEDBoard.h"
#include <math.h>

const uint32_t fill_colors[] = {0xFF0000, 0x00FF00, 0x0000FF, 0xFFFF00,
                                0x00FFFF, 0xFF00FF, 0xFFFFFF};
const auto color_count = sizeof(fill_colors) / sizeof(fill_colors[0]);
uint8_t fill_index = 0;
uint8_t bright_index = 0;
uint32_t step = 0;

void effectStep() {
  if (fill_index == 0) {
    if (step % 50 == 0) {
      pixels.fill(fill_colors[(step / 50) % color_count]);
    }
  } else if (fill_index == 1) {
    pixels.rainbow((step * 30) % 0xFFFF, -1, 255, 255);
  } else if (fill_index == 2) {
    if (step % 5 == 0) {
      pixels.clear();
      auto v = step / 5;
      pixels.setPixelColor(v % PIX_NUM,
                           fill_colors[(v / PIX_NUM) % color_count]);
    }
  } else if (fill_index == 3) {
    if (step % 10 == 0) {
      pixels.clear();
      auto v = step / 10;
      for (uint8_t i = 0; i < 8; i++) {
        pixels.setPixelColor((v % 8) * 8 + i,
                             fill_colors[(v / 8) % color_count]);
      }
    }
  } else if (fill_index == 4) {
    if (step % 10 == 0) {
      pixels.clear();
      uint32_t v = step / 10;
      uint64_t map[] = {0x0000001818000000, 0x00003c24243c0000,
                        0x007e424242427e00, 0xFF818181818181FF};
      uint64_t p = 0;
      for (uint8_t i = 0; i < PIX_NUM; i++) {
        p = 1;
        int idx = (v % 7) - 3;
        if ((p << i) & map[3 - abs(idx)]) {
          pixels.setPixelColor(i, fill_colors[(v / 7) % color_count]);
        }
      }
    }
  }
  pixels.show();
  step += 1;
  if (step == 0x10000) {
    step = 0;
  }
}

#endif