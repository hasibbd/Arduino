#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#define art 6
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {21, 20, 19, 18};
byte colPins[COLS] = {17, 16, 15, 14};
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
Servo Servo1;
char pass[4] = "1234";
char ipass[16];
char date[16];
int i;
int n = 0, e = 0, x = 0;
int warning = 0;
int q;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  Servo1.attach(7);
  Servo1.write(0);
  pinMode(art, OUTPUT);
}
void dooropen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Door Unlocked");
  Servo1.write(90);
  delay(2000);
}
void doorclose() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Door Locked");
  Servo1.write(0);
  delay(2000);
}
void loop() {
f:
  char customKey = customKeypad.getKey();
  if (customKey == 'D') {
    digitalWrite(art, HIGH);
    delay(500);
    digitalWrite(art, LOW);
w:
clean:
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Password");
    n = 0;
    i = 0;
    while (1) {
      char customKey = customKeypad.getKey();
      if (customKey) {
        if (customKey == 'A') {
          goto compare;
        }
        else if (customKey == 'C') {

          lcd.setCursor(0, 1);
          lcd.print("Password Clear");
          delay(1000);
          lcd.clear();
          digitalWrite(art, HIGH);
          delay(1000);
          digitalWrite(art, LOW);
          goto clean;
        }
        else if (customKey == 'B') {
          for (int j = 0; j < 10; j++) {
            lcd.setCursor(0, 0);
            lcd.print("Lock in 10 sec");
            lcd.setCursor(0, 1);
            lcd.print("Second: ");
            lcd.print(          j + 1);
            delay(500);
            digitalWrite(art, HIGH);
            delay(500);
            digitalWrite(art, LOW);
          }
          doorclose();
          goto f;
        }
        ipass[i] = customKey;
        i++;
        digitalWrite(art, HIGH);
        delay(200);
        digitalWrite(art, LOW);
        Serial.println(customKey);
        lcd.setCursor(n, 1);
        lcd.print("*");
        n++;

      }
    }
compare: {
      if (pass[0] == ipass[0] && pass[1] == ipass[1] && pass[2] == ipass[2] && pass[3] == ipass[3] && i == 4) {
        warning = 0;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access Granted");
        digitalWrite(art, HIGH);
        delay(2000);
        digitalWrite(art, LOW);
        dooropen();
        i = 0;
        n = 0;
        lcd.clear();
        while (1) {

          lcd.setCursor(0, 0);
          lcd.print("Want To Lock?");
          lcd.setCursor(0, 1);
          lcd.print("Press: B");
          char customKey = customKeypad.getKey();
          if (customKey == 'B') {
            goto l;
          }
        }
l:
        lcd.clear();
        for (int j = 0; j < 10; j++) {
          lcd.setCursor(0, 0);
          lcd.print("Lock in 10 sec");
          lcd.setCursor(0, 1);
          lcd.print("Second: ");
          lcd.setCursor(8, 1);
          lcd.print(j + 1);
          delay(500);
          digitalWrite(art, HIGH);
          delay(500);
          digitalWrite(art, LOW);
        }
        doorclose();
      }
      else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Access Deny");
        lcd.setCursor(0, 1);
        lcd.print("Wrong Password");
        digitalWrite(art, HIGH);
        delay(500);
        digitalWrite(art, LOW);
        delay(500);
        digitalWrite(art, HIGH);
        delay(500);
        digitalWrite(art, LOW);
        delay(500);
        digitalWrite(art, HIGH);
        delay(500);
        digitalWrite(art, LOW);
        warning = warning + 1;
        if (warning == 3) {
          for (int d = 1; d <= 30; d++) {
            warning = 0;
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Suspend 30 sec.");
            lcd.setCursor(0, 1);
            lcd.print(d);
            delay(1000);
          }
        }
        goto w;
      }
    }
  }
  else if (customKey == 'B') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter The time: ");
    n = 0;
    while (1) {
      char customKey = customKeypad.getKey();
      if (customKey) {
        if (customKey == 'A') {
          q = atoi(date);
          goto u;
        }
        date[e] = customKey;
        e++;
        digitalWrite(art, HIGH);
        delay(200);
        digitalWrite(art, LOW);
        Serial.println(customKey);
        lcd.setCursor(n, 1);
        lcd.print(customKey);
        n++;

      }
    }
u:
    for (int h = 1; h < q; h++) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(q - h);
      lcd.print("      Sec Left");
      delay(1000);
    }
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Product Expired");
    digitalWrite(art, LOW);
    delay(500);
    digitalWrite(art, HIGH);
    delay(2000);
    digitalWrite(art, LOW);

  }
  else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Door Lock: D");
    lcd.setCursor(0, 1);
    lcd.print("Food Expire: B");
    delay(500);
  }


}
