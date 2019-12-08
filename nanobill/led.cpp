/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "led.h"
#include "config.h"
#include "debug.h"
#include <Arduino.h>

namespace led {
    void rgb_fade(int d) {
        rgb(0, 0, 0);
        int c = 0;

        while (c < 255) {
            analogWrite(LED_R, ++c);
            delay(d);
        }

        while (c > 0) {
            analogWrite(LED_R, --c);
            delay(d);
        }

        while (c < 255) {
            analogWrite(LED_G, ++c);
            delay(d);
        }

        while (c > 0) {
            analogWrite(LED_G, --c);
            delay(d);
        }

        while (c < 255) {
            analogWrite(LED_B, ++c);
            delay(d);
        }

        while (c > 0) {
            analogWrite(LED_B, --c);
            delay(d);
        }
    }

    void begin() {
        pinMode(LED_R, OUTPUT);
        pinMode(LED_G, OUTPUT);
        pinMode(LED_B, OUTPUT);

        rgb_fade(1);

        debugln("LED initialized");
    }

    void rgb(uint8_t r, uint8_t g, uint8_t b) {
        analogWrite(LED_R, r);
        analogWrite(LED_G, g);
        analogWrite(LED_B, b);
    }

    void color(const color_t& c) {
        rgb(c.r, c.g, c.b);
    }
}