//WWW.arduteca.blogspot.com.es

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#define LRS 0
#define LE 1
#define LD4 2
#define LD5 3
#define LD6 4
#define LD7 5 
#define IRA 6
#define SOUND 7
#define SERV 8
#define RSDA 9
#define RRST 10 
LiquidCrystal lcd (LRS, LE, LD4, LD5, LD6, LD7);
MFRC522 mfrc522(RSDA,RRST);        // Create MFRC522 instance.

const byte ledind=13;    //Rele del Abrepuertas
const int  timetoclean=3000;  //msecs en quitar información display
const int numcards=2;                                 //numero de tarjetas rfids que hay definidas
unsigned long rfid[numcards]={0x753B1102,0x537C7565}; //definimos los codigos de las tarjetas (4 primeros digitos en formato hexadecimal)
char* individuo[numcards]={"Hola Fernando","Hola Susan"};      //aqui podemos introducir las personas a la que pertenecen los targetas 
unsigned long clearlcd;
boolean er;  //Cambia de estado cuando hay información en el display
//se utiliza para hacer limpieza del display
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns

char keys[ROWS][COLS] =
{{'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}};
 
byte rowPins[ROWS] = {
  33, 35, 37, 39}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  41, 43, 45}; // connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

const byte ncodigos=3;  //Nº de codigos que queremos usar
//Detallamos los codigos que darán paso
char* Codkeypad[ncodigos]={"123456",
                           "654321",
                          "000000"}; 
//Detallamos los saludos correspondientes a cada código
char* nombreskeypad[ncodigos]={"Hola Sr. Merkel",
                               "Hola Sr. Rajoy",
                               "Buenas Sr. Pujol"};
String pass;
byte pos= 0;

void setup() {
  Serial.begin(9600);
  SPI.begin();                // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card
  lcd.begin(20,4); 
  lcd.backlight();   //iluminación de fondo del display
  limpialcd();       //Procedimiento borrado display
  pinMode(ledind, OUTPUT);  //Definimos el pin13 de salida
  digitalWrite(ledind, LOW);  
}

void loop() {
  
  if (er==true) if (clearlcd+timetoclean<millis()) limpialcd();
  //limpia la información del display 
  //LEE keypad
  char keypadkey = keypad.getKey();
    if (keypadkey != NO_KEY) password(keypadkey);
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
   // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    
    return;
     }                //MIENTRAS NO LEA UNA NUEVA TARJETA EL PROGRAMA NO PASA DE AQUI
   // Select one of the cards
   if ( ! mfrc522.PICC_ReadCardSerial())    return; 
   byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
   byte buffer[18];  
   byte block  = 0;
   byte status;
   status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
   if (status != MFRC522::STATUS_OK) {
           error();
           return;
        }
        // Read block
   byte byteCount = sizeof(buffer);
   status = mfrc522.MIFARE_Read(block, buffer, &byteCount);  
   if (status != MFRC522::STATUS_OK) {
	    error();
	}
        else  // Dump data
	{
        
        
        //transforma los 4 primeros numeros del bloque 0 en una variable de 4 bytes para poderla comparar con las numeraciones registradas 
   unsigned long card=0;
   byte b=0;
   for (int a=3;a>-1;a--) {
   switch (a){
        case 3:  card += buffer[b]*16777216; break;
        case 2:  card += buffer[b]*65536; break;
        case 1:  card += buffer[b]*256; break;
        case 0:  card += buffer[b];break;
        }
        b++;}
   boolean encontrada=false;
   for (byte a=0;a<numcards;a++) {                      
          if (rfid[a]==card) {
            lcd.setCursor(0,3);
            lcd.print(individuo[a]);
            encontrada=true;}} //si el num de la tarjeta coincide con alguno de los definidos dice el nombre
   lcd.setCursor(0,2);
   if (encontrada) {
              lcd.print("Tarjeta valida");
              digitalWrite(ledind, HIGH); 
              delay(500);  //Activamos el led durante 0,5 seg
              digitalWrite(ledind, LOW); }
   else 
            {lcd.print("Tarjeta invalida");
            lcd.setCursor(0,3); 
            lcd.print("Vuelvase a casa");}
            er=true;
            clearlcd=millis();}
   mfrc522.PICC_HaltA(); // Halt PICC
   mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD       
}
//Procedimiento para cuando ha habido un error en la lectura
//de la numeración de la tarjeta
void error() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Error de lectura");
  lcd.setCursor(0,1);
  lcd.print("Vuelva a pasarla");
  clearlcd=millis();
  er=true;}
//Hace un borrado del display y reinicia variables  
void limpialcd(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Pase su tarjeta o");
  lcd.setCursor(0,1);
  lcd.print("Teclee codigo:"); 
  er=false;
  pos=0;
  pass=""; } 

//Hace de contador de digitos al introducir codigo y cuando
//ya se han introducido 6 digitos llama al procedimiento para
//su compruebacion
void password(char key) {
   pass+= key;
  lcd.setCursor(14+pos,1);
  lcd.print("*");
  if (pos<5) 
    pos++;
    else {comprueba_codigos();pos=0;}

}  
//Comprueba si el codigo introducido esta registrado
//si lo está da acceso
void comprueba_codigos() {
  boolean encontrada=false;
  for (byte a=0; a<ncodigos;a++){ 
          String pwd = String(Codkeypad[a]);
          if (pwd==pass) {
            lcd.setCursor(0,3);
            lcd.print(nombreskeypad[a]);
            encontrada=true;}}
   lcd.setCursor(0,2);
   if (encontrada) {
              lcd.print("Codigo valido");
              digitalWrite(ledind, HIGH); 
              delay(500);  //Activamos el led durante 0,5 seg
              digitalWrite(ledind, LOW); }
   else 
            {lcd.print("Codigo invalido");
            lcd.setCursor(0,3); 
            lcd.print("Vuelvase a casa");}
            er=true;
            clearlcd=millis();}
            
    
  
