#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS  30
#define LED_PIN   22

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 0, 0);
  }
  FastLED.show();
  delay(1000);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 255, 0);
  }
  FastLED.show();
  delay(1000);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 255);
  }
  FastLED.show();
  delay(1000);
}
