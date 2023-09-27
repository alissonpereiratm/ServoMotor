#include "Servo.h"

Servo meuservo1;
Servo meuservo2;
int angulo1 = 0; 
int angulo2 = 0; 
int incremento = 5; 

void setup() {
  meuservo1.attach(9); 
  meuservo2.attach(10); 
}

void loop() {
  while (angulo1 <= 90) {
    meuservo2.write(angulo2);
    meuservo1.write(angulo1);
    delay(500); 
    angulo1 += incremento;
      }
  if (angulo1 >= 90) {
    meuservo2.write(angulo2);
     delay(500); 
    angulo2 += incremento; 
    angulo1 = 0;
     }
}