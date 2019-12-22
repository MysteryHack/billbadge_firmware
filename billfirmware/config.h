/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#pragma once

#include <Arduino.h>

// =========== GAME CONFIG ========= //
#define PWM_HZ 140             // PWM speed in hz

#define WOLOLO_DELAY 200       // Time in ms after each signal sent
#define WOLOLO_MAX 5           // Max. signals that can be send in a row

#define PLAYER_UPDATE 15       // Fading time for each step in ms
#define PLAYER_COLOR r         // Start color of player

#define SAVE_PLAYER_STATS      // Save color in EEPROM

#define UNICORN_UPDATE 30      // Fading time for each rainbow step in ms

#define PARTY_CODE 0x42c3      // Party signal IR code
#define PARTY_HARD_CODE 0x36c3 // Party hard signal IR code
#define PARTY_TIME 10000       // How long the party will last in ms
#define PARTY_UPDATE 10        // Fading time for each rainbow step in ms

// =========== ATTINY85 CONFIG ========= //
#if defined(__AVR_ATtiny85__)
/* ===== DEBUG ===== */
  #define debug_init() 0
  #define debug(...) 0
  #define debugln(...) 0

/* ===== HARDWARE ===== */
  #define BUTTON_MODE() ({\
        DDRB |= (0 << DDB5);\
        PORTB |= (1 << PB5);\
    })
  #define BUTTON_READ() ((PINB & (1 << PINB5)) == 0)

  #define IR_RECEIVE_MODE() (DDRB |= (0 << DDB2))
  #define IR_RECEIVE_READ() ((PINB & (1 << PINB2)) != 0)

  #define IR_SEND_MODE() (DDRB |= (1 << DDB1))
  #define IR_SEND_LOW() (PORTB &= ~(1 << PB1))

  #define RGB_MODE() (DDRB |= (1<<PB4 | 1<<PB3 | 1<<PB0))
  #define RGB_SET(rx, gx, bx) (PORTB |= (rx<<PB4) | (gx<<PB3) | (bx<<PB0))
  #define RGB_RESET() (PORTB &= ~(1<<PB4 | 1<<PB3 | 1<<PB0))

// =========== ARDUINO NANO CONFIG ========= //
#else /* if defined(__AVR_ATtiny85__) */
/* ===== DEBUG ===== */
  #define debug_init() Serial.begin(115200)
  #define debug(...) Serial.print(__VA_ARGS__)
  #define debugln(...) Serial.println(__VA_ARGS__)

/* ===== HARDWARE ===== */
  #define BUTTON_MODE() ({\
        DDRD |= (0 << DDD6);\
        PORTD |= (1 << PD6);\
    })
  #define BUTTON_READ() ((PIND & (1 << PIND6)) == 0)

  #define IR_RECEIVE_MODE() (DDRD |= (0 << DDD7))
  #define IR_RECEIVE_READ() ((PIND & (1 << PIND7)) != 0)

  #define IR_SEND_MODE() (DDRD |= (1 << DDD3))
  #define IR_SEND_LOW() (PORTD &= ~(1 << PD3))

  #define RGB_MODE() (DDRB |= (1<<PB3 | 1<<PB2 | 1<<PB1))
  #define RGB_SET(r, g, b) (PORTB |= (r<<PB3) | (g<<PB2) | (b<<PB1))
  #define RGB_RESET() (PORTB &= ~(1<<PB3 | 1<<PB2 | 1<<PB1))
#endif /* if defined(__AVR_ATtiny85__) */