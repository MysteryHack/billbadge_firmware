/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "team.h"

#include "config.h"

namespace team {
    team_t r = { 'R', 0, 0xef30, { 40, 0, 0 }, { 255, 0, 0 } };
    team_t y = { 'Y', 1, 0x8187, { 50, 25, 0 }, { 240, 70, 0 } };
    team_t g = { 'G', 2, 0xcad2, { 0, 35, 0 }, { 0, 170, 0 } };
    team_t c = { 'C', 3, 0x4ad7, { 0, 15, 60 }, { 0, 100, 130 } };
    team_t b = { 'B', 4, 0x7da8, { 0, 0, 40 }, { 0, 0, 255 } };
    team_t p = { 'P', 5, 0x6c45, { 50, 0, 15 }, { 255, 0, 150 } };

    bool validate_code(uint16_t code) {
        return code == r.code
               || code == y.code
               || code == g.code
               || code == c.code
               || code == b.code
               || code == p.code;
    }

    team_t* get_random() {
        return &PLAYER_COLOR;
    }

    team_t* from_code(uint16_t code) {
        if (code == r.code) return &r;
        if (code == y.code) return &y;
        if (code == g.code) return &g;
        if (code == c.code) return &c;
        if (code == b.code) return &b;
        if (code == p.code) return &p;

        return NULL; // team_t();
    }
}