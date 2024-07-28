#ifndef __LED_BOARD_H__
#define __LED_BOARD_H__

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <ArduinoOTA.h>
#include <OneButton.h>
#include <WiFi.h>
#include <map>

#ifdef LED_BUILTIN
#undef LED_BUILTIN
#endif
#define LED_BUILTIN 8
#define PIN_PIXS 10
#define PIX_NUM 64

#define PIN_KEY_UP 2
#define PIN_KEY_DOWN 4
#define PIN_KEY_LEFT 3
#define PIN_KEY_RIGHT 1

Adafruit_NeoPixel pixels(PIX_NUM, PIN_PIXS, NEO_GRB + NEO_KHZ800);
uint8_t brightneessMap[] = {1, 2, 4, 8, 16, 32, 64, 128, 192, 255};
std::map<u32_t, OneButton *> buttons;

extern void onButtonClick(void *p);
extern void onButtonDoubleClick(void *p);

void inline setupButtons() {
  u32_t btnPins[] = {PIN_KEY_UP, PIN_KEY_DOWN, PIN_KEY_LEFT, PIN_KEY_RIGHT};
  for (auto pin : btnPins) {
    auto *btn = new OneButton(pin);
    btn->attachClick(onButtonClick, (void *)pin);
    btn->attachDoubleClick(onButtonDoubleClick, (void *)pin);
    buttons.insert({pin, btn});
  }
}

void inline initBoard() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  pixels.begin();
  pixels.setBrightness(1);
  pixels.clear();
  pixels.show();
}

void inline autoConfigWifi() {
  WiFi.mode(WIFI_MODE_STA);
  WiFi.begin();
  for (int i = 0; WiFi.status() != WL_CONNECTED && i < 100; i++) {
    delay(100);
  }
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.mode(WIFI_MODE_APSTA);
    WiFi.beginSmartConfig();
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
    }
    WiFi.stopSmartConfig();
    WiFi.mode(WIFI_MODE_STA);
  }
}

void inline startConfigTime() {
  const int timeZone = 8 * 3600;
  configTime(timeZone, 0, "ntp6.aliyun.com", "cn.ntp.org.cn", "ntp.ntsc.ac.cn");
  while (time(nullptr) < 8 * 3600 * 2) {
    delay(500);
  }
}

void inline setupOTAConfig() {
  ArduinoOTA.onStart([] {});
  ArduinoOTA.onProgress([](u32_t pro, u32_t total) {});
  ArduinoOTA.onEnd([] {});
  ArduinoOTA.onError([](ota_error_t err) {});
  ArduinoOTA.begin();
}

#endif