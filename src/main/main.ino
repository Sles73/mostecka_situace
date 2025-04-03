//část kódu převzata z https://navody.dratek.cz/navody-k-produktum/krokovy-motor-a-driver.html

#include <Servo.h>
#include <Adafruit_NeoPixel.h>

Servo myservo1;  
Servo myservo2;

#define LED_PIN    2
#define LED_COUNT 1

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

const int side1[] = {4,5,6,7};
const int side2[] = {8,9,10,11};
const int button[] = {A1,A3,A2};
const int lamps[] = {12,13};

int rychlost = 10;
byte state = 0;

const int valueSize=50;
int value_buffer[valueSize];
int max;

bool semafor_state = true;
bool gate_state = true;
bool lamp_state = false;

#define LIGHT_SENSOR A5

#define SEMAFOR_PIN 3

#define SERVO_2 A0
#define SERVO_1 A4

#define GATE_OPEN 75
#define GATE_CLOSE 150

#define red strip.Color(255,   0,   0)
#define green strip.Color(0,   255,   0)
#define blue strip.Color(0,   0,   255)
#define yellow strip.Color(255,   255,   0)
const uint32_t colors[] = {red,green,blue};

void setup() {
  for(int i = 0; i < 4; i++) pinMode(side1[i], OUTPUT);
  for(int i = 0; i < 4; i++) pinMode(side2[i], OUTPUT);
  for(int i = 0; i < 3; i++) pinMode(button[i],INPUT);
  for(int i = 0; i < 2; i++) pinMode(lamps[i],OUTPUT);

  Serial.begin(9600);

  pinMode(LIGHT_SENSOR,INPUT);
  
  pinMode(SEMAFOR_PIN,OUTPUT);
  digitalWrite(SEMAFOR_PIN,HIGH);

  myservo1.attach(SERVO_1);
  myservo2.attach(SERVO_2);  

  strip.begin();       
  strip.show();
  strip.setBrightness(25);

  myservo1.write(GATE_OPEN);  
  myservo2.write(GATE_OPEN); 

  digitalWrite(SEMAFOR_PIN,LOW); 
  
  setColor(red);
  delay(500);
  setColor(green);
  delay(500);
  setColor(blue);
  delay(500);
  strip.clear(); 
  strip.show();  

}

void loop() {
  if(digitalRead(button[2])){
    state = ++state%3;
    while(digitalRead(button[2]));
  }
  setColor(colors[state]);
 

  switch(state){
    case 0:
      if(digitalRead(button[0]) == HIGH){
        Serial.println("lower the bridge");
        rotaceProtiSmeru(side1);
        rotaceProtiSmeru(side2);
      }

      if(digitalRead(button[1]) == HIGH){
        Serial.println("raise the bridge");
        rotacePoSmeru(side1);
        rotacePoSmeru(side2);
      }
      break;

    case 1:
      if(digitalRead(button[0]) == HIGH){
        semafor_state = !semafor_state;
        Serial.print("Switched semafor state to ");
        Serial.println(semafor_state);
        while(digitalRead(button[0]));
      }

      if(digitalRead(button[1]) == HIGH){
        gate_state = !gate_state;
        Serial.print("Switched gate state to ");
        Serial.println(gate_state);
        while(digitalRead(button[1]));
      }
      break;

    case 2:
      if(digitalRead(button[0]) == HIGH){
        setColor(yellow);
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
      }

      if(digitalRead(button[1]) == HIGH){
        lamp_state = !lamp_state;
        Serial.print("Switched lamp state to ");
        Serial.println(lamp_state);
        while(digitalRead(button[1]));
      }
      break;

    default:
      state=0;
      break;
  }
  
  if(gate_state){
    Serial.println("gate opened");
    myservo1.write(GATE_OPEN);  
    myservo2.write(GATE_OPEN); 
  }else{
    Serial.println("gate closed");
    myservo1.write(GATE_CLOSE);  
    myservo2.write(GATE_CLOSE); 
  }

  Serial.print("semafor state ");
  Serial.println(semafor_state);
  digitalWrite(SEMAFOR_PIN,semafor_state);

//kód pro detekci lampy světly
/*
  if(lighRead() < 425){
    lamp_state=true;
  }else{
    lamp_state=false;
  }
  */
  turnLamps(lamp_state);
  
}

int lighRead(){
  max = 0;                                                                 
  for(int i=valueSize - 1; i>0; i--)
  {
    value_buffer[i] = value_buffer[i-1];            
    if(value_buffer[i]>max) max = value_buffer[i];
  }

  value_buffer[0] = analogRead(LIGHT_SENSOR);

  max = map(max,150,350,0,1024);

  return max;
}

void turnLamps(bool ligh){
  for(int i = 0; i < 2; i++) digitalWrite(lamps[i],ligh);
}

void setColor(uint32_t color){
  strip.setPixelColor(0, color);         
  strip.show();  
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