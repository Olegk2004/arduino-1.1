// подключение библиотеки
#include <AccelStepper.h>
// создаем экземпляр AccelStepper
#define A  8
#define B  7
#define C  6
#define D  5
#define E  4
#define F  3
#define G  2
#define IN1 A4
#define IN2 A3
#define IN3 A2
#define IN4 A1
#define PIN_POT A5
AccelStepper stepper(8, IN1, IN3, IN2, IN4);

// клавиши выбора режима
int pinBut2 = 13;
int lbut2 = 1;
int cbut2 = 1;
int pinBut = 12;
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
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
}


void loop() {  
  cbut = deb(lbut, pinBut);
  if (lbut == 0 && cbut == 1 && num > -4095){
    num -= 455;
    q = -1;
  }
  lbut = cbut;
  cbut2 = deb(lbut2, pinBut2);
  if (lbut2 == 0 && cbut2 == 1 && num < 0){
    num += 455;
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
  Serial.println(corpot);
  if (stepper.currentPosition() != num){
    digitalWrite(A, LOW); //при движении двишателя дисплей отключается
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
  }else if (num / 455 == -1){
    digitalWrite(A, LOW); //цифра один
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
  }else if (num / 455 == -2){
    digitalWrite(A, HIGH); //цифра два
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, LOW);
    digitalWrite(G, HIGH);
  }else if (num / 455 == -3){
    digitalWrite(A, HIGH); //цифра три
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, HIGH);
  }else if (num / 455 == -4){
    digitalWrite(A, LOW); //цифра четыре
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
  }else if (num / 455 == -5){
    digitalWrite(A, HIGH); //цифра пять
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, LOW);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
  }else if (num / 455 == -6){
    digitalWrite(A, HIGH); //цифра шесть
    digitalWrite(B, LOW);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
  }else if (num / 455 == -7){
    digitalWrite(A, HIGH); //цифра семь
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
  }else if(num / 409 == -8){
    digitalWrite(A, HIGH); //цифра восемь
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
  }else if(num / 455 == -9){
    digitalWrite(A, HIGH); //цифра девять
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, LOW);
    digitalWrite(F, HIGH);
    digitalWrite(G, HIGH);
  }else if (num == 0){
    digitalWrite(A, HIGH); //цифра ноль
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);
    digitalWrite(G, LOW);
  }
}

// устранение дребезга
int deb (int l,int pin){
  int c = digitalRead(pin);
  if (l != c) { // если изменение
    delay(5);
    c = digitalRead(pin);
    return c;
    }
  }
