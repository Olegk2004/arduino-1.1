// подключение библиотеки
#include <AccelStepper.h>

// создаем экземпляр AccelStepper
#define CLK 3
#define DIO 2
#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO);
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
int q = 0;
int flag = 1;
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
  if (lbut == 0 && cbut == 1 && number_of_position != 1){
    number_of_position -= 1;
    side = 1;
    if (number_of_position == 1){
      num = 0;
    }if (number_of_position == 2){
      num = -1006;
    }if (number_of_position == 3){
      num = -1550;
    }if (number_of_position == 4){
      num = -2116;
    }if (number_of_position == 5){
      num = -2580;
    }if (number_of_position == 6){
      num = -3226;
    }
  }
  lbut = cbut;
  cbut2 = deb(lbut2, pinBut2);
  if (lbut2 == 0 && cbut2 == 1 && number_of_position != 6){
    number_of_position += 1;
    side = -1;
      if (number_of_position == 1){
        num = 0;
      }if (number_of_position == 2){
        num = -1006;
      }if (number_of_position == 3){
        num = -1573;
      }if (number_of_position == 4){
        num = -2116;
      }if (number_of_position == 5){
        num = -2595;
      }if (number_of_position == 6){
        num = -3226;
    }
  }
  lbut2 = cbut2;
  Serial.println(stepper.currentPosition());
  pot_value = analogRead(PIN_POT);
  if (flag == 1){
    if (pot_value > 297){
      stepper.setSpeed(500 * side);
      stepper.runSpeed();
      q = 1;
    }
    else if(pot_value < 297){
      stepper.setSpeed(-500);
      stepper.runSpeed();
      q = 1;
    }
    else{
     stepper.stop();
     stepper.setCurrentPosition(0);
     delay(1000);
     flag = 0;
     q = 0;
  }
  }else{
    if (stepper.currentPosition() != num){
      stepper.setSpeed(500 * side);
      stepper.runSpeed();
      q = 1;
    }else{
      stepper.stop();
      q = 0;
      }
  } 
  if(pot_value >= 296 && pot_value <= 298){
    disp.displayByte(1, _1);
  }
  else if(pot_value >= 358 && pot_value <= 359 && side == -1){
    disp.displayByte(1, _3);
  }
  else if(pot_value >= 355 && pot_value <= 356 && side == 1){
    disp.displayByte(1, _3);
  }
  else if(pot_value >= 395 && pot_value <= 396 && side == -1){
    disp.displayByte(1, _5);
  }
  else if(pot_value >= 392 && pot_value <= 393 && side == 1){
    disp.displayByte(1, _5);
  }
  else{
    disp.displayByte(1, _empty);
  }
  if (q == 1){
    disp.displayByte(0, _empty);
  }else if (number_of_position == 1){
    disp.displayByte(0, _1);
  }else if (number_of_position == 2){
    disp.displayByte(0, _2);
  }else if (number_of_position == 3){
    disp.displayByte(0, _3);
  }else if (number_of_position == 4){
    disp.displayByte(0, _4);
  }else if (number_of_position == 5){
    disp.displayByte(0, _5);
  }else if (number_of_position == 6){
    disp.displayByte(0, _6);
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
