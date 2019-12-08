/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "config.h"
#include "types.h"
#include "debug.h"
#include "led.h"
#include "button.h"
#include "ir.h"
#include "player.h"
#include "team.h"

void setup() {
    debug_init();
    debugln("Booting Bill");

    ir::begin();
    led::begin();
    button::begin();

    player::begin();
}

void loop() {
    if (button::pressed()) {
        player::wololo();
    } else if (ir::update()) {
        player::convert(team::from_code(ir::get_msg()));
    }
}