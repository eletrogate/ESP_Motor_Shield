//inclusão de bibliotecas
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//definição de funções e pinos
#define BLYNK_PRINT Serial
#define RightMotorSpeed 5
#define RightMotorDir   0 
#define LeftMotorSpeed  4
#define LeftMotorDir    2

//variáveis referentes à conexão WiFi
char auth[] = "*********************";
char nome_rede[] = "*************";
char senha[] = "*********";

//variáveis de controle dos motores
int minRange = 300;
int maxRange = 900;
int minSpeed = 450;
int maxSpeed = 1020;
int noSpeed = 0;


void movimento(int x, int y){
//mover para frente
   if(y >= maxRange && x >= minRange && x <= maxRange){
    digitalWrite(RightMotorDir,HIGH); 
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

//mover para frente e para direita
  else if(x >= maxRange && y >= maxRange){
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

//mover para frente e para esquerda
  else if(x <= minRange && y >= maxRange){
    digitalWrite(RightMotorDir,HIGH);
    digitalWrite(LeftMotorDir,HIGH);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,minSpeed);
  }

  //zona neutra
  else if(y < maxRange && y > minRange && x < maxRange && x > minRange){
    analogWrite(RightMotorSpeed,noSpeed);
    analogWrite(LeftMotorSpeed,noSpeed);
  }

 //mover para trás
  else if(y <= minRange && x >= minRange && x <= maxRange){
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
   analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed);
  }

  //mover para trás e para direita
  else if(y <= minRange && x <= minRange){
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,minSpeed);
    analogWrite(LeftMotorSpeed,maxSpeed); 
  }

  //mover para trás e para esquerda
  else if(y <= minRange && x >= maxRange){
    digitalWrite(RightMotorDir,LOW);
    digitalWrite(LeftMotorDir,LOW);
    analogWrite(RightMotorSpeed,maxSpeed);
    analogWrite(LeftMotorSpeed,minSpeed);
  }
}

void setup(){
//iniciando a comunicação serial para verificação da conexão WiFi  
  Serial.begin(9600);
  Blynk.begin(auth, nome_rede, senha);
 
//setando os pinos referentes aos motores
  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
  pinMode(RightMotorDir, OUTPUT);
  pinMode(LeftMotorDir, OUTPUT);
  
//iniciando o carrinho com os motores desligados e sentido de rotação à frente
  digitalWrite(RightMotorSpeed, LOW);
  digitalWrite(LeftMotorSpeed, LOW);
  digitalWrite(RightMotorDir, HIGH);
  digitalWrite(LeftMotorDir,HIGH);
}

void loop(){
//comando para execução do código
   Blynk.run();
}

//inserção dos parâmetros informados pelo app
BLYNK_WRITE(V1){               //pino virtual selecionado no joystick
  int x = param[0].asInt();
  int y = param[1].asInt();
  movimento(x,y);
}