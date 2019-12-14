/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "button.h"
#include "config.h"
#include "debug.h"
#include <Arduino.h>

namespace button {
    void begin() {
        BUTTON_MODE();
        debugln("Button initialized");
    }

    bool pressed() {
        return READ_BUTTON();
    }
}