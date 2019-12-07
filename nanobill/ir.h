/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "stdint.h"

namespace ir {
    void begin();
    int update();
    uint32_t get_msg();
    void send(uint32_t code);
}