/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "unicorn.h"

#include "config.h"
#include "player.h"
#include "button.h"
#include "led.h"

namespace unicorn {
    unsigned long prev = 0;
    uint8_t pos        = 0;
    bool    en         = false;

    void begin() {
#ifdef SAVE_PLAYER_STATS
        if (player::unicorn()) {
#endif // ifdef SAVE_PLAYER_STATS

        uint8_t c = 0;

        while (!en && button::pressed()) {
            ++c;
            delay(50);

            if (c == 10) {
                en = true;
                debugln("Unicorn enabled!");
            }
        }

#ifdef SAVE_PLAYER_STATS
    }

#endif // ifdef SAVE_PLAYER_STATS
    }

    void update() {
        unsigned long m = millis();

        if (m - prev >= UNICORN_UPDATE) {
            prev = m;
            ++pos;

            if (pos < 85) {
                led::rgb(pos* 3, 255 - pos* 3, 0);
            } else if (pos < 170) {
                led::rgb(255 - (pos-85) * 3, 0, (pos-85)* 3);
            } else {
                led::rgb(0, (pos-170)* 3, 255 - (pos-170) * 3);
            }

            if (pos == 255) pos = 0;
        }
    }

    bool enabled() {
        return en;
    }
}