#define trig1 13
#define echo1 12
#define trig2 11
#define echo2 10
#define r1 9
#define g1 8
#define r2 7
#define g2 6
#define r3 5
#define g3 4
#define r4 3
#define g4 2
int s=0;
int f=0;

void setup() {
  Serial.begin (9600);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
   pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(r1, OUTPUT);
  pinMode(g1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(g3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(g4, OUTPUT);
}
void loop() {
  
  long dur1, dis1;
  long dur2, dis2;
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  dur1 = pulseIn(echo1, HIGH);
  dis1 = (dur1 / 2) / 29.1;
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  dur2 = pulseIn(echo2, HIGH);
  dis2 = (dur2 / 2) / 29.1;
  if (dis1 < 6 && dis1>= 2 && s>=0) {
      Serial.print(dis1);
    s=s+1;
    Serial.print("First");
    Serial.print(s);
    Serial.println();
    delay(30);
  }
   if (dis2 < 6 && s>=1) {
    Serial.print("Finish");
    s=s-1;
    Serial.print(s);
      Serial.println();
        delay(30);
  }
 if(s>=5){
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);
digitalWrite(r3,HIGH);
digitalWrite(r4,HIGH);
digitalWrite(g1,HIGH);
digitalWrite(g2,LOW);
digitalWrite(g3,LOW);
digitalWrite(g4,LOW);
delay(200);
  }
  else{
digitalWrite(r1,LOW);
digitalWrite(r2,LOW);
digitalWrite(r3,LOW);
digitalWrite(r4,LOW);
digitalWrite(g1,LOW);
digitalWrite(g2,LOW);
digitalWrite(g3,LOW);
digitalWrite(g4,LOW);
delay(100);
digitalWrite(r1,LOW);
digitalWrite(r2,HIGH);
digitalWrite(r3,LOW);
digitalWrite(r4,HIGH);
digitalWrite(g1,HIGH);
digitalWrite(g2,LOW);
digitalWrite(g3,HIGH);
digitalWrite(g4,LOW);
delay(2000);
digitalWrite(r1,HIGH);
digitalWrite(r2,LOW);
digitalWrite(r3,HIGH);
digitalWrite(r4,LOW);
digitalWrite(g1,LOW);
digitalWrite(g2,HIGH);
digitalWrite(g3,LOW);
digitalWrite(g4,HIGH);
delay(2000);


  
  }

/* if(s==0 && f==0){
delay(200);
  count=count+1;
  if(count<40){
    digitalWrite(red,HIGH);
    digitalWrite(green,LOW);
  }
  else{
    digitalWrite(green,HIGH);
     digitalWrite(red,LOW);
    if(count==80){
      count=0;
    }
  }
    
 }*/
}
