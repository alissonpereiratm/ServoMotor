#include <Stepper.h>
#include "Servo.h"
#include "Ultrasonic.h"  //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO DO CÓDIGO
#include <String.h>
#include <Stdlib.h>
#include <Stdio.h>

const int echoPin = 2;  //PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 3;  //PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)

Ultrasonic ultrasonic(trigPin, echoPin);  //INICIALIZANDO OS PINOS DO ARDUINO

int distancia;  //VARIÁVEL DO TIPO INTEIRO
String result;  //VARIÁVEL DO TIPO STRING
Servo meuservo1;
Servo meuservo2;
int angulo1 = 0;
int angulo2 = 0;
int incremento = 1;

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
// for your motor

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {

  pinMode(echoPin, INPUT);   //DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT);  //DEFINE O PINO COMO SAIDA (ENVIA)
  Serial.begin(9600);        //INICIALIZA A PORTA SERIAL

Serial.print(hcsr04());  // FAZ A CHAMADA DO MÉTODO "hcsr04()"

  meuservo1.attach(6);
  // meuservo2.attach();
  // set the speed at 60 rpm:
  myStepper.setSpeed(1);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  
  

  for (int x = 0; x <= stepsPerRevolution; x++) {
    myStepper.step(1);
    for (int y = 0; y <= 90; y += incremento) {
      meuservo1.write(y);
      //hcsr04();  // FAZ A CHAMADA DO MÉTODO "hcsr04()"

  String formattedString = formatString("%d; %d; %d", x, y, hcsr04());
  Serial.println(formattedString);

  //Serial.println(x);
  //Serial.print("; ");
  //Serial.print(y);
  //Serial.print("; ");
      //Serial.print(hcsr04());  ////IMPRIME NO MONITOR SERIAL A DISTÂNCIA MEDIDA
    delay(50);
    }
  }
}

String formatString(const char* format, ...) {
  static char buffer[256]; // Tamanho máximo da string formatada
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  return String(buffer);
}
//MÉTODO RESPONSÁVEL POR CALCULAR A DISTÂNCIA
int hcsr04() {
  digitalWrite(trigPin, LOW);   //SETA O PINO 6 COM UM PULSO BAIXO "LOW"
  delayMicroseconds(2);         //INTERVALO DE 2 MICROSSEGUNDOS
  digitalWrite(trigPin, HIGH);  //SETA O PINO 6 COM PULSO ALTO "HIGH"
  delayMicroseconds(10);        //INTERVALO DE 10 MICROSSEGUNDOS
  digitalWrite(trigPin, LOW);   //SETA O PINO 6 COM PULSO BAIXO "LOW" NOVAMENTE
  //FUNÇÃO RANGING, FAZ A CONVERSÃO DO TEMPO DE
  //RESPOSTA DO ECHO EM CENTIMETROS, E ARMAZENA
  //NA VARIAVEL "distancia"
  distancia = (ultrasonic.read(CM));  //VARIÁVEL GLOBAL RECEBE O VALOR DA DISTÂNCIA MEDIDA
  return distancia;         //VARIÁVEL GLOBAL DO TIPO STRING RECEBE A DISTÂNCIA(CONVERTIDO DE INTEIRO PARA STRING)
}
