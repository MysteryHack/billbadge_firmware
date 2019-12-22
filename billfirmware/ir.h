/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "stdint.h"

namespace ir {
    void begin();
    bool update();

    uint16_t get_msg();

    void send(uint16_t code);
}