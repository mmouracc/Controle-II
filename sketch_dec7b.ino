#include <HCSR04.h>

//Definição dos pinos de controle do motor
#define M1 9     // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta IN2 ponte H;
#define M2 11    //Pino_Velocidade 2º Motor ( 0 a 255) _ Porta IN4 ponte H;
#define dir1 8   //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define dir2 10  //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;

//Define os pinos do Arduino D8 e D9 como porta do ECHO e TRIGGER
#define TRIGGER 4
#define ECHO 5

float tempo;

// Inicializa o sensor usando os pinos TRIGGER and ECHO.
UltraSonicDistanceSensor distanceSensor(TRIGGER, ECHO);

//variável responsável por controlar a velocidade dos motores
float vel = 0.0;
float distancia = 0.0;
float erro = 0.0;

void setup() {
  //Setamos os pinos de controle dos motores como saída
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(dir1, OUTPUT);
  pinMode(dir2, OUTPUT);

  //Setamos a direção inicial do motor como 0, isso fará com que ambos os motores girem para frente
  digitalWrite(dir1, LOW);
  digitalWrite(dir2, LOW);


  //Inicializa a porta serial do Arduino com 9600 de baud rate
  Serial.begin(9600);
}

void loop() {


  //Variável recebe o valor da função da biblioteca
  distancia = distanceSensor.measureDistanceCm();

  erro = 10 - distancia;
  vel = 50 * erro;
  if (vel > 255) { vel = 255; }
  if (vel < -255) { vel = -255; }

  if (vel >= 0) {
    
    analogWrite(M1, vel);  // Ambos motores ligam na mesma velocidade
    analogWrite(M2, vel);
    digitalWrite(dir1, LOW);  //O motor gira para frente
    digitalWrite(dir2, LOW);

  }


  else {

    analogWrite(M1, vel);  // Ambos motores ligam na mesma velocidade
    analogWrite(M2, vel);
    digitalWrite(dir1, HIGH);  //O motor gira para frente
    digitalWrite(dir2, HIGH);
  }

  //exibe na porta serial o valor de distancia medido
  tempo = tempo + 0.1;
  //Serial.print(tempo);
  Serial.print(distancia);
  Serial.print(" ");
  Serial.print(vel);
  Serial.print(" ");
  Serial.print(erro);
  Serial.println(" ");

  //Espera 1 segundo
  delay(100);
}