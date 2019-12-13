/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "button.h"
#include "config.h"
#include <avr/io.h>

namespace button {
    void begin() {
        DDRB |= (1 << PB4);
    }

    bool pressed() {
        return !(PORTB & (1 << PB4));
    }
}