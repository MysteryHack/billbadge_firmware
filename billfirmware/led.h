/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "stdint.h"
#include "types.h"

namespace led {
    void begin();

    void enable();
    void disable();

    void digital(bool r, bool g, bool b);
    void rgb(uint8_t r, uint8_t g, uint8_t b);
    void color(const color_t& c);

    void rainbow(uint8_t pos);
    void random_color();

    void update();
}