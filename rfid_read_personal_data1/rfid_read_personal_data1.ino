/*
 * ----------------------------------------------------------------------
 * rfid_read_personal_data
 * ----------------------------------------------------------------------
 * https://circuits4you.com
 * 
 * RC522 Interfacing with NodeMCU
 * 
 * Typical pin layout used:
 * ----------------------------------
 *             MFRC522      Node     
 *             Reader/PCD   MCU      
 * Signal      Pin          Pin      
 * ----------------------------------
 * RST/Reset   RST          D1 (GPIO5)        
 * SPI SS      SDA(SS)      D2 (GPIO4)       
 * SPI MOSI    MOSI         D7 (GPIO13)
 * SPI MISO    MISO         D6 (GPIO12)
 * SPI SCK     SCK          D5 (GPIO14)
 * 3.3V        3.3V         3.3V
 * GND         GND          GND
 */

#include <SPI.h>
#include <MFRC522.h>

constexpr uint8_t RST_PIN = 5;     // Configurable, see typical pin layout above
constexpr uint8_t SS_PIN = 4;     // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

//*****************************************************************************************//
void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read
}


void loop() {

  
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  byte block;
  byte len;
  MFRC522::StatusCode status;
      if ( ! mfrc522.PICC_IsNewCardPresent()) {
          mfrc522.PICC_HaltA();
          mfrc522.PCD_StopCrypto1();
          return;
          }
      if ( ! mfrc522.PICC_ReadCardSerial()) {
          mfrc522.PICC_HaltA();
           mfrc522.PCD_StopCrypto1();
        return;
        }
  Serial.println(F("**Card Detected:**"));
  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------
  //Serial.print(F("Name: "));
  Serial.println("Data");
  Serial.println("");
  

  byte buffer1[18];
  block = 1;
  len = 18;
  for (block=0;block<16;block++)
  {
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    return;
  }
    status = mfrc522.MIFARE_Read(block, buffer1, &len);
        if (status != MFRC522::STATUS_OK) {
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        mfrc522.PICC_HaltA();
        mfrc522.PCD_StopCrypto1();
        return;
        }

   Serial.print(block<0x10 ? " 0" : " ");
   Serial.print(block, HEX);
    Serial.print("    ");     
    for (uint8_t i = 0; i < 16; i++)
  {
    
      Serial.print(buffer1[i]<0x10 ? " 0" : " ");
      Serial.print(buffer1[i], HEX);
      Serial.print(" ");
   }
    
    Serial.print("    ");
   for (uint8_t i = 0; i < 16; i++)
  {
    
      Serial.print(char(buffer1[i]));
     
      Serial.print(" ");
   }
  Serial.println(" ");
  }
  
  Serial.println(F("\n**End Reading**\n"));

  delay(1000); //change value if you want to read cards faster

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}
//*****************************************************************************************//
