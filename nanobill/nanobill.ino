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

team_t red    = { 'R', 0xFFFFFF01, { 40, 0, 0 }, { 255, 0, 0 } };
team_t yellow = { 'Y', 0xFFFFFF02, { 40, 45, 0 }, { 255, 255, 0 } };
team_t green  = { 'G', 0xFFFFFF03, { 0, 50, 0 }, { 0, 255, 0 } };
team_t cyan   = { 'C', 0xFFFFFF04, { 0, 15, 60 }, { 0, 130, 170 } };
team_t blue   = { 'B', 0xFFFFFF05, { 0, 0, 40 }, { 0, 0, 255 } };
team_t pink   = { 'P', 0xFFFFFF06, { 50, 0, 15 }, { 255, 0, 150 } };

player_t player;

team_t* get_random_team() {
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    randomSeed(analogRead(A1) + analogRead(A2) + analogRead(A3) + analogRead(A4) + analogRead(A5));

    int rteam = random(1, 7);

    if (rteam == 1) return &red;
    if (rteam == 2) return &yellow;
    if (rteam == 3) return &green;
    if (rteam == 4) return &cyan;
    if (rteam == 5) return &blue;
    if (rteam == 6) return &pink;

    debug("AAAAAAAH THIS IS NOT SUPPOSE TO HAPPEN!");
    return &red;
}

team_t* get_team(uint32_t code) {
    if (code == red.code) return &red;
    if (code == yellow.code) return &yellow;
    if (code == green.code) return &green;
    if (code == cyan.code) return &cyan;
    if (code == blue.code) return &blue;
    if (code == pink.code) return &pink;

    return NULL;
}

void player_init() {
    player.team  = get_random_team();
    player.color = player.team->bright;
    player.fperc = 100;

    led::color(player.color.r, player.color.g, player.color.b);

    debugln("Player initialized");
    debug("Team=");
    debugln(player.team->name);
}

void update_player() {
    led::color(player.color.r, player.color.g, player.color.b);
}

void setup() {
    debug_init();
    debugln("Booting Bill");

    led::begin();
    button::begin();
    ir::begin();

    player_init();
}

void loop() {
    if (button::pressed()) {
        player.color = player.team->bright;
        player.fperc = 100;
        led::color(player.color.r, player.color.g, player.color.b);

        ir::send(player.team->code);

        debug("Sending team");
        debug(player.team->name);
        debug(" ");
        debugln(player.team->code, HEX);

        delay(IR_SEND_DELAY);
    } else if (ir::update()) {
        uint32_t code = ir::get_msg();

        debug("Received ");
        debug(code, HEX);

        team_t* team = get_team(code);

        if (team && (team != player.team)) {
            debug(" ");
            debug(team->name);

            player.team  = team;
            player.color = player.team->bright;
            player.fperc = 100;
            led::color(player.color.r, player.color.g, player.color.b);
        }

        debugln();

        ir::update();
    }
}