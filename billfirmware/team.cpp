/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "team.h"

#include "config.h"

namespace team {
    team_t r = { 'R', 0, 0x523D, { 40, 0, 0 }, { 255, 0, 0 } };    // r3d
    team_t y = { 'Y', 1, 0x5910, { 50, 25, 0 }, { 240, 70, 0 } };  // y10
    team_t g = { 'G', 2, 0x6772, { 0, 35, 0 }, { 0, 170, 0 } };    // gr
    team_t c = { 'C', 3, 0xC794, { 0, 15, 60 }, { 0, 100, 130 } }; // cya
    team_t b = { 'B', 4, 0xB6C0, { 0, 0, 40 }, { 0, 0, 255 } };    // blo
    team_t p = { 'P', 5, 0x701C, { 50, 0, 15 }, { 255, 0, 150 } }; // p1c

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