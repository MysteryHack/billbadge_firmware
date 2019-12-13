/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#pragma once

#include "stdint.h"

typedef struct color_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} color_t;

typedef struct team_t {
    const char     name;
    const uint8_t  bit;
    const uint32_t code;
    const color_t  dimm;
    const color_t  bright;
} team_color_t;

typedef struct player_t {
    uint8_t  magic_num;
    uint8_t  team_collection;
    uint32_t team_code;
} player_t;