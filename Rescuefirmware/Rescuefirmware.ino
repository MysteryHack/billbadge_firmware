// AVR High-voltage Serial Fuse Reprogrammer
// Adapted from code and design by Paul Willoughby 03/20/2010
// http://www.rickety.us/2010/03/arduino-avr-high-voltage-serial-programmer/
// Fuse Calc:
// http://www.engbedded.com/fusecalc/

#define ATTINY13_LFUSE_VALUE 0x6A
#define ATTINY13_HFUSE_VALUE 0x57

// Fuse calculator: http://eleccelerator.com/fusecalc/fusecalc.php?chip=attiny85
#define ATTINY85_LFUSE_VALUE 0xD1 // PLL=D1, default=62
#define ATTINY85_HFUSE_VALUE 0xDF // RST disabled=5F, default=DF
#define ATTINY85_EFUSE_VALUE 0xFF

#define RST 13                    // Output to level shifter for !RESET from transistor
#define SCI 12                    // Target Clock Input
#define SDO 11                    // Target Data Output
#define SII 10                    // Target Instruction Input
#define SDI 9                     // Target Data Input
#define VCC 8                     // Target VCC

#define HFUSE 0x747C
#define LFUSE 0x646C
#define EFUSE 0x666E

// Define ATTiny series signatures
#define ATTINY13 0x9007 // L: 0x6A, H: 0xFF 8 pin
#define ATTINY24 0x910B // L: 0x62, H: 0xDF, E: 0xFF 14 pin
#define ATTINY25 0x9108 // L: 0x62, H: 0xDF, E: 0xFF 8 pin
#define ATTINY44 0x9207 // L: 0x62, H: 0xDF, E: 0xFFF 14 pin
#define ATTINY45 0x9206 // L: 0x62, H: 0xDF, E: 0xFF 8 pin
#define ATTINY84 0x930C // L: 0x62, H: 0xDF, E: 0xFFF 14 pin
#define ATTINY85 0x930B // L: 0x62, H: 0xDF, E: 0xFF 8 pin

void setup() {
    pinMode(VCC, OUTPUT);
    pinMode(RST, OUTPUT);
    pinMode(SDI, OUTPUT);
    pinMode(SII, OUTPUT);
    pinMode(SCI, OUTPUT);
    pinMode(SDO, OUTPUT);    // Configured as input when in programming mode
    digitalWrite(RST, HIGH); // Level shifter is inverting, this shuts off 12V
    Serial.begin(115200);
    Serial.println("Code is modified by Spacehuhn. Visit spacehuhn.io for more projects");
    Serial.println("-------------------------------------------------------------------------------------------------");
    Serial.println("Enter button to start process..");

    pinMode(7, INPUT_PULLUP);
    pinMode(6, OUTPUT);

    digitalWrite(6, LOW);
}

void loop() {
    if (digitalRead(7) == LOW) {
        digitalWrite(6, HIGH);
        delay(100);
        start_rescue();
        delay(100);
        digitalWrite(6, LOW);
    }
}

