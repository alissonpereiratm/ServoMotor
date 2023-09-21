#include "Servo.h"

Servo meuservo;
int angulo = 0; 
int incremento = 10; 

void setup() {
  meuservo.attach(9); 
}

void loop() {
  while (angulo <= 360) {
    meuservo.write(angulo);
    delay(1500); 
    angulo += incremento; 
  }

  delay(2000); 
}