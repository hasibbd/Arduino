#define pir 2
#define led 3
int var = LOW;
void setup() {
  pinMode(pir, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  var = digitalRead(pir);
  if (var == HIGH)
  {
  digitalWrite(led, HIGH); 
  delay(100);                     
  digitalWrite(led, LOW);  
  delay(100);        
  }
}
