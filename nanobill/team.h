/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#pragma once

#include "types.h"

namespace team {
    bool validate_code(uint32_t code);

    team_t* get_random();
    team_t* from_code(uint32_t code);

    bool unicorn();
}