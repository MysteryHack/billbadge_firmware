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
    player_t p;

    void begin() {
        convert(team::pick_random());
        debugln("Player initialized");
    }

    void update() {
        led::color(p.color);
    }

    void wololo() {
        ir::send(p.team.code);

        debug("Sending team ");
        debug(p.team.name);
        debug(" ");
        debugln(p.team.code, HEX);

        delay(IR_SEND_DELAY);
    }

    void convert(team_t t) {
        if (team::validate(t) && (t != p.team)) {
            p.team  = t;
            p.color = t.dimm;
            p.fperc = 0;

            debug("Team=");
            debug(p.team.name);
            debug(" ");
            debugln(p.team.code, HEX);

            update();
        }
    }
}