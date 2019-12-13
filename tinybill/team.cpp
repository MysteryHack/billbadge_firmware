/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "team.h"

#include "config.h"

namespace team {
    team_t r = { 'R', 0, 0xef301c9a, { 30, 0, 0 }, { 255, 0, 0 } };
    team_t y = { 'Y', 1, 0x8187745d, { 30, 10, 0 }, { 255, 40, 0 } };
    team_t g = { 'G', 2, 0xcad2655e, { 0, 4, 0 }, { 0, 50, 0 } };
    team_t c = { 'C', 3, 0x4ad7d0a9, { 0, 18, 14 }, { 0, 65, 100 } };
    team_t b = { 'B', 4, 0x7da81da1, { 0, 0, 10 }, { 0, 0, 200 } };
    team_t p = { 'P', 5, 0x6c45e2dd, { 40, 0, 10 }, { 255, 0, 150 } };

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
        return &r;
#endif // ifdef PLAYER_COLOR
    }

    team_t* from_code(uint32_t code) {
        if (code == r.code) return &r;
        if (code == y.code) return &y;
        if (code == g.code) return &g;
        if (code == c.code) return &c;
        if (code == b.code) return &b;
        if (code == p.code) return &p;

        return 0;
    }
}