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
#include "eeprom.h"

#define PLAYER_MAGIC_NUM 123
#define UNICORN_MASK 0x3F

namespace player {
    player_t p;

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

            p.team_code        = team->code;
            p.team_collection |= 1<<team->bit;

#ifdef SAVE_PLAYER_STATS
            eeprom::save(0, p);
#endif // ifdef SAVE_PLAYER_STATS

            led::color(team->dimm);

            step     = 0;
            step_add = 1;

            debug("Team=");
            debug(team->name);
            debug(" ");
            debugln(team->code, HEX);
            debug("Collected teams: ");
            debugln(p.team_collection, BIN);

            timeout_begin = millis();
        }
    }

    void begin() {
#ifdef SAVE_PLAYER_STATS
        eeprom::get(0, p);

        if (p.magic_num == PLAYER_MAGIC_NUM) {
            set_team(team::from_code(p.team_code));
        } else {
#endif // ifdef SAVE_PLAYER_STATS
        p.magic_num       = PLAYER_MAGIC_NUM;
        p.team_collection = 0;
        set_team(team::get_random());

#ifdef SAVE_PLAYER_STATS
    }

#endif // ifdef SAVE_PLAYER_STATS

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

    bool unicorn() {
        return p.team_collection == UNICORN_MASK;
    }
}