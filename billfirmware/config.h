/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#pragma once

// =========== GAME CONFIG ========= //
#define PWM_HZ 120           // PWM speed in hz

#define WOLOLO_MAX 5         // Times you can send a signal before delay
#define WOLOLO_DELAY 200     // Time in ms after each signal sent
#define WOLOLO_TIMEOUT 5000  // Time in ms after exceeding amount of sents

#define PLAYER_UPDATE 20     // Fading time for each step in ms
#define PLAYER_TIMEOUT 10000 // Time in ms until player can change teams

#define UNICORN_UPDATE 30    // Fading time for each rainbow step in ms

#define SAVE_PLAYER_STATS    // Save color in EEPROM

#define PLAYER_COLOR c

// =========== ARDUINO NANO CONFIG ========= //
#if (ARDUINO_==AVR_ATTINYX5)
/* ===== HARDWARE ===== */
  #define BUTTON_MODE() DDRB |= (0 << DDB5); PORTB |= (1 << PB5);
  #define BUTTON_READ() (PINB & (1 << PINB5)) == 0

  #define IR_RECEIVE_MODE() DDRB |= (0 << DDB2);
  #define IR_RECEIVE_READ() (PINB & (1 << PINB2)) != 0

  #define IR_SEND_MODE() DDRB |= (1 << DDB1);
  #define IR_SEND_LOW() PORTB &= ~(1 << PB1);

  #define RGB_MODE() DDRB |= (1<<PB4 | 1<<PB3 | 1<<PB0);
  #define RGB_SET(rx, gx, bx) (PORTB |= (rx<<PB4) | (gx<<PB3) | (bx<<PB0))
  #define RGB_RESET() (PORTB &= ~(1<<PB4 | 1<<PB3 | 1<<PB0))

// =========== ATTINY85 CONFIG ========= //
#elif (ARDUINO_==AVR_NANO)
/* ===== DEBUG ===== */
  #define ENABLE_DEBUG
  #define DEBUG_PORT Serial
  #define DEBUG_BAUD 115200

/* ===== HARDWARE ===== */
  #define BUTTON_MODE() DDRD |= (0 << DDD6); PORTD |= (1 << PD6);
  #define BUTTON_READ() (PIND & (1 << PIND6)) == 0

  #define IR_RECEIVE_MODE() DDRD |= (0 << DDD7);
  #define IR_RECEIVE_READ() (PIND & (1 << PIND7)) != 0

  #define IR_SEND_MODE() DDRD |= (1 << DDD3);
  #define IR_SEND_LOW() PORTD &= ~(1 << PD3);

  #define RGB_MODE() DDRB |= (1<<PB3 | 1<<PB2 | 1<<PB1);
  #define RGB_SET(r, g, b) (PORTB |= (r<<PB3) | (g<<PB2) | (b<<PB1))
  #define RGB_RESET() (PORTB &= ~(1<<PB3 | 1<<PB2 | 1<<PB1))
#else  /* if (ARDUINO_==AVR_ATTINYX5) */
  #error Compile for Arduino Nano or Attiny85
#endif /* ifdef USE_NANO */