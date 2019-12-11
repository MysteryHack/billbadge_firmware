/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "eeprom.h"

#include "config.h"

// Used to verify memory
typedef struct boot_t {
    unsigned int magic_num : 32;
    unsigned int boot_num  : 8;
} boot_t;

namespace eeprom {
    void begin() {
        EEPROM.begin();

        boot_t b;

        EEPROM.get(EEPROM_BOOT_ADDR, b);

        if ((b.magic_num == BOOT_MAGIC_NUM) && (b.boot_num < 3)) {
            save(EEPROM_BOOT_ADDR, boot_t { BOOT_MAGIC_NUM, ++b.boot_num });
            return;
        } else {
            save(EEPROM_BOOT_ADDR, boot_t { BOOT_MAGIC_NUM, 1 });
        }
    }

    void end() {
        EEPROM.end();
    }
};