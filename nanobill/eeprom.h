/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#pragma once

#include <EEPROM.h>

namespace eeprom {
    void begin();
    void end();

    template<typename T>
    void save(const int address, const T& t) {
        EEPROM.put(address, t);
    }

    template<typename T>
    void get(const int address, const T& t) {
        EEPROM.get(address, t);
    }
};