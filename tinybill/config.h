/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#pragma once

/* ===== HARDWARE ===== */
#define PWM_HZ 100           // PWM speed in hz

/* ===== PLAYER ===== */
#define WOLOLO_MAX 5         // Times you can send a signal before delay
#define WOLOLO_DELAY 200     // Time in ms after each signal sent
#define WOLOLO_TIMEOUT 5000  // Time in ms after exceeding amount of sents

#define PLAYER_UPDATE 20     // Fading time for each step in ms
#define PLAYER_TIMEOUT 10000 // Time in ms until player can change teams

#define UNICORN_UPDATE 30    // Fading time for each rainbow step in ms

#define SAVE_PLAYER_STATS    // Save color in EEPROM

// Preflashed Player color (r,y,g,c,b,p) comment out for random color
#define PLAYER_COLOR c