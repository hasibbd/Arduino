/* adaptado do codigo que acompanha a biblioteca MFRC522:
https://github.com/ljos/MFRC522

Este exemplo armazena o numero primeiro cartão lido em uma variavel
A partir ao aproximar um catão é feita a comparação entre o valor lido do cartão e o valor armazenado.
As informações são mostrada em um display 16x2 via comunicação I2C.
*/

// bibliotecas
#include <SPI.h>  // padrão do arduino
#include <MFRC522.h>  // necessário adicionar na pasta libraries do arduino
#include <Wire.h> // padrão do arduino
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
MFRC522 mfrc522(RSDA,RRST);    // cria uma intancia MFRC522 com o nome mfrc522

int *aux;
int card1[4];
int flag = 0;
int led = 13;
int cnt =0;

void setup() {
        pinMode(led, OUTPUT);
        
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init();    // Init MFRC522 card
        lcd.print(" Aproxime o card");
        lcd.setCursor(0,1);
        lcd.print(" Para registro  ");
}

void loop() {
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    // Now a card is selected. The UID and SAK is in mfrc522.uid.
    
    // Dump UID
    
    for (byte i = 0; i < mfrc522.uid.size; i++) {
            aux[i]= mfrc522.uid.uidByte[i];
    } 
           if(flag == 0)
           {
             lcd.clear();
             lcd.print("   Card UID:    ");
             lcd.setCursor(0,1);
             for (byte i = 0; i < mfrc522.uid.size; i++) {
               card1[i] = aux[i];
             lcd.print( card1[i], DEC);
             lcd.print( " ");
             flag =1;
            }
           delay(3000);
           lcd.clear();
           lcd.print(" Aproxime o card");
           lcd.setCursor(0,1);
           lcd.print("  Para Acesso   ");
           } 

           else{
            
           
             for (byte i = 0; i < mfrc522.uid.size; i++) {
               if(aux[i] == card1[i])
                cnt++;
             }
                            
            if(cnt == mfrc522.uid.size-1)
            {
              lcd.clear();
              lcd.print("     ACESSO     ");
              lcd.setCursor(0,1);
              lcd.print("   PERMITIDO    ");
              delay(2000);
             }
             else
             {
              lcd.clear();
              lcd.print("     ACESSO     ");
              lcd.setCursor(0,1);
              lcd.print("     NEGADO     ");
              delay(2000);
             }
             
           }
           
           lcd.clear();
           lcd.print(" Aproxime o card");
           lcd.setCursor(0,1);
           lcd.print("  Para Acesso   ");
  cnt=0;
}

