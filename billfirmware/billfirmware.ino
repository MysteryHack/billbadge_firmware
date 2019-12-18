/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "config.h"
#include "eeprom.h"
#include "ir.h"
#include "led.h"
#include "button.h"
#include "player.h"
#include "unicorn.h"

void setup() {
    debug_init();
    debugln("Booting Bill... please stand by...");

    eeprom::begin();
    ir::begin();
    led::begin();
    button::begin();
    player::begin();
    unicorn::begin();

    debugln("Bill up and running!");

    if (unicorn::enabled()) {
        while (1) {
            unicorn::update();
            led::update();
        }
    }
}

void loop() {
    if (button::pressed()) {
        player::wololo();
    } else if (ir::update()) {
        player::convert(ir::get_msg());
    }

    player::update();
    led::update();
}
