/*
   Copyright (c) 2019 MysteryH4ck
   This software is licensed under the MIT License. See the license file for details.
   Source: github.com/spacehuhn/bill
 */

#pragma once

#include <Arduino.h>

#ifdef ENABLE_DEBUG

#define debug_init() DEBUG_PORT.begin(DEBUG_BAUD);\
    DEBUG_PORT.setTimeout(200);

#define debug(...) DEBUG_PORT.print(__VA_ARGS__)
#define debugln(...) DEBUG_PORT.println(__VA_ARGS__)

#else /* ifdef ENABLE_DEBUG */

#define debug_init() 0

#define debug(...) 0
#define debugln(...) 0

#endif /* ifdef ENABLE_DEBUG */