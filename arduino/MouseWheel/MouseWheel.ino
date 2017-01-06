#include "Mouse.h"

int pinA = 2;
int pinB = 3;

volatile int previous = 0;
volatile int counter = 0;

void setup() {
  pinMode(pinA, INPUT_PULLUP); 
  pinMode(pinB, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(pinA), changed, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(pinB), changed, CHANGE);
  
  Mouse.begin();
}

void changed() {
  int A = digitalRead(pinA); 
  int B = digitalRead(pinB);

  int current = (A << 1) | B;
  int combined  = (previous << 2) | current;
   
  if(combined == 0b0010 || 
     combined == 0b1011 ||
     combined == 0b1101 || 
     combined == 0b0100) {
    counter++;
  }
   
  if(combined == 0b0001 ||
     combined == 0b0111 ||
     combined == 0b1110 ||
     combined == 0b1000) {
    counter--;
  }

  previous = current;
}

void loop(){ 
  if(counter >= 4) {
    Mouse.move(0,0,1);
    counter -= 4;
  } else if(counter <= -4) {
    Mouse.move(0,0,-1);
    counter += 4;
  } 
}
