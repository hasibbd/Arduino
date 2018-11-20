#define led 13
#define ldr A0
int ldrStatus;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(ldr, INPUT);
}
void loop() {
  ldrStatus = analogRead(ldrPin);
  if (ldrStatus <= 200) {
    digitalWrite(ledPin, HIGH);
    Serial.print("Its DARK, Turn on the LED : ");
    Serial.println(ldrStatus);
  }
  else {
    digitalWrite(ledPin, LOW);
    Serial.print("Its BRIGHT, Turn off the LED : ");
    Serial.println(ldrStatus);
  }
}
