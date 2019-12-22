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
#include "ir.h"

namespace unicorn {
    unsigned long update_time = 0;
    unsigned long wololo_time = 0;

    uint8_t pos          = 0;
    uint8_t wololo_count = WOLOLO_MAX;

    bool en = false;

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

        if (m - update_time >= UNICORN_UPDATE) {
            update_time = m;

            led::rainbow(pos++);

            if (pos == 255) pos = 0;
        }
    }

    bool enabled() {
        return en;
    }

    void party() {
        debugln("Starting party!");

        unsigned long start_time = millis();
        unsigned long m;

        while (millis() - start_time < PARTY_TIME) {
            m = millis();

            if (m - update_time >= PARTY_UPDATE) {
                update_time = m;

                led::rainbow(pos++);

                if (pos == 255) pos = 0;
            }

            led::update();
        }

        ir::update();

        debugln("Party ended :(");
    }

    void wololo() {
        unsigned long m = millis();

        if ((wololo_count < WOLOLO_MAX) && (m - wololo_time >= WOLOLO_DELAY)) {
            debug("Sending party ");
            debugln(PARTY_CODE, HEX);

            ir::send(PARTY_CODE);

            ++wololo_count;
            wololo_time = m;
        }
    }

    void recharge() {
        wololo_count = 0;
    }
}