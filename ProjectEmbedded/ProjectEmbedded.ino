#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#define r_led 2
#define g_led 3
#define buzzer 8
#define trigger_pin 7
#define echo_pin 4
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
Servo myservo1;
Servo myservo2;
LiquidCrystal_I2C lcd(0x3F,16,2); 
int block=2;
byte blockcontent[16] = {"Anda-Sudah-Masuk"};
//byte blockcontent[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte readbackblock[18];

void setup() {
  Serial.begin(9600);
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(r_led, OUTPUT);
  pinMode(g_led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  myservo1.attach(5);
  SPI.begin();     
  mfrc522.PCD_Init();   
  lcd.begin();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Tempelkan Kartu!");
}

void loop(){
  long duration;
  float distance;
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  duration = pulseIn (echo_pin, HIGH);
  distance = duration * 0.034/2;
  //Serial.println (distance);
  if(distance < 20){
    myservo1.write(90);
    digitalWrite(g_led, LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tempelkan Kartu!");
  }

  for (byte i = 0; i < 6; i++)
  {
    key.keyByte[i] = 0xFF;
  }
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  readblock(block, readbackblock);

  String data = "";
  for (byte i = 0; i < 16; i++) {
    data += char(readbackblock[i]);
  }
  Serial.println(data);

  if (!data.equals(blockcontent)) {
    writeblock(block, blockcontent);
    digitalWrite(g_led, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Silahkan Masuk!");
    delay(500);
    myservo1.write(180);
    delay(1000);
  }  
  else {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print("Anda Telah");
    lcd.setCursor(1, 1);
    lcd.print("Menaiki Wahana");
    digitalWrite(r_led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(r_led, LOW);
    digitalWrite(buzzer, LOW);
    delay(500);
  }
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
} 

void writeblock(int blocknumber, byte arrayaddress[]){
  int trailerBlock=blocknumber+(4-blocknumber%4)-1;

  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed: ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
  else{
    Serial.println("Berhasil Autentikasi");
  }
  
  status = mfrc522.MIFARE_Write(blocknumber, arrayaddress, 16);
  //status = mfrc522.MIFARE_Write(9, value1Block, 16);
  if (status != MFRC522::STATUS_OK) {
           Serial.print("MIFARE_Write() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return 4;//return "4" as error message
  }
  else{
    Serial.println("Berhasil Tulis");
  }
}

void readblock(int blocknumber, byte arrayaddress[]){
  int largestModulo4Number=blocknumber/4*4;
  int trailerBlock=largestModulo4Number+3;

  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed: ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }
  else{
    Serial.println("Berhasil Autentikasi");
  }
  
  byte buffersize = 18;
  status = mfrc522.MIFARE_Read(blocknumber, arrayaddress, &buffersize);
  if (status != MFRC522::STATUS_OK) {
           Serial.print("MIFARE_Write() failed: ");
           Serial.println(mfrc522.GetStatusCodeName(status));
           return 4;//return "4" as error message
  }
  else{
    Serial.println("Berhasil Baca");
  }
}