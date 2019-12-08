/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#include "ir.h"
#include "config.h"
#include "debug.h"
#include <IRremote.h>

namespace ir {
    IRsend irsend;
    IRrecv irrecv(IR_RECEIVE);

    decode_results results;
    uint32_t msg;

    void begin() {
        irrecv.enableIRIn();
        debugln("IR initialized");
    }

    bool update() {
        if (irrecv.decode(&results)) {
            msg = results.value;

            debug("Received ");
            debugln(msg, HEX);

            irrecv.resume();

            return true;
        }

        return false;
    }

    uint32_t get_msg() {
        return msg;
    }

    void send(uint32_t code) {
        // irsend.sendNEC(code, 32); // kinda sucks
        irsend.sendRC5(code, 32); // ok
        // irsend.sendRC6(code, 32); // sucks
        // irsend.sendSAMSUNG(code, 32); // sucks hard
        // irsend.sendSony(code, 32); // meh

        irrecv.enableIRIn();
    }
}