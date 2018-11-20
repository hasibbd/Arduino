#include <Servo.h>
#include <RFID.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
#define IRA 6
#define SOUND 7
#define SERV 8
#define RSDA 10
#define RRST 9
RFID rfid(RSDA, RRST);
int ir = 6;
int sound = 7;
int ir1 = HIGH;
int kml;
int servoPin = 8;
Servo Servo1;
int red = 5;
int blue = 4;
int green = 3;
int power = 8;
int adjust = 17;
int serNum[5];
int cards[][5] = {
  {10, 56, 215, 43, 206}
};
bool access = false;
int wel = 1;
int door_op = 0;
int door_cl = 0;
int card_c = 0;
int ir_c = 1;
int bus = 0;
int kilo = 0;
int km = 1;
int cost = 0;
int cut = 0;
int i;
int door = 1;
int open_alart = 1;
int welcome = 1;
int alart = 0;
int balance = 500;
int d = 1;
char pass[4] = "1234";
char ipass[4];
int stol = 0;
int start = 2;
int www = 0;
int dis = 1;
void setup() {
  lcd.begin(16, 2);
  pinMode(ir, INPUT);
  pinMode(km, INPUT);
  pinMode(start, OUTPUT);
  pinMode(sound, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  Servo1.attach(servoPin);
  SPI.begin();
  rfid.init();
}
void loop() {
  ir1 = digitalRead(ir);
  digitalWrite(start, HIGH);
  if (wel == 1) {
    Servo1.write(30);
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(sound, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   Welcome To   ");
    lcd.setCursor(0, 1);
    lcd.print("   Smart  Bus   ");
    ir_c = 1;
    wel = 0;
  }
  else if (ir_c == 1) {
    if (ir1 == LOW) {
      door_op = 1;
      card_c = 1;
      alart = 1;
      digitalWrite(green, LOW);
      ir_c = 0;
    }
  }
  else if (door_op == 1) {
    digitalWrite(sound, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door Opening");
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    lcd.setCursor(0, 1);
    for (i = 0; i < 16; i++) {
      lcd.print("*");
      delay(100);
    }
    Servo1.write(120);
    digitalWrite(sound, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Show your Card");
    delay(100);
    door_op = 0;
  }
  else if (card_c == 1) {
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    while (1) {
      {
        if (rfid.isCard()) {
          digitalWrite(sound, HIGH);
          delay(100);
          digitalWrite(sound, LOW);
          if (rfid.readCardSerial()) {
            for (int x = 0; x < sizeof(cards); x++) {
              for (int i = 0; i < sizeof(rfid.serNum); i++ ) {
                if (rfid.serNum[i] != cards[x][i]) {
                  access = false;
                  break;
                } else {
                  access = true;
                }
              }
              if (access) break;
            }
          }
          if (access) {
            digitalWrite(sound, HIGH);
            delay(100);
            digitalWrite(sound, LOW);
            delay(100);
            digitalWrite(sound, HIGH);
            delay(100);
            digitalWrite(sound, LOW);
            if (balance < 50) {
              digitalWrite(sound, HIGH);
              delay(300);
              digitalWrite(sound, LOW);
              delay(300);
              digitalWrite(sound, HIGH);
              delay(300);
              digitalWrite(sound, LOW);
              digitalWrite(blue, HIGH);
              digitalWrite(red, LOW);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Balance: ");
              lcd.print(balance);
              lcd.setCursor(0, 1);
              lcd.print("Balance is low");
              delay(5000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Door Closing");
              lcd.setCursor(0, 1);
              for (i = 0; i < 16; i++) {
                lcd.print("*");
                delay(100);
              }
              delay(1000);
              goto k;
            }
            else {
              digitalWrite(sound, HIGH);
              delay(200);
              digitalWrite(sound, LOW);
              digitalWrite(blue, HIGH);
              digitalWrite(green, LOW);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Balance: ");
              lcd.print(balance);
              lcd.setCursor(0, 1);
              lcd.print("Plz Take Ur Seat");
              delay(5000);
              digitalWrite(blue, HIGH);
              digitalWrite(green, HIGH);
              digitalWrite(red, LOW);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Door Closing");
              lcd.setCursor(0, 1);
              for (i = 0; i < 16; i++) {
                lcd.print("*");
                delay(100);
              }
              delay(1000);
              bus = 1;
              goto p;
            }
          }
          else {
            digitalWrite(sound, HIGH);
            delay(200);
            digitalWrite(sound, LOW);
            delay(200);
            digitalWrite(sound, HIGH);
            delay(200);
            digitalWrite(sound, LOW);
            digitalWrite(blue, HIGH);
            digitalWrite(red, LOW);
            lcd.setCursor(0, 1);
            lcd.print("Sorry, invalid card!!");
            delay(1000);
            digitalWrite(blue, HIGH);
            digitalWrite(green, HIGH);
            digitalWrite(red, LOW);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Door Closing");
            digitalWrite(blue, HIGH);
            digitalWrite(green, HIGH);
            digitalWrite(red, LOW);
            lcd.setCursor(0, 1);
            for (i = 0; i < 16; i++) {
              lcd.print("*");
              delay(100);
            }
            delay(1000);
            goto l;
          }
        }
        else {
        }
        rfid.halt();
      }
    }
k:
p:
l:
    card_c = 0;
    wel = 1;
    Servo1.write(30);
    delay(100);
  }
  if (bus == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Run");
    delay(5000);
    digitalWrite(start, LOW);
    while (1) {
      kml = HIGH;
      kml = digitalRead(km);
      float sensorValue = analogRead(A0);
      if (sensorValue >= 300 + adjust && sensorValue <= 370 + adjust) {
        float sensorValue = analogRead(A0);
        digitalWrite(sound, HIGH);
        delay(100);
        digitalWrite(sound, LOW);
        delay(100);
        digitalWrite(sound, HIGH);
        delay(100);
        digitalWrite(sound, LOW);
        stol = 1;
      }
      else if (kml == LOW) {
        digitalWrite(blue, LOW);
        digitalWrite(green, LOW);
        digitalWrite(red, HIGH);
        kilo = kilo + 1;
        www = kilo / 5;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Distances:");
        lcd.setCursor(0, 1);
        lcd.print(www);
        kml = HIGH;
      }
      else if (stol == 1) {
        digitalWrite(blue, LOW);
        digitalWrite(green, LOW);
        digitalWrite(red, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Bus Is Stopping");
        digitalWrite(start, HIGH);
        delay(5000);
        cost = www * 10;
        digitalWrite(sound, HIGH);
        delay(100);
        digitalWrite(sound, LOW);
        delay(5000);
        stol = 0;
        goto s;
      }
      else {
        digitalWrite(blue, LOW);
        delay(100);
        digitalWrite(blue, HIGH);
        digitalWrite(green, LOW);
        delay(100);
        digitalWrite(green, HIGH);
        digitalWrite(red, LOW);
        delay(100);
        digitalWrite(red, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Running");
        delay(500);
      }
    }
s:
    bus = 0;
    cut = 1;
  }
  else if (cut == 1 ) {
f:
again:
    digitalWrite(sound, HIGH);
    delay(100);
    digitalWrite(sound, LOW);
    delay(100);
    digitalWrite(sound, HIGH);
    delay(100);
    digitalWrite(sound, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Show Your CARD");
    lcd.setCursor(0, 1);
    lcd.print("The cost is: ");
    lcd.print(cost);
    delay(1000);
    while (1) {
      if (rfid.isCard()) {
        if (rfid.readCardSerial()) {
          for (int x = 0; x < sizeof(cards); x++) {
            for (int i = 0; i < sizeof(rfid.serNum); i++ ) {
              if (rfid.serNum[i] != cards[x][i]) {
                access = false;
                break;
              } else {
                access = true;
              }
            }
            if (access) break;
          }
        }
        if (access) {
          digitalWrite(sound, HIGH);
          delay(100);
          digitalWrite(sound, LOW);
          digitalWrite(blue, HIGH);
          digitalWrite(green, LOW);
          digitalWrite(red, HIGH);
          int h = 0;
          char m;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter Password");
          lcd.setCursor(0, 1);
          while (1) {
            float sensorValue = analogRead(A0);
            /*  lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print(sensorValue);
              delay(500);*/
            if (sensorValue >= 10 && sensorValue <= 50) {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              m = '1';
              delay(100);
              ipass[h] = m;
              h = h + 1;
              lcd.print("*") ;

            }
            if (sensorValue >= 360 && sensorValue <= 390) {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              m = '2';
              delay(100);
              ipass[h] = m;
              h = h + 1;
              lcd.print("*");
            }
            if (sensorValue >= 455 && sensorValue <= 466) {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              m = '3';
              delay(100);
              ipass[h] = m;
              h = h + 1;
              lcd.print("*");
            }
            if (sensorValue >= 150 && sensorValue <= 200) {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              m = '4';
              delay(100);
              ipass[h] = m;
              h = h + 1;
              lcd.print("*");
            }
            if (sensorValue >= 405 && sensorValue <= 425) {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              m = '5';
              delay(100);
              ipass[h] = m;
              h = h + 1;
              lcd.print("*");
            }
            if (sensorValue >= 475 && sensorValue <= 495) {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              m = '6';
              delay(100);
              ipass[h] = m;
              h = h + 1;
              lcd.print("*");
            }
            if (sensorValue >= 210 && sensorValue <= 290) {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              m = '7';
              delay(100);
              ipass[h] = m;
              h = h + 1;
              lcd.print("*");
            }
            if (sensorValue >= 435 && sensorValue <= 454) {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              m = '8';
              delay(100);
              ipass[h] = m;
              h = h + 1;
              lcd.print("*");
            }
            if (sensorValue >= 496 && sensorValue <= 510) {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              m = '9';
              delay(100);
              ipass[h] = m;
              h = h + 1;
              lcd.print("*");
            }
            if (sensorValue >= 467 && sensorValue <= 474) {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              m = '0';
              delay(100);
              ipass[h] = m;
              h = h + 1;
              lcd.print("*");
            }
            if (sensorValue >= 335 && sensorValue <= 355) {
              ipass[h] = '\0';
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              delay(100);
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              lcd.print("Checking");
              delay(500);
              h = 0;
              goto compare;
            }
            if (sensorValue >= 511 && sensorValue <= 520) {
              h = 0;
              digitalWrite(sound, HIGH);
              delay(300);
              digitalWrite(sound, LOW);
              lcd.clear();
              lcd.print("Password Clear");
              delay(1000);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Enter password");
              lcd.setCursor(0, 1);
            }
            delay(300);
          }
compare: {
            if (pass[0] == ipass[0] && pass[1] == ipass[1] && pass[2] == ipass[2] && pass[3] == ipass[3]) {
              digitalWrite(sound, HIGH);
              delay(200);
              digitalWrite(sound, LOW);
              lcd.setCursor(0, 1);
              lcd.print("Access Granted");
              digitalWrite(blue, HIGH);
              digitalWrite(green, LOW);
              digitalWrite(red, HIGH);
              delay(1000);
              lcd.clear();
              balance = balance - cost;
              lcd.setCursor(0, 0);
              lcd.print("The cost is: ");
              lcd.print(cost);
              lcd.setCursor(0, 1);
              lcd.print("New Balance: ");
              lcd.print(balance);
              digitalWrite(blue,  LOW);
              digitalWrite(green, HIGH);
              digitalWrite(red, LOW);
              delay(10000);
              digitalWrite(blue, HIGH);
              digitalWrite(green, LOW);
              digitalWrite(red, HIGH);
              digitalWrite(sound, HIGH);
              digitalWrite(sound, HIGH);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Door Opening...");
              lcd.setCursor(0, 1);
              for (i = 0; i < 16; i++) {
                lcd.print("*");
                delay(100);
              }
              digitalWrite(sound, LOW);
              Servo1.write(120);
              delay(2000);
              digitalWrite(sound, LOW);
              delay(1000);
              digitalWrite(sound, HIGH);
              delay(5000);
              digitalWrite(blue, HIGH);
              digitalWrite(green, HIGH);
              digitalWrite(red, LOW);
              delay(10000);
              goto y;
            }
            else {
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              delay(100);
              digitalWrite(sound, HIGH);
              delay(100);
              digitalWrite(sound, LOW);
              lcd.setCursor(0, 1);
              lcd.print("Access Deney");
              digitalWrite(blue, HIGH);
              digitalWrite(green, HIGH);
              digitalWrite(red, LOW);
              delay(500);
              goto again;
            }
          }
        }
        else {
          digitalWrite(sound, HIGH);
          delay(300);
          digitalWrite(sound, LOW);
          digitalWrite(blue, HIGH);
          digitalWrite(green, HIGH);
          digitalWrite(red, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Wrong CARD");
          delay(1000);
          digitalWrite(blue, LOW);
          digitalWrite(green, HIGH);
          digitalWrite(red, HIGH);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Show Your CARD");
        }
        rfid.halt();
      }
    }
y:
    cut = 0;
    wel = 1;
    kilo = 0;
    www = 0;
    digitalWrite(sound, HIGH);
    delay(100);
    digitalWrite(sound, LOW);
    delay(300);
    digitalWrite(sound, HIGH);
    delay(100);
    digitalWrite(sound, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door Closing");
    digitalWrite(blue, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    lcd.setCursor(0, 1);
    for (i = 0; i < 16; i++) {
      lcd.print("*");
      delay(100);
    }
  }
}

