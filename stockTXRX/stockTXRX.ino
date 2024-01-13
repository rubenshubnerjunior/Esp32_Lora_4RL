/*

   Softaware escrito por Rubens Hubner Junior em 11/09/2022
   Usado para acionar reles atraves do Radio Lora com o Esp32

   Pinos usados:
   RX2 --> 16
   TX2 --> 17
   CTS --> 08
   RTS --> 07

   bt1 --> 34
   bt2 --> 35
   bt3 --> 36
   bt4 --> 39

   r1  -->  4
   r2  -->  5
   r3  --> 18
   r4  --> 23

   Aux --> 15
   M1  --> 19
   M0  --> 21

*/


#include<HardwareSerial.h>

#define RXD2 16
#define TXD2 17


char rl1 = 'a'; // Mensagem enviada/recebida para ligar o rele  1
char rl2 = 'b'; // Mensagem enviada/recebida para ligar o rele  1
char rl3 = 'c'; // Mensagem enviada/recebida para ligar o rele  1
char rl4 = 'd'; // Mensagem enviada/recebida para ligar o rele  1

char recebida = 'a'; // Mensagem recebida pelo Radio Lora

int r1 = 4; // pino para acionar rele
int r2 = 5; // pino para acionar rele
int r3 = 18; // pino para acionar rele
int r4 = 23; // pino para acionar rele

int bt1 = 34;
int bt2 = 35;
int bt3 = 36;
int bt4 = 39;

long tempoRele =    0; // Para usar funcao de rele Pulsado
long tempoTeste =    0; // Para usar funcao de auto teste

bool teste = false; // Inicia sem a funcao teste habilitada
int  testeCount = 1; // Teste feitos de 1 a 4 ( 04 Reles)
int tempoBotao = 0; // Tempo em que o botao fica apertado


HardwareSerial lora(2);

//===========Funcao para efetuar testes sem precisar apertar os botoes=====================
void autoTeste()
{
  if (teste == false) return; // Funcao autoTeste nao habilitada
  
  if (testeCount == 1)
  {
    lora.write(rl1); // Liga rele 1 Remoto
    digitalWrite(r2, LOW);  // Liga Desliga Rele Local
    digitalWrite(r3, LOW);  // Liga Desliga Rele Local
    digitalWrite(r4, LOW);  // Liga Desliga Rele Local
    digitalWrite(r1, HIGH); // Liga Desliga Rele Local
  }
  if (testeCount == 2)
  {
    lora.write(rl2); // Liga rele 2 Remoto

    digitalWrite(r3, LOW); // Liga Desliga Rele Local
    digitalWrite(r4, LOW); // Liga Desliga Rele Local
    digitalWrite(r1, LOW); // Liga Desliga Rele Local
    digitalWrite(r2, HIGH); // Liga Desliga Rele Local

  }
  if (testeCount == 3)
  {
    lora.write(rl3); // Liga rele 3 Remoto

    digitalWrite(r4, LOW); // Liga Desliga Rele Local
    digitalWrite(r1, LOW); // Liga Desliga Rele Local
    digitalWrite(r2, LOW); // Liga Desliga Rele Local
    digitalWrite(r3, HIGH); // Liga Desliga Rele Local

  }
  if (testeCount == 4)
  {
    lora.write(rl4); // Liga rele 4 Remoto

    digitalWrite(r1, LOW); // Liga Desliga Rele Local
    digitalWrite(r2, LOW); // Liga Desliga Rele Local
    digitalWrite(r3, LOW); // Liga Desliga Rele Local
    digitalWrite(r4, HIGH); // Liga Desliga Rele Local

  }

  testeCount = testeCount + 1; // Testa proximo rele
  if (testeCount > 4) testeCount = 1;
  Serial.println(testeCount);

}
//=====================================================
void setup()
{

  Serial.begin(115200);
  lora.begin(9600, SERIAL_8N1, RXD2, TXD2);

  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);

  pinMode(bt1, INPUT);
  pinMode(bt2, INPUT);
  pinMode(bt3, INPUT);
  pinMode(bt4, INPUT);

  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, LOW);
  digitalWrite(r4, LOW);

  teste = false;
  testeCount = 1;
  tempoBotao = 0;


}

