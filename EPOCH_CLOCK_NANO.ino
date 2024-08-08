/*
  Project: Epoch Clock Nano
  Description: Epoch Clock using arduino nano and  7-segment display x 10
  Author: Y-ZEN
  Date: 08/07/2024
  Version: 1.0
  License: MIT License
  Note: Remember to disconnect pin RX/TX during code upload on Arduino 

  TX1 -|< 1 
  RX0 -|< 2 
  D2 ->|- 4
  D3 ->|- 5
  D4 ->|- 9
  D5 ->|- 7
  D6 ->|- 6
  D7 ->|- 2
  D8 ->|- 1
  D9 Empty
  D10 -|< 10 
  D11 -|< 9 
  D12 -|< 8 
  A7 Button 
  A6 Button
  A5 SCL
  A4 SDA
  A3 -|< 3 
  A2 -|< 4 
  A1 -|< 5 
  A0 -|< 6 
  REF Empty
  3v3 Empty
  D13 -|< 7 
*/

#include <RTClib.h>

RTC_DS3231 rtc;

const byte pinA = 2;
const byte pinB = 3;
const byte pinC = 4;
const byte pinD = 5;
const byte pinE = 6;
const byte pinF = 7;
const byte pinG = 8;

const byte pinGND0 = A0;
const byte pinGND1 = A1;
const byte pinGND2 = A2;
const byte pinGND3 = A3;
const byte pinGND4 = A4;
const byte pinGNDRX = 0;
const byte pinGND5 = A5;
const byte pinGNDTX = 1;

const byte pinBTN1 = A6;
const byte pinBTN2 = A7;

const byte pinGND10 = 10;
const byte pinGND11 = 11;
const byte pinGND12 = 12;
const byte pinGND13 = 13;

bool fixTime = true;
long lastMillis = 0;
long diffMillis = 0;
long seconds = 1710507950;
int epoch[10] = {0,0,0,0,0,0,0,0,0,0};
String epochString = "";

const int PRESS_DELAY = 100;
const int BLINK_DELAY = 500;


bool currStateBTN1 = false;
bool lastStateBTN1 = false;
bool flikerStateBTN1 = false;
unsigned long lastPressedTimeBTN1 = 0;

int selectDigit = -1;
unsigned long lastBlinked = 0;
bool blinkOff = false;


bool currStateBTN2 = false;
bool lastStateBTN2 = false;
bool flikerStateBTN2 = false;
unsigned long lastPressedTimeBTN2 = 0;

void setup() {                

  //Serial.begin(9600);

  // SETUP RTC MODULE
  if (! rtc.begin()) {
    //Serial.println("Couldn't find RTC");
    //Serial.flush();
    while (1);
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));

// initialize the digital pins as outputs.
  pinMode(pinA, OUTPUT);   
  pinMode(pinB, OUTPUT);   
  pinMode(pinC, OUTPUT);   
  pinMode(pinD, OUTPUT);    
  pinMode(pinE, OUTPUT);   
  pinMode(pinF, OUTPUT);    
  pinMode(pinG, OUTPUT);    

  pinMode(pinGND0, OUTPUT); 
  pinMode(pinGND1, OUTPUT); 
  pinMode(pinGND2, OUTPUT);
  pinMode(pinGND3, OUTPUT); 
  //pinMode(pinGND4, OUTPUT); 
  pinMode(pinGNDRX, OUTPUT);  
  //pinMode(pinGND5, OUTPUT);
  pinMode(pinGNDTX, OUTPUT);  
  pinMode(pinGND10, OUTPUT); 
  pinMode(pinGND11, OUTPUT); 
  pinMode(pinGND12, OUTPUT); 
  pinMode(pinGND13, OUTPUT); 


}

