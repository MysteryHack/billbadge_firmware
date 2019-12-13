/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "led.h"
#include "config.h"

#include <avr/io.h>

namespace led {
    const unsigned long pwm_int = 1000000 / PWM_HZ / 256;

    unsigned long pwm_prev = 0;

    uint8_t pwm_count = 0;

    uint8_t pwm_color[] = { 255, 255, 255 };

    bool changed = false;

    uint8_t new_color[] = { 255, 255, 255 };

    void begin() {
        // pinMode(LED_R, OUTPUT);
        // pinMode(LED_G, OUTPUT);
        // pinMode(LED_B, OUTPUT);

        DDRB |= (1 << DDB4);
        DDRB |= (1 << DDB3);
        DDRB |= (1 << DDB1);

        rgb(0, 0, 0);

        // pwm_prev = micros();
    }

    void digital(bool r, bool g, bool b) {
        PORTB |= (r << PB4 | g << PB3 | b << PB1);
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

    void update() {
        unsigned long m = 0; // micros();

        if (m - pwm_prev >= pwm_int) {
            pwm_prev += pwm_int;

            if (pwm_count == 255) {
                // digitalWrite(LED_R, LOW);
                // digitalWrite(LED_G, LOW);
                // digitalWrite(LED_B, LOW);

                PORTB &= ~(1 << PB4 | 1 << PB3 | 1 << PB1);

                pwm_count = 0;

                if (changed) {
                    changed      = false;
                    pwm_color[0] = new_color[0];
                    pwm_color[1] = new_color[1];
                    pwm_color[2] = new_color[2];
                }
            } else {
                // if (pwm_count == pwm_color[0]) digitalWrite(LED_R, HIGH);
                // if (pwm_count == pwm_color[1]) digitalWrite(LED_G, HIGH);
                // if (pwm_count == pwm_color[2]) digitalWrite(LED_B, HIGH);

                PORTB |= ((pwm_count == pwm_color[0])<<PB4)
                         | ((pwm_count == pwm_color[1])<<PB3)
                         | ((pwm_count == pwm_color[2])<<PB1);

                ++pwm_count;
            }
        }
    }
}