//============================loop()================================
void loop() {

  long now = millis();


  if (lora.available()) // Tem mensagem na porta Serial
  {

    recebida = (char)lora.read();
    Serial.println(recebida);


    if ( recebida == rl1)
    {
      Serial.print(rl1);
      Serial.println(": Ligando Rele 1");
      digitalWrite(r2, LOW);  // Liga Desliga Rele Local
      digitalWrite(r3, LOW);  // Liga Desliga Rele Local
      digitalWrite(r4, LOW);  // Liga Desliga Rele Local
      digitalWrite(r1, HIGH); // Liga Desliga Rele Local
      tempoRele = now;
    }
    if ( recebida == rl2)
    {
      Serial.print(rl2);
      Serial.println(": Ligando Rele 2");
      digitalWrite(r3, LOW); // Liga Desliga Rele Local
      digitalWrite(r4, LOW); // Liga Desliga Rele Local
      digitalWrite(r1, LOW); // Liga Desliga Rele Local
      digitalWrite(r2, HIGH); // Liga Desliga Rele Local
      tempoRele = now;
    }

    if ( recebida == rl3)
    {
      Serial.print(rl3);
      Serial.println(": Ligando Rele 3");
      digitalWrite(r4, LOW); // Liga Desliga Rele Local
      digitalWrite(r1, LOW); // Liga Desliga Rele Local
      digitalWrite(r2, LOW); // Liga Desliga Rele Local
      digitalWrite(r3, HIGH); // Liga Desliga Rele Local
      tempoRele = now;

    }

    if ( recebida == rl4)
    {
      Serial.print(rl4);
      Serial.println(": Ligando Rele 4");
      digitalWrite(r1, LOW); // Liga Desliga Rele Local
      digitalWrite(r2, LOW); // Liga Desliga Rele Local
      digitalWrite(r3, LOW); // Liga Desliga Rele Local
      digitalWrite(r4, HIGH); // Liga Desliga Rele Local
      tempoRele = now;
    }

  } // final lora.available() Mensagem recebida


  if (digitalRead(bt1) == LOW) // Apetado o botao 1
  {
    tempoBotao = 0;
    while (digitalRead(bt1) == LOW ) // Bounce
    {
      tempoBotao = tempoBotao + 1;
      Serial.println(tempoBotao);
      delay(50);
    }
    if (tempoBotao > 50)
    {
      teste = true;
      Serial.print("Teste:");
      Serial.println(teste);
    }
    else
    {
      teste = false;
      Serial.print("Teste:");
      Serial.println(teste);
    }

    Serial.println("Botao 1");

    lora.write(rl1); // Liga rele 1 Remoto

    digitalWrite(r2, LOW);  // Liga Desliga Rele Local
    digitalWrite(r3, LOW);  // Liga Desliga Rele Local
    digitalWrite(r4, LOW);  // Liga Desliga Rele Local
    digitalWrite(r1, HIGH); // Liga Desliga Rele Local
    tempoRele = now;

  }

  if (digitalRead(bt2) == LOW) // Apetado o botao 2
  {
    tempoBotao = 0;
    teste = false;
    while (digitalRead(bt2) == LOW) // Bounce
    {
      Serial.print(".");
      delay(50);
    }
    Serial.println("Botao 2");

    lora.write(rl2); // Liga rele 2 Remoto

    digitalWrite(r3, LOW); // Liga Desliga Rele Local
    digitalWrite(r4, LOW); // Liga Desliga Rele Local
    digitalWrite(r1, LOW); // Liga Desliga Rele Local
    digitalWrite(r2, HIGH); // Liga Desliga Rele Local
    tempoRele = now;
  }
  if (digitalRead(bt3) == LOW) // Apetado o botao 3
  {
    tempoBotao = 0;
    teste = false;
    while (digitalRead(bt3) == LOW) // Bounce
    {
      Serial.print(".");
      delay(50);
    }
    Serial.println("Botao 3");

    lora.write(rl3); // Liga rele 3 Remoto

    digitalWrite(r4, LOW); // Liga Desliga Rele Local
    digitalWrite(r1, LOW); // Liga Desliga Rele Local
    digitalWrite(r2, LOW); // Liga Desliga Rele Local
    digitalWrite(r3, HIGH); // Liga Desliga Rele Local
    tempoRele = now;
  }
  if (digitalRead(bt4) == LOW)// Apetado o botao 4
  {
    tempoBotao = 0;
    teste = false;
    while (digitalRead(bt4) == LOW) // Bounce
    {
      Serial.print(".");
      delay(50);
    }
    Serial.println("Botao 4");

    lora.write(rl4); // Liga rele 4 Remoto

    digitalWrite(r1, LOW); // Liga Desliga Rele Local
    digitalWrite(r2, LOW); // Liga Desliga Rele Local
    digitalWrite(r3, LOW); // Liga Desliga Rele Local
    digitalWrite(r4, HIGH); // Liga Desliga Rele Local
    tempoRele = now;
  }

  if (now - tempoTeste > 2000) // Chama a funcao teste a cada 2 segundos
  {
    autoTeste();
    tempoTeste = now;
  }

  if (now - tempoRele > 2000) // Se querer usar o rele pulsado descomente as linhas
  {
    //digitalWrite(r1, LOW);
    //digitalWrite(r2, LOW);
    //digitalWrite(r3, LOW);
    //digitalWrite(r4, LOW);
  }






} // Fim do loop()
