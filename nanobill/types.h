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
    const uint32_t code;
    const color_t  dimm;
    const color_t  bright;
    uint8_t        counter;
} team_color_t;