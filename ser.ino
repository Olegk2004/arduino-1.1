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
//1-0
//2-27
//3-39
//4-51
//5-63
//6-75
// клавиши выбора режима
int pinBut2 = 10;
int lbut2 = 1;
int cbut2 = 1;
int pinBut = 11;
int lbut = 1;
int cbut = 1;
int pot_value = 1023;
int nap = -1;
int side = 1;
int number_of_position = 1;
int correct_pot = 0;
int lastpot = 139;
int flag = 1;

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
  if (lbut == 0 && cbut == 1 && number_of_position != 1){
    number_of_position -= 1;
    side = 1;
    flag = 1;
  }
  lbut = cbut;
  cbut2 = deb(lbut2, pinBut2);
  if (lbut2 == 0 && cbut2 == 1 && number_of_position != 6){
    number_of_position += 1;
    side = -1;
    flag = 1;
  }
  lbut2 = cbut2;
  if (number_of_position == 1){
    correct_pot = 1;
  }if (number_of_position == 2){
    correct_pot = 27;
  }if (number_of_position == 3){
    correct_pot = 39;
  }if (number_of_position == 4){
    correct_pot = 51;
  }if (number_of_position == 5){
    correct_pot = 63;
  }if (number_of_position == 6){
    correct_pot = 75;
  }
  Serial.println(pot_value);
  pot_value = analogRead(PIN_POT);
  if (abs(pot_value - correct_pot) > 1 && flag == 1){
    stepper.setSpeed(500 * side);
    stepper.runSpeed();
  }else{
    stepper.stop();
    flag = 0;
    }
  if (flag == 1){
    disp.display("p", "p", "p", "p");
  }else if (number_of_position == 1){
    disp.display(0, 1);
  }else if (number_of_position == 2){
    disp.display(0, 2);
  }else if (number_of_position == 3){
    disp.display(0, 3);
  }else if (number_of_position == 4){
    disp.display(0, 4);
  }else if (number_of_position == 5){
    disp.display(0, 5);
  }else if (number_of_position == 6){
    disp.display(0, 6);
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
