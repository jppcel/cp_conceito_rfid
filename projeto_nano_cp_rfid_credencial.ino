

/*
 * 
 * All the resources for this project: http://randomnerdtutorials.com/
 * Modified by Rui Santos
 * 
 * Created by FILIPEFLOP
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define BUZ 8

#define RED 3
#define BLUE 4
#define GREEN 2
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() {
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();

  pinMode(BUZ, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(BLUE, HIGH);
  

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "64 7E 64 EB") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    setColor(1);
    tone(BUZ,2000);    
    // Espera um tempo para Desativar
    delay(1000);
    //Desativa o buzzer
    noTone(BUZ); 
    delay(2000);
    setColor(0);
  }
 
 else   {
    Serial.println(" Access denied");
    setColor(2);
    tone(BUZ,200);    
    // Espera um tempo para Desativar
    delay(200);
    setColor(3);
    tone(BUZ,300);  
    delay(200);
    setColor(2);
    noTone(BUZ);   
    // Espera um tempo para Desativar
    delay(200);
    setColor(2);
    tone(BUZ,200);    
    delay(200);
    setColor(3);
    noTone(BUZ); 
    // Espera um tempo para Desativar
    delay(200);
    setColor(2);
    tone(BUZ,300);    
    delay(200);
    noTone(BUZ); 
    delay(2000);
    setColor(0);
  }
} 

void setColor(int color){
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  switch(color){
    case 0:
      digitalWrite(BLUE, HIGH);
      break;
    case 1:
      digitalWrite(GREEN, HIGH);
      break;
    case 2:
      digitalWrite(RED, HIGH);
      break;
  }
}

