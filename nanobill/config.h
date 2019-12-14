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
#define RANDOM_SEED

/* ===== HARDWARE ===== */
#define BUTTON_MODE() (pinMode(BTN, INPUT_PULLUP))
#define READ_BUTTON() (digitalRead(BTN) == LOW)

#define IR_RECEIVE_MODE() (pinMode(irparams.recvpin, INPUT))
#define IR_RECEIVE_READ() ((uint8_t)digitalRead(irparams.recvpin))

#define IR_SEND_MODE() (pinMode(TIMER_PWM_PIN, OUTPUT))
#define IR_SEND_LOW() (digitalWrite(TIMER_PWM_PIN, LOW))

#define RGB_MODE() pinMode(LED_R, OUTPUT);\
    pinMode(LED_G, OUTPUT);\
    pinMode(LED_B, OUTPUT);

#define RGB_SET(r, g, b) PORTB |= (r<<PB3) | (g<<PB2) | (b<<PB1)
// digitalWrite(LED_R, r);
// digitalWrite(LED_G, g);
// digitalWrite(LED_B, b);

#define RGB_RESET() (PORTB &= ~(1<<PB3 | 1<<PB2 | 1<<PB1))
// digitalWrite(LED_R, LOW);
// digitalWrite(LED_G, LOW);
// digitalWrite(LED_B, LOW);


#define BTN 6 // Button pin

// Infrared receive and send pin
#define IR_RECEIVE 7
#define IR_SEND 3

// RGB LED pins
#define LED_R 11
#define LED_G 10
#define LED_B 9

#define PWM_HZ 120           // PWM speed in hz

/* ===== PLAYER ===== */
#define WOLOLO_MAX 5         // Times you can send a signal before delay
#define WOLOLO_DELAY 200     // Time in ms after each signal sent
#define WOLOLO_TIMEOUT 5000  // Time in ms after exceeding amount of sents

#define PLAYER_UPDATE 20     // Fading time for each step in ms
#define PLAYER_TIMEOUT 10000 // Time in ms until player can change teams

#define UNICORN_UPDATE 30    // Fading time for each rainbow step in ms

#define SAVE_PLAYER_STATS    // Save color in EEPROM

// Preflashed Player color (r,y,g,c,b,p) comment out for random color
// #define PLAYER_COLOR c