void displayOff() {
  digitalWrite(pinA, LOW);  
  digitalWrite(pinB, LOW);
  digitalWrite(pinC, LOW);  
  digitalWrite(pinD, LOW);    
  digitalWrite(pinE, LOW);    
  digitalWrite(pinF, LOW);    
  digitalWrite(pinG, LOW);    
  analogWrite(pinGND0, 0);
  analogWrite(pinGND1, 0);
  analogWrite(pinGND2, 0);
  analogWrite(pinGND3, 0);
  //analogWrite(pinGND4, 0);
  digitalWrite(pinGNDRX, LOW);
  //analogWrite(pinGND5, 0);
  digitalWrite(pinGNDTX, LOW);
  digitalWrite(pinGND10, LOW);    
  digitalWrite(pinGND11, LOW);    
  digitalWrite(pinGND12, LOW);    
  digitalWrite(pinGND13, LOW);    
}

void segmentOn(byte pin){
  digitalWrite(pin, HIGH);
  digitalWrite(pin, LOW);
}

void writeNumber(int n,int d, int sel, bool off) {
  displayOff();

  if (d == 0) {
    if ((d == sel) && (off == true)) {
     
    }
    else {
      digitalWrite(pinGND10, HIGH);
    }
  }

  if (d == 1) {
    if ((d == sel) && (off == true)) {

    }
    else {
     digitalWrite(pinGND11, HIGH);
    }
  }

  if (d == 2) {
    if ((d == sel) && (off == true)) {

    }
    else {
     digitalWrite(pinGND12, HIGH);
    }
  }

  if (d == 3) {
    if ((d == sel) && (off == true)) {

    }
    else {
     digitalWrite(pinGND13, HIGH);
    }
  }

  if (d == 4) {
    if ((d == sel) && (off == true)) {

    }
    else {
     analogWrite(pinGND0, 255);
    }
  }

  if (d == 5) {
    if ((d == sel) && (off == true)) {

    }
    else {
     analogWrite(pinGND1, 255);
    }
  }

  if (d == 6) {
    if ((d == sel) && (off == true)) {

    }
    else {
     analogWrite(pinGND2, 255);
    }
  }

  if (d == 7) {
    if ((d == sel) && (off == true)) {

    }
    else {
     analogWrite(pinGND3, 255);
    }
  }

  if (d == 8) {
    if ((d == sel) && (off == true)) {

    }
    else {
     //analogWrite(pinGND4, 255);
     digitalWrite(pinGNDRX, HIGH);
    }
  }

  if (d == 9) {
    if ((d == sel) && (off == true)) {

    }
    else {
     //analogWrite(pinGND5, 255);
     digitalWrite(pinGNDTX, HIGH);
    }
  }



  if (n == 0) {
    segmentOn(pinA);
    segmentOn(pinB);
    segmentOn(pinC);
    segmentOn(pinD);
    segmentOn(pinE);
    segmentOn(pinF);
  }
  if (n == 1) {
    segmentOn(pinB);
    segmentOn(pinC);
  }
  if (n == 2) {
    segmentOn(pinA);
    segmentOn(pinB);
    segmentOn(pinG);
    segmentOn(pinE);
    segmentOn(pinD);
  }
  if (n == 3) {
    segmentOn(pinA);
    segmentOn(pinB);
    segmentOn(pinG);
    segmentOn(pinC);
    segmentOn(pinD);
  }
  if (n == 4) {
    segmentOn(pinF);
    segmentOn(pinB);
    segmentOn(pinG);
    segmentOn(pinC);
  }
  if (n == 5) {
    segmentOn(pinA);
    segmentOn(pinF);
    segmentOn(pinG);
    segmentOn(pinC);
    segmentOn(pinD);
  }
  if (n == 6) {
    segmentOn(pinA);
    segmentOn(pinF);
    segmentOn(pinG);
    segmentOn(pinC);
    segmentOn(pinD);
    segmentOn(pinE);
  }
  if (n == 7) {
    segmentOn(pinA);
    segmentOn(pinB);
    segmentOn(pinC);
  }
  if (n == 8) {
    segmentOn(pinA);
    segmentOn(pinB);
    segmentOn(pinC);
    segmentOn(pinD);
    segmentOn(pinE);
    segmentOn(pinF);
    segmentOn(pinG);
  }
  if (n == 9) {
    segmentOn(pinA);
    segmentOn(pinB);
    segmentOn(pinC);
    segmentOn(pinD);
    segmentOn(pinF);
    segmentOn(pinG);
  }

  displayOff();
}

