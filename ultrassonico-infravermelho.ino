#include <HCSR04.h>

//Definição dos pinos de controle do motor
#define M1 9 // Pino_Velocidade 1º Motor ( 0 a 255)_ Porta IN2 ponte H;
#define M2 11 //Pino_Velocidade 2º Motor ( 0 a 255) _ Porta IN4 ponte H;
#define dir1 8 //Pino_Direção do 1º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN1 ponte H;
#define dir2 10 //Pino_Direção do 2º Motor: Para frente / Para trás (HIGH ou LOW)_ porta IN3 ponte H;

//Define os pinos do Arduino D8 e D9 como porta do ECHO e TRIGGER
#define TRIGGER   4
#define ECHO      5
#define pin_S1 7
#define pin_S2 6
bool Sensor1 = 0;
bool Sensor2 = 0;

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

  //Setamos os pinos dos sensores como entrada
  pinMode(pin_S1, INPUT);
  pinMode(pin_S2, INPUT);

  //Inicializa a porta serial do Arduino com 9600 de baud rate
  Serial.begin(9600);

}

void loop() {

  Sensor1 = digitalRead(pin_S1);
  Sensor2 = digitalRead(pin_S2);

  //Variável recebe o valor da função da biblioteca
  distancia = distanceSensor.measureDistanceCm();

  erro = 5 - distancia;
  vel = 50 * erro;



  if (vel >= 0)
  {
    if ((Sensor1 == 0) && (Sensor2 == 0))
    { // Se detectar na extremidade das faixas duas cores brancas
      analogWrite(M1, vel); // Ambos motores ligam na mesma velocidade
      analogWrite(M2, vel);
      digitalWrite(dir1, LOW);//O motor gira para frente
      digitalWrite(dir2, LOW);
    }
    if ((Sensor1 == 1) && (Sensor2 == 0)) { // Se detectar um lado preto e o outro branco
      analogWrite(M1, 0); // O motor 1 desliga
      analogWrite(M2, vel);
      digitalWrite(dir1, LOW);//O motor gira para frente
      digitalWrite(dir2, LOW);
    }
    if ((Sensor1 == 0) && (Sensor2 == 1)) { // Se detectar um lado branco e o outro preto
      analogWrite(M1, vel); //O motor 1 fica ligado
      analogWrite(M2, 0); // O motor 2 desliga, fazendo assim o carrinho virar no outro sentido
      digitalWrite(dir1, LOW);//O motor gira para frente
      digitalWrite(dir2, LOW);
    }
  }


  else {
    if ((Sensor1 == 0) && (Sensor2 == 0))
    { // Se detectar na extremidade das faixas duas cores brancas
      analogWrite(M1, vel); // Ambos motores ligam na mesma velocidade
      analogWrite(M2, vel);
      digitalWrite(dir1, HIGH);//O motor gira para frente
      digitalWrite(dir2, HIGH);
    }
    if ((Sensor1 == 1) && (Sensor2 == 0)) { // Se detectar um lado preto e o outro branco
      analogWrite(M1, 0); // O motor 1 desliga
      analogWrite(M2, vel);
      digitalWrite(dir1, HIGH);//O motor gira para frente
      digitalWrite(dir2, HIGH);
    }
    if ((Sensor1 == 0) && (Sensor2 == 1)) { // Se detectar um lado branco e o outro preto
      analogWrite(M1, vel); //O motor 1 fica ligado
      analogWrite(M2, 0); // O motor 2 desliga, fazendo assim o carrinho virar no outro sentido
      digitalWrite(dir1, HIGH);//O motor gira para frente
      digitalWrite(dir2, HIGH);
    }
  }

  //exibe na porta serial o valor de distancia medido
  Serial.print(distancia);
  Serial.print(" ");
  Serial.print(vel);
  Serial.print(" ");
  Serial.print(erro);
  Serial.print(" ");
  Serial.print(Sensor1);
  Serial.print(" ");
  Serial.println(Sensor2);
  Serial.print(" ");

  
  delay(100);
}
