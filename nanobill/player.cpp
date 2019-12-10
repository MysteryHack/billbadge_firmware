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
    team_t team;

    unsigned long prev_update   = 0;
    unsigned long timeout_begin = 0;

    uint8_t step     = 0;
    int8_t  step_add = 1;

    void set_team(team_t t) {
        team::increase(t.code);

        team = t;

        led::color(team.dimm);
        step     = 0;
        step_add = 1;

        debug("Team=");
        debug(team.name);
        debug(" ");
        debugln(team.code, HEX);

        timeout_begin = millis();
    }

    void begin() {
        set_team(team::get_random());
        debugln("Player initialized");
    }

    void update() {
        if (millis() - prev_update >= PLAYER_UPDATE) {
            prev_update += PLAYER_UPDATE;

            color_t new_color;

            // Fading magic: (Max-Min)/Steps * CurrentStep + Min
            new_color.r = (team.bright.r - team.dimm.r)/float(255) * step + team.dimm.r;
            new_color.g = (team.bright.g - team.dimm.g)/float(255) * step + team.dimm.g;
            new_color.b = (team.bright.b - team.dimm.b)/float(255) * step + team.dimm.b;

            led::color(new_color);

            step += step_add;

            if ((step == 0) || (step == 255)) {
                step_add = -step_add;
            }

            /*
                        debug(perc);
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
        led::digital(0, 0, 0);

        ir::send(team.code);

        debug("Sending team ");
        debug(team.name);
        debug(" ");
        debugln(team.code, HEX);

        delay(IR_SEND_DELAY);
    }

    void convert(uint32_t code) {
        if ((millis() - timeout_begin >= PLAYER_TIMEOUT) && (code != team.code)) {
            if (team::validate_code(code)) {
                set_team(team::from_code(code));
            }
        }
    }
}