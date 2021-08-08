#include <Arduino.h>
#include <FastLED.h>
#include <esp_wifi.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#define NUM_LEDS 30
#define LED_PIN 22

BluetoothSerial Serial_bt;
CRGB leds[NUM_LEDS];

void bluetooth_receive(void *) {
  while (true) {
    if (Serial_bt.available()) {
      Serial.print(Serial_bt.readString());
    }
    vTaskDelay(300);
  }
}

void leds_blink(void *) {
  while (true) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(25, 0, 0);
    }
    FastLED.show();
    vTaskDelay(1000);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, 25, 0);
    }
    FastLED.show();
    vTaskDelay(1000);

    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(0, 0, 25);
    }
    FastLED.show();
    vTaskDelay(1000);
  }
}
void setup() {
  Serial.begin(115200);
  Serial_bt.begin("LEDS_INO"); // Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  esp_wifi_stop(); //stop WiFi because it is not used in this project

  xTaskCreatePinnedToCore(leds_blink,   // Function to implement the task
                          "leds_blink", // Name of the task
                          6000,         // Stack size in words
                          NULL,         // Task input parameter
                          0,            // Priority of the task
                          NULL,         // Task handle.
                          1);           // Core where the task should run

  xTaskCreatePinnedToCore(bluetooth_receive,   // Function to implement the task
                          "bluetooth_receive", // Name of the task
                          6000,                // Stack size in words
                          NULL,                // Task input parameter
                          0,                   // Priority of the task
                          NULL,                // Task handle.
                          0);                  // Core where the task should run
  vTaskStartScheduler();
}

void loop() {

  delay(10000);
  // vTaskDelete(NULL);
}
