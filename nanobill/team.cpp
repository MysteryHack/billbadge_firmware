/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "team.h"

#include <Arduino.h>
#include "debug.h"

namespace team {
    const team_t nt = { '0', 0x00000000, { 0, 0, 0 }, { 0, 0, 0 } };

    const PROGMEM  team_t r = { 'R', 0xFFFFFF01, { 40, 0, 0 }, { 255, 0, 0 } };
    const PROGMEM  team_t y = { 'Y', 0xFFFFFF02, { 40, 45, 0 }, { 255, 255, 0 } };
    const PROGMEM  team_t g = { 'G', 0xFFFFFF03, { 0, 50, 0 }, { 0, 255, 0 } };
    const PROGMEM  team_t c = { 'C', 0xFFFFFF04, { 0, 15, 60 }, { 0, 130, 170 } };
    const PROGMEM  team_t b = { 'B', 0xFFFFFF05, { 0, 0, 40 }, { 0, 0, 255 } };
    const PROGMEM  team_t p = { 'P', 0xFFFFFF06, { 50, 0, 15 }, { 255, 0, 150 } };

    /*
        team_t red() {
            return r;
        }

        team_t yellow() {
            return y;
        }

        team_t green() {
            return g;
        }

        team_t cyan() {
            return c;
        }

        team_t blue() {
            return b;
        }

        team_t pink() {
            return p;
        }*/
    bool validate(const team_t& t) {
        return t == r || t == y || t == g || t == c || t == b || t == p;
    }

    team_t pick_random() {
        pinMode(A1, INPUT);
        pinMode(A2, INPUT);
        pinMode(A3, INPUT);
        pinMode(A4, INPUT);
        randomSeed(analogRead(A1) + analogRead(A2) + analogRead(A3) + analogRead(A4) + analogRead(A5));

        int rteam = random(1, 7);

        if (rteam == 1) return r;
        if (rteam == 2) return y;
        if (rteam == 3) return g;
        if (rteam == 4) return c;
        if (rteam == 5) return b;
        if (rteam == 6) return p;

        return r;
    }

    team_t from_code(uint32_t code) {
        if (code == r.code) return r;
        if (code == y.code) return y;
        if (code == g.code) return g;
        if (code == c.code) return c;
        if (code == b.code) return b;
        if (code == p.code) return p;

        return team_t();
    }
}