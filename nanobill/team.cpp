/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "team.h"

#include <Arduino.h>
#include "debug.h"
#include "config.h"

namespace team {
    team_t r = { 'R', 0xFFFFFF01, { 30, 0, 0 }, { 255, 0, 0 }, 0 };
    team_t y = { 'Y', 0xFFFFFF02, { 30, 10, 0 }, { 255, 40, 0 }, 0 };
    team_t g = { 'G', 0xFFFFFF03, { 0, 4, 0 }, { 0, 50, 0 }, 0 };
    team_t c = { 'C', 0xFFFFFF04, { 0, 18, 14 }, { 0, 65, 100 }, 0 };
    team_t b = { 'B', 0xFFFFFF05, { 0, 0, 10 }, { 0, 0, 200 }, 0 };
    team_t p = { 'P', 0xFFFFFF06, { 40, 0, 10 }, { 255, 0, 150 }, 0 };

    bool validate_code(uint32_t code) {
        return code == r.code
               || code == y.code
               || code == g.code
               || code == c.code
               || code == b.code
               || code == p.code;
    }

    team_t* get_random() {
#ifdef PLAYER_COLOR
        return &PLAYER_COLOR;
#else // ifdef PLAYER_COLOR
        pinMode(A1, INPUT);
        pinMode(A2, INPUT);
        pinMode(A3, INPUT);
        randomSeed(analogRead(A1) + analogRead(A2) + analogRead(A3));

        int rteam = random(1, 7);

        if (rteam == 1) return &r;
        if (rteam == 2) return &y;
        if (rteam == 3) return &g;
        if (rteam == 4) return &c;
        if (rteam == 5) return &b;
        /*if (rteam == 6) */ return &p;
#endif // ifdef PLAYER_COLOR
    }

    team_t* from_code(uint32_t code) {
        if (code == r.code) return &r;
        if (code == y.code) return &y;
        if (code == g.code) return &g;
        if (code == c.code) return &c;
        if (code == b.code) return &b;
        if (code == p.code) return &p;

        return NULL; // team_t();
    }

    bool unicorn() {
        return r.counter && y.counter && g.counter && c.counter && b.counter && p.counter;
    }
}