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
    void begin() {
        pinMode(LED_R, OUTPUT);
        pinMode(LED_G, OUTPUT);
        pinMode(LED_B, OUTPUT);

        rgb(0, 0, 0);

        debugln("LED initialized");
    }

    void rgb(uint8_t r, uint8_t g, uint8_t b) {
        digitalWrite(LED_R, r);
        digitalWrite(LED_G, g);
        digitalWrite(LED_B, b);
    }

    void color(color_t c) {
        rgb(c.r, c.g, c.b);
    }
}