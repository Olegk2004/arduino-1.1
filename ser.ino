// подключение библиотеки
#include <AccelStepper.h>
// создаем экземпляр AccelStepper
#define CLK 3
#define DIO 2
#include "TM1637.h"
TM1637 disp(CLK, DIO);
#define IN1 A4
#define IN2 A3
#define IN3 A2
#define IN4 A1
#define PIN_POT A5
AccelStepper stepper(8, IN1, IN3, IN2, IN4);

// клавиши выбора режима
int pinBut2 = 10;
int lbut2 = 1;
int cbut2 = 1;
int pinBut = 11;
int lbut = 1;
int cbut = 1;
int corpot = 1023;
int nap = -1;
int q = -1;
boolean go=false;
int num = 0;

void setup(){
  Serial.begin(9600);
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(100);
  stepper.setSpeed(500);
  pinMode(PIN_POT, INPUT);
  disp.clear();
  disp.brightness(7);
}


void loop() {  
  cbut = deb(lbut, pinBut);
  if (lbut == 0 && cbut == 1 && num > -4095){
    num -= 585;
    q = -1;
  }
  lbut = cbut;
  cbut2 = deb(lbut2, pinBut2);
  if (lbut2 == 0 && cbut2 == 1 && num < 0){
    num += 585;
    q = 1;
  }
  lbut2 = cbut2;
  corpot = analogRead(PIN_POT);
  if (nap == -1){
    if(corpot >= 20){
      stepper.setSpeed(500);
      stepper.runSpeed();
      corpot = analogRead(PIN_POT);
    }else{
      nap = 1;
      stepper.setCurrentPosition(0);
      delay(1000);
    }
  }else{
    if (stepper.currentPosition() != num){
      stepper.setSpeed(500 * q);
      stepper.runSpeed();
    }else{
      stepper.stop();
    }
  }
  Serial.println(cbut);
  if (stepper.currentPosition() != num){
    disp.display("A", "A", "A", "A");
  }else if (num / 585 == 0){
    disp.display(0, 1);
  }else if (num / 585 == -1){
    disp.display(0, 2);
  }else if (num / 585 == -2){
    disp.display(0, 3);
  }else if (num / 585 == -3){
    disp.display(0, 4);
  }else if (num / 585 == -4){
    disp.display(0, 5);
  }else if (num / 585 == -5){
    disp.display(0, 6);
  }else if (num / 585 == -6){
    disp.display(0, 7);
  }else if(num / 585 == -7){
    disp.display(0, 8);
  }
}

// устранение дребезга
int deb (int l,int pin){
  int c = digitalRead(pin);
  if (l != c) { // если изменение
    delay(15);
    c = digitalRead(pin);
    return c;
    }
  }
