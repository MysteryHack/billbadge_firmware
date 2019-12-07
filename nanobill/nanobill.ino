#include <IRremote.h>


#define BTN 6

#define IR_RECEIVE 7
#define IR_SEND 3

#define LED_R 11
#define LED_G 10
#define LED_B 9

#define SPEED_FAST 16
#define SPEED_NORMAL 18
#define SPEED_SLOW 22


IRsend irsend;
IRrecv irrecv(IR_RECEIVE);

decode_results results;

uint32_t red = 0xFFFFFF01;
uint32_t green = 0xFFFFFF02;
uint32_t blue = 0xFFFFFF03;

uint32_t color = 0;

void setup() {
  Serial.begin(115200);

  pinMode(LED_R, OUTPUT);
  analogWrite(LED_R, 0);

  pinMode(LED_G, OUTPUT);
  analogWrite(LED_G, 0);

  pinMode(LED_B, OUTPUT);
  analogWrite(LED_B, 0);

  pinMode(BTN, INPUT_PULLUP);

  irrecv.enableIRIn();

  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  randomSeed(analogRead(A1) + analogRead(A2) + analogRead(A3) + analogRead(A4) + analogRead(A5));
  
  color = random(1, 4);

  switch (color) {
    case 1:
      digitalWrite(LED_R, HIGH);
      Serial.println("Red");
      break;
    case 2:
      digitalWrite(LED_G, HIGH);
      Serial.println("Green");
      break;
    case 3:
      digitalWrite(LED_B, HIGH);
      Serial.println("Blue");
      break;
  }
}

void loop() {
  if (digitalRead(BTN) == LOW) {
    switch (color/*random(1, 4)*/) {
      case 1:
        irsend.sendNEC(red, 32);
        Serial.print(red, HEX);
        Serial.println(" Red");
        delay(100);
        break;
      case 2:
        irsend.sendNEC(green, 32);
        Serial.print(green, HEX);
        Serial.println(" Green");
        delay(100);
        break;
      case 3:
        irsend.sendNEC(blue, 32);
        Serial.print(blue, HEX);
        Serial.println(" Blue");
        delay(100);
        break;
    }
  } else {
    if (irrecv.decode(&results)) {
      uint32_t msg = results.value;

      if ((msg & 0xFFFFFF00) == 0xFFFFFF00) {
        uint32_t newcolor = msg & 0x000000FF;

        digitalWrite(LED_R, LOW);
        digitalWrite(LED_G, LOW);
        digitalWrite(LED_B, LOW);

        switch (newcolor) {
          case 1:
            digitalWrite(LED_R, HIGH);
            Serial.println("Red");
            color = newcolor;
            break;
          case 2:
            digitalWrite(LED_G, HIGH);
            Serial.println("Green");
            color = newcolor;
            break;
          case 3:
            digitalWrite(LED_B, HIGH);
            Serial.println("Blue");
            color = newcolor;
            break;
          default:
            Serial.println(color, HEX);
        }
      } else {
        Serial.println(msg, HEX);
      }

      irrecv.resume(); // Receive the next value
    }
  }
}
