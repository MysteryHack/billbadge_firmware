/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "player.h"

#include "config.h"
#include "debug.h"
#include "led.h"
#include "team.h"
#include "ir.h"

namespace player {
    team_t* team = NULL;

    unsigned long prev_update   = 0;
    unsigned long timeout_begin = 0;

    unsigned long wololo_time = 0;

    uint8_t wololo_count = 0;

    uint8_t step     = 0;
    int8_t  step_add = 1;

    void set_team(team_t* t) {
        if (t) {
            team = t;

            ++team->counter;

            led::color(team->dimm);

            step     = 0;
            step_add = 1;

            debug("Team=");
            debug(team->name);
            debug(" ");
            debugln(team->code, HEX);

            timeout_begin = millis();
        }
    }

    void begin() {
        set_team(team::get_random());
        debugln("Player initialized");
    }

    void update() {
        if (millis() - prev_update >= PLAYER_UPDATE) {
            prev_update += PLAYER_UPDATE;

            // Fading magic: (Max-Min)/Steps * CurrentStep + Min
            color_t new_color {
                (team->bright.r - team->dimm.r)/float(255) * step + team->dimm.r,
                (team->bright.g - team->dimm.g)/float(255) * step + team->dimm.g,
                (team->bright.b - team->dimm.b)/float(255) * step + team->dimm.b
            };

            led::color(new_color);

            step += step_add;

            if ((step == 0) || (step == 255)) {
                step_add = -step_add;
            }

            /*
               debug(step);
               debug("=");
               debug(new_color.r);
               debug(" ");
               debug(new_color.g);
               debug(" ");
               debugln(new_color.b);
             */
        }
    }

    void wololo() {
        if (team) {
            unsigned long m = millis();

            if (m - wololo_time >= WOLOLO_TIMEOUT) {
                wololo_count = 0;
            }

            if ((wololo_count < WOLOLO_MAX) && (m - wololo_time >= WOLOLO_DELAY)) {
                wololo_time = m;
                ++wololo_count;

                // led::digital(0, 0, 0);

                ir::send(team->code);

                debug("Sending team ");
                debug(team->name);
                debug(" ");
                debug(team->code, HEX);
                debug(" ");
                debugln(wololo_count);
            }
        }
    }

    void convert(uint32_t code) {
        if ((millis() - timeout_begin >= PLAYER_TIMEOUT) && (code != team->code)) {
            if (team::validate_code(code)) {
                set_team(team::from_code(code));
            }
        }
    }
}