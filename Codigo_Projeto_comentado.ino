#include <Ultrasonic.h>       //inclusao da biblioteca Ultrasonico
#include <Servo.h>           // inclusao da biblioteca Servo
#define echoPin 13           // define o pino digital 13 do arduino como echo do sensor ultrasonico
#define trigPin 12           // define o pino digital 12 do arduino como trig do sensor ultrasonico

Servo servo_objeto;             // cria um objeto (servo_objeto) que é do tipo Servo, esse objeto faz chamadas ao metodos attach(), write()
Ultrasonic ultrasonic(12, 13);  // cria um objeto construtor  (ultrasonic) do tipo Ultrasonico e passa os pinos como parametro

int posicao_inicial_servo = 0;  // seta a posição inicial do servo motor como = 0
int ledPin =  10;               // seta o pino digital 10 como corrente para o led
/*-----------------------------------------*/
void setup()
{
  Serial.begin(9600);        // inicia a porta serial com o baud rate padrão (9600)
  pinMode(echoPin, INPUT);   // seta o modo do pino 13 como Input (entrada) recebe dados
  pinMode(trigPin, OUTPUT);  // seta o modo do pino 12 como Output (saida) envia dados
  pinMode(ledPin, OUTPUT);   // seta o modo do pino 1o como output (saida) envia dados (luz)
  servo_objeto.attach(9);    // atraves do objeto servo_objeto faz a chamada do metodo attach e atriui o pino 9 como emissor de dados para o servo motor

}
/*-----------------------------------------*/
void loop()
{
  digitalWrite(ledPin, LOW);  // inicia o pino 10 (led) como desligado
  servo_objeto.write(posicao_inicial_servo); // seta a posiçao inicial do servo como = 0
  int valor = func_distancia_ultrasonico(); // armazena em valor o retorno da funcao func_distania_ultrasonico() esse valor é a distancia em cm
  if (valor <= 15)  // verifica se o valor retornado é menor ou igual a 15 cm, se for igual entra no IF() e chama a funcao func_controladora
  {
    func_controladora(); // funcao func_controladora() responsavel por fazer as chamadas das funcoes: func_liga_led() e func_chama_servo()
    delay(5000);         // delay (espera) de 5000 milisegundos esse é o tempo em q a porta fica aberta e o led acesso
  }

  delay(500);            // delay (espera) de 500 milisegundos para fazer novamente o laço loop()
}
/*----------------------------------------*/
void func_controladora() // funcao func_controladora() responsavel pela chamadas das funcoes abaixo
{
  func_liga_led();       // funcao para ligar o led
  func_chama_servo();   // funcao para acionar o servo motor
}
/*----------------------------------------*/
void func_liga_led()   // funcao para ligar o led
{
  digitalWrite(ledPin, HIGH); // seta o pino 10 como HIGH (ligado)
}
/*----------------------------------------*/
void func_chama_servo()    // funcao chama servo responsavel pelo acionamento do servo motor
{
  int posicao_final_servo = 90;  // define a posiçao final do eixo do servo motor (seta como 90 graus)
  servo_objeto.write(posicao_final_servo); //faz a escrita no pino 9 por onde passam os dados para o servo motor, nesse momento a porta se abre
}
/*----------------------------------------*/
int func_distancia_ultrasonico() // funcao responsavel por medir a distancia dos objetos e pessoas diante da porta
{
  digitalWrite(trigPin, LOW); // seta o pino 13 trig como desligado
  delayMicroseconds(2);  // delay de 2 microssegundos

  digitalWrite(trigPin, HIGH);// seta o pino 13 trig como ligado, nesse momento o arduino envia um pulso (energia) para o sensor
  delayMicroseconds(10);     // delay de 10 microssegundos

  digitalWrite(trigPin, LOW);  // seta o pino 13 trig como desligado
  int distancia = (ultrasonic.Ranging(CM)); // chama o metodo Ranging atraves do objeto ultrasonic passando CM como parametro
  Serial.print("Distancia em CM: "); // imprime a mensagem ("Distancia em CM:") na tela serial da ide do arduino
  Serial.println(distancia);  // imprime a distancia na tela serial da ide do arduino
  return distancia;          // faz um retorno da distancia
}
/*------------------------------------------*/
