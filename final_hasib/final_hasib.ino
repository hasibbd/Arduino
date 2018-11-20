#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char auth[] = "9737249161994ddeaf7900eb4344ca79";
char ssid[] = "Hasib";
char pass[] = "bangladesh";
#define EspSerial Serial1
#define trig1 30
#define echo1 31
#define trig2 9
#define echo2 8
#define pump 7
#define alart 6
long dur1, dur2;
int dis1, dis2;
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
WidgetLED led1(V0);
WidgetLED led2(V5);
WidgetLCD vlcd(V10);
BlynkTimer timer;
int s, a;
int cc = 0, m = 0;
BLYNK_WRITE(V1)
{ int pinValue1 = param.asInt();
  s = pinValue1;
}
BLYNK_WRITE(V4)
{ int pinValue = param.asInt();
  a = pinValue;
}
void setup()
{
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(pump, OUTPUT);
  pinMode(alart, OUTPUT);
  digitalWrite(pump, HIGH);
  digitalWrite(alart, HIGH);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("Primeasia University");
  lcd.setCursor(0, 2);
  lcd.print("Connecting Internet");
  lcd.setCursor(0, 3);
  lcd.print("Please Wait.....");
  lcd.setCursor(0, 1);
  lcd.print("********************");
  Blynk.begin(auth, wifi, ssid, pass);
  digitalWrite(alart, LOW);
  lcd.setCursor(0, 3);
  vlcd.print(0, 0, "Connected......");
  lcd.print("Connected.........");
  delay(2000);
  lcd.clear();
  rl();
  delay(500);
  tl();
  vlcd.clear();
}
void rl() {
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  dur2 = pulseIn(echo2, HIGH);
  dis2 = 10 * dur2 * 0.034 / 2;
  Serial.print("Res ");
  Serial.println(dis2);
  lcd.setCursor(0, 3);
  if (dis2 <= 54) {
    lcd.print("Reserved: 100%     ");
    Blynk.virtualWrite(V2, 100);
  } else if (dis2 > 54 && dis2 <= 56) {
    lcd.print("Reserved: 95%      ");
    Blynk.virtualWrite(V2, 95);
  } else if (dis2 > 56 && dis2 <= 58) {
    lcd.print("Reserved: 90%      ");
    Blynk.virtualWrite(V2, 90);
  } else if (dis2 > 58 && dis2 <= 60) {
    lcd.print("Reserved: 85%      ");
    Blynk.virtualWrite(V2, 85);
  } else if (dis2 > 60 && dis2 <= 62) {
    lcd.print("Reserved: 80%      ");
    Blynk.virtualWrite(V2, 80);
  } else if (dis2 > 62 && dis2 <= 64) {
    lcd.print("Reserved: 75%      ");
    Blynk.virtualWrite(V2, 75);
  } else if (dis2 > 64 && dis2 <= 66) {
    lcd.print("Reserved: 70%      ");
    Blynk.virtualWrite(V2, 70);
  } else if (dis2 > 66 && dis2 <= 68) {
    lcd.print("Reserved: 65%      ");
    Blynk.virtualWrite(V2, 65);
  } else if (dis2 > 68 && dis2 <= 70) {
    lcd.print("Reserved: 60%      ");
    Blynk.virtualWrite(V2, 60);
  } else if (dis2 > 70 && dis2 <= 72) {
    lcd.print("Reserved: 55%      ");
    Blynk.virtualWrite(V2, 55);
  } else if (dis2 > 72 && dis2 <= 74) {
    lcd.print("Reserved: 50%      ");
    Blynk.virtualWrite(V2, 50);
  } else if (dis2 > 74 && dis2 <= 76) {
    lcd.print("Reserved: 45%      ");
    Blynk.virtualWrite(V2, 45);
  } else if (dis2 > 76 && dis2 <= 78) {
    lcd.print("Reserved: 40%      ");
    Blynk.virtualWrite(V2, 40);
  } else if (dis2 > 78 && dis2 <= 80) {
    lcd.print("Reserved: 35%      ");
    Blynk.virtualWrite(V2, 35);
  } else if (dis2 > 80 && dis2 <= 82) {
    lcd.print("Reserved: 30%      ");
    Blynk.virtualWrite(V2, 30);
  } else if (dis2 > 82 && dis2 <= 84) {
    lcd.print("Reserved: 25%      ");
    Blynk.virtualWrite(V2, 25);
  } else if (dis2 > 84 && dis2 <= 86) {
    lcd.print("Reserved: 20%      ");
    Blynk.virtualWrite(V2, 20);
  } else if (dis2 > 86 && dis2 <= 88) {
    lcd.print("Reserved: 15%      ");
    Blynk.virtualWrite(V2, 15);
  } else if (dis2 > 88 && dis2 <= 90) {
    lcd.print("Reserved: 10%      ");
    Blynk.virtualWrite(V2, 10);
  } else if (dis2 > 90 && dis2 <= 92) {
    lcd.print("Reserved: 05%      ");
    Blynk.virtualWrite(V2, 5);
  } else if (dis2 > 92) {
    lcd.print("Reserved: 00%      ");
    Blynk.virtualWrite(V2, 0);
  }
  else {
    lcd.print("Reserved: Emty     ");
  }
}
void tl() {
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  dur1 = pulseIn(echo1, HIGH);
  dis1 = 10 * dur1 * 0.034 / 2;
  Serial.print("tank ");
  Serial.println(dis1);
  lcd.setCursor(0, 2);
  if (dis1 > 90) {
    Blynk.virtualWrite(V3, 0);
    lcd.print("Tank: 00% ");
  } else if (dis1<90 and dis1 >= 87 ) {
    lcd.print("Tank: 05% ");
    Blynk.virtualWrite(V3, 5);
  } else if (dis1<87 and dis1 >= 84) {
    lcd.print("Tank: 10% ");
    Blynk.virtualWrite(V3, 10);
  } else if (dis1<84 and dis1 >= 81) {
    lcd.print("Tank: 15% ");
    Blynk.virtualWrite(V3, 15);
  } else if (dis1<81 and dis1 >= 78) {
    lcd.print("Tank: 20% ");
    Blynk.virtualWrite(V3, 20);
  } else if (dis1<78 and dis1 >= 75) {
    lcd.print("Tank: 25% ");
    Blynk.virtualWrite(V3, 25);
  } else if (dis1<75 and dis1 >= 72) {
    lcd.print("Tank: 30% ");
    Blynk.virtualWrite(V3, 30);
  } else if (dis1<72 and dis1 >= 69) {
    lcd.print("Tank: 35% ");
    Blynk.virtualWrite(V3, 35);
  } else if (dis1<69 and dis1 >= 65) {
    lcd.print("Tank: 40% ");
    Blynk.virtualWrite(V3, 40);
  } else if (dis1<65 and dis1 >= 63) {
    lcd.print("Tank: 45% ");
    Blynk.virtualWrite(V3, 45);
  } else if (dis1<63 and dis1 >= 61) {
    lcd.print("Tank: 50% ");
    Blynk.virtualWrite(V3, 50);
  } else if (dis1<61 and dis1 >= 59) {
    lcd.print("Tank: 55% ");
    Blynk.virtualWrite(V3, 55);
  } else if (dis1<59 and dis1 >= 57) {
    lcd.print("Tank: 60% ");
    Blynk.virtualWrite(V3, 60);
  } else if (dis1<57 and dis1 >= 55) {
    lcd.print("Tank: 65% ");
    Blynk.virtualWrite(V3, 65);
  } else if (dis1<55 and dis1 >= 52) {
    lcd.print("Tank: 70% ");
    Blynk.virtualWrite(V3, 70);
  } else if (dis1<52 and dis1 >= 49) {
    lcd.print("Tank: 75% ");
    Blynk.virtualWrite(V3, 75);
  } else if (dis1<49 and dis1 >= 45) {
    lcd.print("Tank: 80% ");
    Blynk.virtualWrite(V3, 80);
  } else if (dis1<45 and dis1 >= 42) {
    lcd.print("Tank: 85% ");
    Blynk.virtualWrite(V3, 85);
  } else if (dis1<42 and dis1 >= 38) {
    lcd.print("Tank: 90% ");
    Blynk.virtualWrite(V3, 90);
  } else if (dis1<38 and dis1 >= 35) {
    lcd.print("Tank: 95% ");
    Blynk.virtualWrite(V3, 95);
  } else if (dis1 < 35) {
    lcd.print("Tank: 100%");
    Blynk.virtualWrite(V3, 100);
  }
}
void loop()
{
  Blynk.run();
  timer.run();
  if (a == 0) {
      BLYNK_CONNECTED();
    tl();
    delay(500);
    rl();
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("Auto Mode: Off");
    vlcd.print(0, 0, "Auto Mode: Off  ");
    led2.off();
    if (s == 0) {
      led1.off();
      lcd.setCursor(0, 1);
      lcd.print("Pump: Off");
      digitalWrite(pump, HIGH);
      vlcd.print(0, 1, "Pump: Off       ");
    } else {
      led1.on();
      lcd.setCursor(0, 1);
      lcd.print("Pump: On ");
      vlcd.print(0, 1, "Pump: On        ");
      digitalWrite(pump, LOW);
      /*   if (dis1 <= 42 || ( dis2 > 630 && dis2 <= 660)) {
           vlcd.print(0, 1, "Stop The Pump  ");
         }*/
    }
  }
  else {
    BLYNK_CONNECTED();
    tl();
    delay(500);
    rl();
    delay(500);
    led2.on();
    lcd.setCursor(0, 0);
    lcd.print("Auto Mode: On ");
    vlcd.print(0, 0, "Auto Mode: On ");
    if (dis1 >= 90) {
      lcd.setCursor(0, 2);
      lcd.print("Tank: Emty");
      vlcd.print(0, 1, "Tank: Emty      ");
      delay(2000);
      if ( dis2 > 92) {
        delay(2000);
        lcd.setCursor(0, 1);
        lcd.print("Pump: Off");
        lcd.setCursor(0, 3);
        lcd.print("Reserved: Emty!!!!");
        vlcd.print(0, 1, "Tank: Emty      ");
        delay(500);
        vlcd.print(0, 1, "Pump: Off        ");
        delay(500);
        vlcd.print(0, 1, "Reserved: Emty  ");
        Blynk.virtualWrite(V2, 0);
        led1.off();
        digitalWrite(pump, HIGH);
      }
      else {
        led1.on();
        lcd.setCursor(0, 1);
        vlcd.print(0, 1, "Pump: On        ");
        lcd.print("Pump: On ");
        digitalWrite(pump, LOW);
      }
    }
    else if (dis1 <= 35 or dis1>100) {
      lcd.setCursor(0, 1);
      lcd.print("Pump: Off");
      lcd.setCursor(0, 2);
      lcd.print("Tank: Full");
      vlcd.print(0, 1, "Tank: Full      ");
      delay(500);
      vlcd.print(0, 1, "Pump: Stop      ");
      led1.off();
      digitalWrite(pump, HIGH);
    }
  else if ( dis2 > 92) {
        delay(2000);
        lcd.setCursor(0, 1);
        lcd.print("Pump: Off");
        lcd.setCursor(0, 3);
        lcd.print("Reserved: Emty!!!!");
        vlcd.print(0, 1, "Pump: Off        ");
        delay(500);
        vlcd.print(0, 1, "Reserved: Emty  ");
        Blynk.virtualWrite(V2, 0);
        led1.off();
        digitalWrite(pump, HIGH);
      }
  }
  cc = cc + 1;
  tl();
  delay(500);
  rl();
  delay(500);
  if (cc == 5) {
    lcd.begin(20, 4);
    cc = 0;
  }
}


