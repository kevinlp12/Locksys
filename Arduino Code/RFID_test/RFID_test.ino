#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "pitches.h"

#define IRQ 2
#define RESET 3
#define speakerPin 12 // Piezo 9

int RFIDResetPin = 13;

// RGB LED Pins
const int RED_PIN = 5;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

LiquidCrystal_I2C lcd(0x3F,20,4); // (LCD address, 20 char, 4 lines)

// notes in the melody:
int melodya[] = {NOTE_C5, NOTE_G5, NOTE_C6};
int melodyb[] = {NOTE_C2, NOTE_C2, NOTE_C2};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurationsa[] = {8, 8, 4};
int noteDurationsb[] = {8, 8, 8};

//Register your RFID tags here
char tag1[13] = "6A0049AEAA27"; //MASTER
char tag2[13] = "010230F28243";
char tag3[13] = "01023C013A04";
char tag4[13] = "01023101093A";
char tag5[13] = "01023C0A4376";
char tag6[13] = "01023C000E31";
char tag7[13] = "01023C0A3207";
char tag8[13] = "1A004116317C";
char tag9[13] = "1E009A81F9FC";
char tag10[13] = "1A004162261F";

void setup(){
  Serial.begin(9600);
  
  pinMode(speakerPin, OUTPUT);
  pinMode(RFIDResetPin, OUTPUT);
  digitalWrite(RFIDResetPin, HIGH);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
  
  delay(10);
  
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0,0);
  lcd.print("    Please Scan");
  lcd.setCursor(0,1);
  lcd.print("    Access Card");
}

void loop(){

  char tagString[13];
  int index = 0;
  boolean reading = false;

  while(Serial.available()){

    int readByte = Serial.read(); //read next available byte

    if(readByte == 2) reading = true; //begining of tag
    if(readByte == 3) reading = false; //end of tag

    if(reading && readByte != 2 && readByte != 10 && readByte != 13){
      //store the tag
      tagString[index] = readByte;
      index ++;
    }
  }

  checkTag(tagString); //Check if it is a match
  clearTag(tagString); //Clear the char of all value
  resetReader(); //eset the RFID reader
}

void checkTag(char tag[]){
///////////////////////////////////
//Check the read tag against known tags
///////////////////////////////////

  if(strlen(tag) == 0) return; //empty, no need to contunue

  if(compareTag(tag, tag1)){ // if matched tag1, do this
    
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("  Access Granted.");   
    
    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, LOW);
    delay(75);
    digitalWrite(GREEN_PIN, LOW);
    delay(75);
    digitalWrite(GREEN_PIN, HIGH);  
    delay(75);
    digitalWrite(GREEN_PIN, LOW);
    delay(75);
    digitalWrite(GREEN_PIN, HIGH);  
    delay(75);
    digitalWrite(GREEN_PIN, LOW);
    delay(75);
    digitalWrite(GREEN_PIN, HIGH);
    delay(75);
    digitalWrite(GREEN_PIN, LOW);
    delay(75);
    digitalWrite(GREEN_PIN, HIGH);
    
    for (int thisNote = 0; thisNote < 3; thisNote++) {
      int noteDurationa = 1000/noteDurationsa[thisNote];
      tone(9, melodya[thisNote],noteDurationa);
  
      int pauseBetweenNotes = noteDurationa * 1.30;
      delay(pauseBetweenNotes);
      noTone(9);
      }
      
    delay(2000); 
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("      Welcome");
    lcd.setCursor(0,1);
    lcd.print("    Phillip Davis");
    lcd.setCursor(0,2);
    lcd.print(" Clearance Level 3");  
    lcd.setCursor(0,3);
    lcd.print("       * * *"); 
    
    delay(5000);
  
  }else if(compareTag(tag, tag2)){ //if matched tag2, do this
    ;

  }else if(compareTag(tag, tag3)){
    ;

  }else if(compareTag(tag, tag4)){
    ;

  }else if(compareTag(tag, tag5)){
    ;

  }else if(compareTag(tag, tag6)){
    ;

  }else if(compareTag(tag, tag7)){
    ;

  }else if(compareTag(tag, tag8)){
    ;

  }else if(compareTag(tag, tag9)){
    ;

  }else if(compareTag(tag, tag10)){
    ;

  }else{
    Serial.println(tag); //read out any unknown tag
    /*
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  
    for (int thisNote = 0; thisNote < 2; thisNote++) {
      int noteDurationb = 1000/noteDurationsb[thisNote];
      tone(9, melodyb[thisNote],noteDurationb);
  
      int pauseBetweenNotes = noteDurationb * 1.30;
      delay(pauseBetweenNotes);
      noTone(9); 
  }*/
  }

}

void resetReader(){
///////////////////////////////////
//Reset the RFID reader to read again.
///////////////////////////////////
  digitalWrite(RFIDResetPin, LOW);
  digitalWrite(RFIDResetPin, HIGH);
  delay(150);
}

void clearTag(char one[]){
///////////////////////////////////
//clear the char array by filling with null - ASCII 0
//Will think same tag has been read otherwise
///////////////////////////////////
  for(int i = 0; i < strlen(one); i++){
    one[i] = 0;
  }
}

boolean compareTag(char one[], char two[]){
///////////////////////////////////
//compare two value to see if same,
//strcmp not working 100% so we do this
///////////////////////////////////

  if(strlen(one) == 0) return false; //empty

  for(int i = 0; i < 12; i++){
    if(one[i] != two[i]) return false;
  }

  return true; //no mismatches
}
