
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
char auth[] = "9737249161994ddeaf7900eb4344ca79";
char ssid[] ="Hasib PC";
char pass[] ="bangladesh";
#define EspSerial Serial1
//#include <SoftwareSerial.h>
//SoftwareSerial EspSerial(0, 1); // RX, TX
#define ESP8266_BAUD 115200
ESP8266 wifi(&EspSerial);
BlynkTimer timer;
void myTimerEvent()
{
  Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  Serial.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);
  //Blynk.begin(auth, wifi, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8442);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}
