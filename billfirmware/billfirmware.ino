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

void unicorn_loop() {
    while (1) {
        if (button::pressed()) {
            unicorn::wololo();
        } else {
            unicorn::recharge();

            if (ir::update()) {
                uint16_t msg = ir::get_msg();
                if (msg == PARTY_CODE) {
                    unicorn::party();
                } else if (msg == PARTY_HARD_CODE) {
                    unicorn::party_hard();
                }
            }
        }

        unicorn::update();
        led::update();
    }
}

void player_loop() {
    while (1) {
        if (button::pressed()) {
            player::wololo();
        } else {
            player::recharge();

            if (ir::update()) {
                uint16_t msg = ir::get_msg();

                if (msg == PARTY_CODE) {
                    unicorn::party();
                } else if (msg == PARTY_HARD_CODE) {
                    unicorn::party_hard();
                } else {
                    player::convert(msg);
                }
            }
        }

        player::update();
        led::update();
    }
}

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
        unicorn_loop();
    } else {
        player_loop();
    }
}

void loop() {}