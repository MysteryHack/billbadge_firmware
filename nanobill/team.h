/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#pragma once

#include "types.h"

namespace team {
    /*
       team_t red();
       team_t yellow();
       team_t green();
       team_t cyan();
       team_t blue();
       team_t pink();
     */
    bool validate(const team_t& t);

    team_t pick_random();
    team_t from_code(uint32_t code);
}