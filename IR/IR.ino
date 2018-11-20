#define LED 13
#define ir 7 
int var = HIGH;
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(var, INPUT);
  Serial.begin(9600);  
}
void loop() {
  var = digitalRead(ir);
  if (var == LOW)
  {
    Serial.println("Stop something is ahead!!");
    digitalWrite(LED, HIGH);
  }
  else
  {
    Serial.println("Path is clear");
    digitalWrite(LED, LOW);
  }
  delay(200);
}
