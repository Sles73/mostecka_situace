#include <Servo.h>

Servo myservo1;  
Servo myservo2;

const int side1[] = {4,5,6,7};
const int side2[] = {8,9,10,11};

int rychlost = 10;

#define SEMAFOR_PIN 3

#define SERVO_2 A0
#define SERVO_1 A5

#define LOWER_BUTTON A1
#define RAISE_BUTTON A2

#define GATE_OPEN 100
#define GATE_CLOSE 175

void setup() {
  for(int i = 0; i < 4; i++) pinMode(side1[i], OUTPUT);
  for(int i = 0; i < 4; i++) pinMode(side2[i], OUTPUT);

   Serial.begin(9600);
  pinMode(LOWER_BUTTON,INPUT);
  pinMode(RAISE_BUTTON,INPUT);
  
  pinMode(SEMAFOR_PIN,OUTPUT);
  digitalWrite(SEMAFOR_PIN,HIGH);

  myservo1.attach(SERVO_1);
  myservo2.attach(SERVO_2);  

  myservo1.write(GATE_OPEN);  
  myservo2.write(GATE_OPEN);  
  delay(1000);

}

void loop() {
  digitalWrite(SEMAFOR_PIN,LOW);

  delay(2000);

  myservo1.write(GATE_CLOSE);  
  myservo2.write(GATE_CLOSE);

  for(int i = 1; i < 80; i++){
    rotacePoSmeru(side1);
    rotacePoSmeru(side2);
  }


  delay(5000);



  for(int i = 1; i < 80; i++){
    rotaceProtiSmeru(side1);
    rotaceProtiSmeru(side2);
  }

  myservo1.write(GATE_OPEN);  
  myservo2.write(GATE_OPEN);

  delay(2000);

  digitalWrite(SEMAFOR_PIN,HIGH);

  delay(5000);

  /*
    if(digitalRead(LOWER_BUTTON) == HIGH){
    Serial.println("lower the bridge");
    rotaceProtiSmeru(side1);
    rotaceProtiSmeru(side2);
  }

  if(digitalRead(RAISE_BUTTON) == HIGH){
    Serial.println("raise the bridge");
    rotacePoSmeru(side1);
    rotacePoSmeru(side2);
  }
  */
}



void rotacePoSmeru(int side[]) {
  krok1(side);
  krok2(side);
  krok3(side);
  krok4(side);
  krok5(side);
  krok6(side);
  krok7(side);
  krok8(side);
}
void rotaceProtiSmeru(int side[]) {
  krok8(side);
  krok7(side);
  krok6(side);
  krok5(side);
  krok4(side);
  krok3(side);
  krok2(side);
  krok1(side);
}
// každý krok obsahuje výrobcem dané pořadí
// pro správné spínání motoru a následnou
// pauzu, kterou určujeme rychlost otáčení
void krok1(int side[]){
  digitalWrite(side[0], HIGH);
  digitalWrite(side[1], LOW);
  digitalWrite(side[2], LOW);
  digitalWrite(side[3], LOW);
  delay(rychlost);
}
void krok2(int side[]){
  digitalWrite(side[0], HIGH);
  digitalWrite(side[1], HIGH);
  digitalWrite(side[2], LOW);
  digitalWrite(side[3], LOW);
  delay(rychlost);
}
void krok3(int side[]){
  digitalWrite(side[0], LOW);
  digitalWrite(side[1], HIGH);
  digitalWrite(side[2], LOW);
  digitalWrite(side[3], LOW);
  delay(rychlost);
}
void krok4(int side[]){
  digitalWrite(side[0], LOW);
  digitalWrite(side[1], HIGH);
  digitalWrite(side[2], HIGH);
  digitalWrite(side[3], LOW);
  delay(rychlost);
}

void krok5(int side[]){
  digitalWrite(side[0], LOW);
  digitalWrite(side[1], LOW);
  digitalWrite(side[2], HIGH);
  digitalWrite(side[3], LOW);
  delay(rychlost);
}
void krok6(int side[]){
  digitalWrite(side[0], LOW);
  digitalWrite(side[1], LOW);
  digitalWrite(side[2], HIGH);
  digitalWrite(side[3], HIGH);
  delay(rychlost);
}
void krok7(int side[]){
  digitalWrite(side[0], LOW);
  digitalWrite(side[1], LOW);
  digitalWrite(side[2], LOW);
  digitalWrite(side[3], HIGH);
  delay(rychlost);
}
void krok8(int side[]){
  digitalWrite(side[0], HIGH);
  digitalWrite(side[1], LOW);
  digitalWrite(side[2], LOW);
  digitalWrite(side[3], HIGH);
  delay(rychlost);
}