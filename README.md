# Bill Badge
MysteryH4ck Bill Cipher Badge 36c3

## Links & Tools

Arduino IDE (required): https://www.arduino.cc/en/Main/Software

Attiny85 Core (required): https://github.com/SpenceKonde/ATTinyCore

Arduino IR library (optional): https://github.com/z3t0/Arduino-IRremote

Tiny IR library (optional): https://gist.github.com/SeeJayDee/caa9b5cc29246df44e45b8e7d1b1cdc5

## Setup & Compilation

Install Attiny85 Core, edit  `...\packages\ATTinyCore\hardware\avr\1.3.2\variants\tinyX5\pins_arduino.h`
and change line 108 to `#define TIMER_TO_USE_FOR_MILLIS                   1`.  

Under tools select:  
* `Board: "ATtiny25/45/85"`
* `Chip: "ATtiny85"`
* `Clock: "16 MHz (PLL)"`
* `B.O.D. Level: "B.O.D Disabled"`
* `Save EEPROM: "EEPROM retained"`
* `Timer 1 Clock: "64MHz"`
* `LTO(1.6.11+ only): "Enabled"`
* `millis()/micros(): "Enabled"`

Fuses:  

`AVRDUDE -U lfuse:w:0xD1:m -U hfuse:w:0xDF:m`

* LFUSE=D1
* HFUSE=DF
* EFUSE=FF

Fuse calculator: http://eleccelerator.com/fusecalc/fusecalc.php?chip=attiny85

## Pinout

### Arduino Nano Prototype

| Function   | AVR Pin | Arduino Pin |
| ---------- | ------- | ----------- |
| Button     | PD6     | D6          |
| IR Send    | PD3     | D3          |
| IR Receive | PD7     | D7          |
| LED R      | PB3     | D11         |
| LED G      | PB2     | D10         |
| LED B      | PB1     | D9          |

### Attiny85 Badge

| Function   | AVR Pin | Arduino Pin | Physical Pin |
| ---------- | ------- | ----------- | ------------ |
| Button     | PB5     | D5          | 1            |
| IR Send    | PB1     | D1          | 6            |
| IR Receive | PB2     | D2          | 7            |
| LED R      | PB4     | D4          | 3            |
| LED G      | PB3     | D3          | 2            |
| LED B      | PB0     | D0          | 5            |

![Stolen Attiny85 pinout 1](https://www.heise.de/developer/imgs/06/1/8/9/4/0/3/6/52713d5b757b7fc0658b4567-f64100a86198028c.png)
![Stolen Attiny85 pinout 2](http://homemadehardware.com/img/attiny85_pinout.jpeg)
