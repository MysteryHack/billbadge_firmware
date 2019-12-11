/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#pragma once

/* ===== DEBUG ===== */
#define ENABLE_DEBUG
#define DEBUG_PORT Serial
#define DEBUG_BAUD 115200

/* ===== HARDWARE ===== */
#define BTN 6 // Button pin

// Infrared receive and send pin
#define IR_RECEIVE 7
#define IR_SEND 3

// RGB LED pins
#define LED_R 11
#define LED_G 10
#define LED_B 9

#define PWM_HZ 120 // PWM speed in hz

/*! ===== EEPROM ===== */
#define EEPROM_BOOT_ADDR  432
#define BOOT_MAGIC_NUM    1234567890

/* ===== PLAYER ===== */
#define WOLOLO_MAX 5         // Times you can send a signal before delay
#define WOLOLO_DELAY 200     // Time in ms after each signal sent
#define WOLOLO_TIMEOUT 5000  // Time in ms after exceeding amount of sents
#define PLAYER_UPDATE 20     // Fading time for each step in ms
#define PLAYER_TIMEOUT 10000 // Time in ms until player can change teams

#define UNICORN_UPDATE 30

#define SAVE_PLAYER_STATS

// Preflashed Player color (r,y,g,c,b,p) comment out for random color
// #define PLAYER_COLOR c