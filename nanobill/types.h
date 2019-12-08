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
    char     name;
    uint32_t code;
    color_t  dimm;
    color_t  bright;
} team_color_t;

typedef struct player_t {
    team_t* team;
    color_t color;
    uint8_t fperc;
} player_t;