void start_rescue() {
    Serial.println("Starting...");
    Serial.flush();

    delay(100);

    pinMode(SDO, OUTPUT); // Set SDO to output

    digitalWrite(SDI, LOW);
    digitalWrite(SII, LOW);
    digitalWrite(SDO, LOW);
    digitalWrite(RST, HIGH); // 12v Off
    digitalWrite(VCC, HIGH); // Vcc On
    delayMicroseconds(20);
    digitalWrite(RST, LOW);  // 12v On
    delayMicroseconds(10);
    pinMode(SDO, INPUT);     // Set SDO to input
    delayMicroseconds(300);
    unsigned int sig = readSignature();
    Serial.println("Reading signature from connected ATtiny......");
    Serial.println("Reading complete..");
    Serial.print("Signature is: ");
    Serial.println(sig, HEX);
    readFuses();
    if (sig == ATTINY13) {
        Serial.println("The ATtiny is detected as ATtiny13/ATtiny13A..");
        Serial.print("LFUSE: ");
        writeFuse(LFUSE, ATTINY13_LFUSE_VALUE);
        Serial.print("HFUSE: ");
        writeFuse(HFUSE, ATTINY13_HFUSE_VALUE);
        Serial.println("");
    } else if ((sig == ATTINY24) || (sig == ATTINY44) || (sig == ATTINY84) ||
               (sig == ATTINY25) || (sig == ATTINY45) || (sig == ATTINY85)) {
        Serial.println("The ATtiny is detected as ");
        if (sig == ATTINY24) Serial.println("ATTINY24..");
        else if (sig == ATTINY44) Serial.println("ATTINY44..");
        else if (sig == ATTINY84) Serial.println("ATTINY84..");
        else if (sig == ATTINY25) Serial.println("ATTINY25..");
        else if (sig == ATTINY45) Serial.println("ATTINY45..");
        else if (sig == ATTINY85) Serial.println("ATTINY85..");

        writeFuse(LFUSE, ATTINY85_LFUSE_VALUE); // 62
        writeFuse(HFUSE, ATTINY85_HFUSE_VALUE); // RST disabled=5F, default=DF
        writeFuse(EFUSE, ATTINY85_EFUSE_VALUE);
    }

    Serial.println("Fuses will be read again to check if it's changed successfully..");
    readFuses();
    digitalWrite(SCI, LOW);
    digitalWrite(VCC, LOW);  // Vcc Off
    digitalWrite(RST, HIGH); // 12v Off

    Serial.println("");
    Serial.println("");
    Serial.println("");
    Serial.println("DONE");
}

byte shiftOut(byte val1, byte val2) {
    int inBits = 0;

    // Wait until SDO goes high
    while (!digitalRead(SDO));
    unsigned int dout = (unsigned int)val1 << 2;
    unsigned int iout = (unsigned int)val2 << 2;

    for (int ii = 10; ii >= 0; ii--) {
        digitalWrite(SDI, !!(dout & (1 << ii)));
        digitalWrite(SII, !!(iout & (1 << ii)));
        inBits <<= 1; inBits |= digitalRead(SDO);
        digitalWrite(SCI, HIGH);
        digitalWrite(SCI, LOW);
    }
    return inBits >> 2;
}

void writeFuse(unsigned int fuse, byte val) {
    Serial.println("Writing correct fuse settings to ATtiny.......");

    shiftOut(0x40, 0x4C);
    shiftOut(val, 0x2C);
    shiftOut(0x00, (byte)(fuse >> 8));
    shiftOut(0x00, (byte)fuse);

    Serial.println("Writing complete..");
}

void readFuses() {
    Serial.println("Reading fuse settings from connected ATtiny.......");

    byte val;
    shiftOut(0x04, 0x4C); // LFuse
    shiftOut(0x00, 0x68);
    val = shiftOut(0x00, 0x6C);
    Serial.print("LFuse: ");
    Serial.print(val, HEX);
    shiftOut(0x04, 0x4C); // HFuse
    shiftOut(0x00, 0x7A);
    val = shiftOut(0x00, 0x7E);
    Serial.print(", HFuse: ");
    Serial.print(val, HEX);
    shiftOut(0x04, 0x4C); // EFuse
    shiftOut(0x00, 0x6A);
    val = shiftOut(0x00, 0x6E);
    Serial.print(", EFuse: ");
    Serial.println(val, HEX);
    Serial.println("Reading complete..");
}

unsigned int readSignature() {
    unsigned int sig = 0;
    byte val;

    for (int ii = 1; ii < 3; ii++) {
        shiftOut(0x08, 0x4C);
        shiftOut(ii, 0x0C);
        shiftOut(0x00, 0x68);
        val = shiftOut(0x00, 0x6C);
        sig = (sig << 8) + val;
    }
    return sig;
}