void loop() {
  long currentMillis = millis();
  
  if(currentMillis - lastMillis >= 1000 && selectDigit==-1){
    DateTime now = rtc.now();
    
    //Serial.println(now.unixtime(), DEC);

    lastMillis = currentMillis;
    seconds = now.unixtime();

    if (seconds > 9999999999) {
      seconds = 0;
    }
    long x = 0;
    long y;
    int i = 0;
    //int epoch[] = {0,0,0,0,0,0,0,0,0,0};
    x = seconds;
    while ( x > 0 ){
        y=x/10 ;
        epoch[i] = x-(10*y) ;
        x=y ;
        i++ ;
    }
  }

  writeNumber(epoch[0],0,selectDigit,blinkOff);
  writeNumber(epoch[1],1,selectDigit,blinkOff);
  writeNumber(epoch[2],2,selectDigit,blinkOff);
  writeNumber(epoch[3],3,selectDigit,blinkOff);
  writeNumber(epoch[4],4,selectDigit,blinkOff);
  writeNumber(epoch[5],5,selectDigit,blinkOff);
  writeNumber(epoch[6],6,selectDigit,blinkOff);
  writeNumber(epoch[7],7,selectDigit,blinkOff);
  writeNumber(epoch[8],8,selectDigit,blinkOff);
  writeNumber(epoch[9],9,selectDigit,blinkOff);
  
  int readBT1 = analogRead(pinBTN1);
  if (readBT1 > 1000) {
    currStateBTN1 = true;
  } else {
    currStateBTN1 = false;
  }


  if ( flikerStateBTN1 != currStateBTN1) {
      lastPressedTimeBTN1 = currentMillis;
      flikerStateBTN1 = currStateBTN1;
  }

  if ((currentMillis - lastPressedTimeBTN1) > PRESS_DELAY) {

      if ( lastStateBTN1 == false && currStateBTN1 == true) {
        selectDigit++;
        if (selectDigit > 9) {
          rtc.adjust(DateTime(seconds));
          selectDigit = -1;
        }
      }
      lastStateBTN1 = currStateBTN1;
      lastPressedTimeBTN1 = currentMillis;
  }


  
  if (((currentMillis - lastBlinked) > BLINK_DELAY) && (selectDigit != -1)) {
    lastBlinked = currentMillis;
    if (blinkOff == true) {
      blinkOff = false;
    } else {
      blinkOff = true;
    }

  }

  int readBT2 = analogRead(pinBTN2); 
  if (readBT2 > 1000) {
    currStateBTN2 = true;
  } else {
    currStateBTN2 = false;
  }


  if ( flikerStateBTN2 != currStateBTN2) {
      lastPressedTimeBTN2 = currentMillis;
      flikerStateBTN2 = currStateBTN2;
  }

  if ((currentMillis - lastPressedTimeBTN2) > PRESS_DELAY) {
     
      if ( lastStateBTN2 == false && currStateBTN2 == true && selectDigit != -1) {
        int n = epoch[selectDigit];
        n++;
        if (n > 9) {
          n = 0;
        }
        epoch[selectDigit] = n;
        epochString = "";
        for (int i = 9; i > -1; --i) {
            epochString += String(epoch[i]);
        }
        
        // Convert the string to a numeric value of type long
        seconds = atol(epochString.c_str());
      }
      lastStateBTN2 = currStateBTN2;
      lastPressedTimeBTN2 = currentMillis;
  }

}