/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "types.h"

bool operator==(const color_t& c1, const color_t& c2) {
    return c1.r == c2.r && c1.g == c2.g && c1.b == c2.b;
}

bool operator!=(const color_t& c1, const color_t& c2) {
    return !(c1 == c2);
}

bool operator==(const team_t& t1, const team_t& t2) {
    return t1.name == t2.name && t1.code == t2.code && t1.dimm == t2.dimm && t1.bright == t2.bright;
}

bool operator!=(const team_t& t1, const team_t& t2) {
    return !(t1 == t2);
}