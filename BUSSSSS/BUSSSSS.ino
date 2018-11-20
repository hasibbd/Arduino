#include <Servo.h>
#include <RFID.h>
#include <SPI.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 0, 5, 4, 3, 2);
RFID rfid(10, 9);
Servo Servol;
int irin = 6;
int sound = 7;
int servoPin = 8;
int led = 7;
int power = 8;
int irs=HIGH;
int serNum[5];
int cards[][5] = {
  {10, 56, 215, 43, 206}
};
bool access = false;
bool music = false;
bool ir = true; 
void setup() {
  lcd.begin(16, 2);
  lcd.print ("Hello");
  delay (1000);
  lcd.print ("World");
  pinMode(irin, INPUT);
  pinMode(sound, OUTPUT);
  Serial.begin(9600);
//  Servo1.attach(servoPin);
  SPI.begin();
  rfid.init();
}

void loop() {
  irs =digitalRead(irin); 
  // Servo1.write(0);
  if(irs== LOW){
    music==true;
    {
      Serial.print("Show the card");
      Serial.print(" ");
      if (rfid.isCard()) {
        if (rfid.readCardSerial()) {
          Serial.print(rfid.serNum[0]);
          Serial.print(" ");
          Serial.print(rfid.serNum[1]);
          Serial.print(" ");
          Serial.print(rfid.serNum[2]);
          Serial.print(" ");
          Serial.print(rfid.serNum[3]);
          Serial.print(" ");
          Serial.print(rfid.serNum[4]);
          Serial.println("");
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
          Serial.println("Welcome!");
          digitalWrite(led, HIGH);
          delay(1000);
          digitalWrite(led, LOW);
          digitalWrite(power, HIGH);
          delay(1000);
          digitalWrite(power, LOW);
        } else {
          Serial.println("Not allowed!");
          digitalWrite(led, HIGH);
          delay(500);
          digitalWrite(led, LOW);
          delay(500);
          digitalWrite(led, HIGH);
          delay(500);
          digitalWrite(led, LOW);
          delay (2000);
        }
        if(music){
            digitalWrite(sound, HIGH);
          }
          else{
            digitalWrite(sound, HIGH);
            delay(1000);
            digitalWrite(sound, LOW);
            delay(500);
            digitalWrite(sound, HIGH);
            delay(1000);
            digitalWrite(sound, LOW);
            delay(500);
            digitalWrite(sound, HIGH);
            delay(1000);
            digitalWrite(sound, LOW);
            delay(500);
          }
      }
  }
  }
  else(
    irs HIGH
    
    )
  // put your main code here, to run repeatedly:
rfid.halt();
}
