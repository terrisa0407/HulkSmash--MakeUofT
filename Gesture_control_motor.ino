#include <Wire.h>
#include "paj7620.h"

#define GES_REACTION_TIME   500       
#define GES_ENTRY_TIME      800       
#define GES_QUIT_TIME     1000

void setup()
{
  uint8_t error = 0;

  Serial.begin(9600);
  Serial.println("\nPAJ7620U2 TEST DEMO: Recognize 9 gestures.");

  error = paj7620Init();      // initialize Paj7620 registers
  for(int i = 9; i<14; i++){
    pinMode(i, OUTPUT);
  }
  if (error) 
  {
    Serial.print("INIT ERROR,CODE:");
    Serial.println(error);
  }
  else
  {
    Serial.println("INIT OK");
  }
  Serial.println("Please input your gestures:\n");
}

uint8_t gesture = 0;

uint8_t read_gesture(){
  uint8_t data, data1, error;
  error = paj7620ReadReg(0x43, 1, &data);       
  if (!error) 
  {
    switch (data)                   
    {
      case GES_RIGHT_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          delay(GES_QUIT_TIME);
        }
        break;
      case GES_LEFT_FLAG: 
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          delay(GES_QUIT_TIME);
        }         
        break;
      case GES_UP_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          delay(GES_QUIT_TIME);
        }  
        break;
      case GES_DOWN_FLAG:
        delay(GES_ENTRY_TIME);
        paj7620ReadReg(0x43, 1, &data);
        if(data == GES_FORWARD_FLAG) 
        {
          delay(GES_QUIT_TIME);
        }
        else if(data == GES_BACKWARD_FLAG) 
        {
          delay(GES_QUIT_TIME);
        }         
        break;
      case GES_FORWARD_FLAG:
        delay(GES_QUIT_TIME);
        break;
      case GES_BACKWARD_FLAG:     
        delay(GES_QUIT_TIME);
        break;
      case GES_CLOCKWISE_FLAG:
        break;
      case GES_COUNT_CLOCKWISE_FLAG:
        break;  
      default:
        paj7620ReadReg(0x44, 1, &data1);
        break;
    }  
    return data;
  }
}

void loop()
{
    int constant = 8;
    
    uint8_t gestureNow = read_gesture(); 
    if(gestureNow != 0){
      gesture = gestureNow;
      Serial.println(gesture);
    }
    if(gesture == GES_CLOCKWISE_FLAG){
      for(int i = 9; i<14; i++){
        digitalWrite(i, HIGH);
        if(i-1<9){
          digitalWrite(13, HIGH);
        }
        else{
          digitalWrite(i-1, HIGH); 
        }
        delay(2);
        if(i-1<9){
          digitalWrite(13, LOW);
        }
        else{
          digitalWrite(i-1, LOW); 
        }
      }
    }
    if(gesture == GES_COUNT_CLOCKWISE_FLAG){
      for(int i = 13; i>=9; i--){
        digitalWrite(i, LOW);
        delay(3);
        digitalWrite(i, HIGH);
      } 
    }
  delay(10);
}
