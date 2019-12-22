/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "led.h"

#include "config.h"

namespace led {
    const unsigned long pwm_int = 1000000 / PWM_HZ / 256;

    unsigned long pwm_prev = 0;

    uint8_t pwm_count = 0;

    uint8_t pwm_color[] = { 255, 255, 255 };

    bool enabled = false;
    bool changed = false;

    uint8_t new_color[] = { 255, 255, 255 };

    void begin() {
        RGB_MODE();

        enable();
        rgb(0, 0, 0);

        debugln("LED initialized");

        pwm_prev = micros();
    }

    void enable() {
        enabled = true;
    }

    void disable() {
        RGB_RESET();
        enabled = false;
    }

    void digital(bool r, bool g, bool b) {
        RGB_RESET();
        RGB_SET(r, g, b);
    }

    void rgb(uint8_t r, uint8_t g, uint8_t b) {
        new_color[0] = 255 - r;
        new_color[1] = 255 - g;
        new_color[2] = 255 - b;

        changed = true;
    }

    void color(const color_t& c) {
        new_color[0] = 255 - c.r;
        new_color[1] = 255 - c.g;
        new_color[2] = 255 - c.b;

        changed = true;
    }

    void rainbow(uint8_t pos) {
        if (pos < 85) {
            rgb(pos* 3, 255 - pos * 3, 0);
        } else if (pos < 170) {
            rgb(255 - (pos-85) * 3, 0, (pos-85)* 3);
        } else {
            rgb(0, (pos-170)* 3, 255 - (pos-170) * 3);
        }
    }

    void random_color() {
        uint8_t r = random(256);
        uint8_t g = random(256-r);
        uint8_t b = (255-r-g);

        rgb(r, g, b);
    }

    void update() {
        if (enabled) {
            unsigned long m = micros();

            if (m - pwm_prev >= pwm_int) {
                pwm_prev += pwm_int;

                if (pwm_count == 255) {
                    RGB_RESET();

                    pwm_count = 0;

                    if (changed) {
                        changed      = false;
                        pwm_color[0] = new_color[0];
                        pwm_color[1] = new_color[1];
                        pwm_color[2] = new_color[2];
                    }
                } else {
                    RGB_SET((pwm_count == pwm_color[0]), (pwm_count == pwm_color[1]), (pwm_count == pwm_color[2]));

                    ++pwm_count;
                }
            }
        }
    }
}