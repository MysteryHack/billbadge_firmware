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

// Time in ms after each signal sent
#define IR_SEND_DELAY 200

// Button pin
#define BTN 6

// Infrared receive and send pin
#define IR_RECEIVE 7
#define IR_SEND 3

// RGB LED pins
#define LED_R 11
#define LED_G 10
#define LED_B 9