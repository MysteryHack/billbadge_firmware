/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#pragma once

// Serial debugging
#define ENABLE_DEBUG
#define DEBUG_PORT Serial
#define DEBUG_BAUD 115200

// Times you can send a signal before delay
#define WOLOLO_MAX 5

// Time in ms after each signal sent
#define WOLOLO_DELAY 200

// Time in ms after exceeding amount of sents
#define WOLOLO_TIMEOUT 5000

// Button pin
#define BTN 6

// Infrared receive and send pin
#define IR_RECEIVE 7
#define IR_SEND 3

// RGB LED pins
#define LED_R 11
#define LED_G 10
#define LED_B 9

// PWM speed in hz
#define PWM_HZ 120

// Fading time for each step in ms
#define PLAYER_UPDATE 20

// Time in ms until player can change teams
#define PLAYER_TIMEOUT 10000

// Preflashed Player color (r,y,g,c,b,p) comment out for random color
// #define PLAYER_COLOR c