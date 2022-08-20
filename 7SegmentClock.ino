#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

int d1Pin = 12;
int d2Pin = 11;
int d3Pin = 10;
int d4Pin = 9;
int clockPin = 6;
int latchPin = 5;
int dataPin = 4;
int digitPins[4] = {12,11,10,9};

int digit1 = 0;
int digit2 = 0;
int digit3 = 0;
int digit4 = 0;

byte numbers[10] {B11111100, B01100000, B11011010, B11110010, B01100110, B10110110, B10111110, B11100000, B11111110, B11110110};
int digits[4];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(d1Pin,OUTPUT);
  pinMode(d2Pin,OUTPUT);
  pinMode(d3Pin,OUTPUT);
  pinMode(d4Pin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(dataPin,OUTPUT);

  digitalWrite(d1Pin,LOW);
  digitalWrite(d2Pin,LOW);
  digitalWrite(d3Pin,LOW);
  digitalWrite(d4Pin,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  tmElements_t tm;
  int tmMin;
  int tmSec;
  if(RTC.read(tm)){
    tmMin = tm.Minute;
    tmSec = tm.Second;
  }
  //Parse input
  digit1 = tmMin / 10;
  digits[0] = digit1;
  digit2 = (tmMin - (digit1 * 10));
  digits[1] = digit2;
  digit3 = tmSec / 10;
  digits[2] = digit3;
  digit4 = (tmSec - (digit3 * 10));
  digits[3] = digit4; 

  //Display number
  for(int i = 0; i < 4; i++){
    digitalWrite(d1Pin,HIGH);
    digitalWrite(d2Pin,HIGH);
    digitalWrite(d3Pin,HIGH);
    digitalWrite(d4Pin,HIGH);  
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,numbers[digits[i]]);
    digitalWrite(digitPins[i],LOW);
    digitalWrite(latchPin,HIGH);   
    delay(1); 
  }
}
