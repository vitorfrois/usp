#define PINO_RX 0 // Pinagem padrão de RX
#define PINO_TX 1 // Pinagem padrão de Tx
#define RTS 2 
#define CTS 3
#define BAUD_RATE 9600 // Velocidade de taxa de transmissão padrão
#define HALF_BAUD (1000/(2*BAUD_RATE)) // Usada para garantir a sincronia na transmissão

#include "Temporizador.h"

int bitsTransmitidos = 0;
char caractere;


// Calcula bit de paridade - Par ou ímpar
bool bitParidade(char dado) {
  int numBitsSet = 0; // Variável para contar o número de bits setados para 1
  
  for (int i = 0; i < 8; i++) {
    if (bitRead(dado, i) == 1) {
      numBitsSet++;
    }
  }
  
  // Verifica se o número de bits setados é par ou ímpar
  if (numBitsSet % 2 == 0) {
    return true; // Paridade par (retorna true)
  } else {
    return false; // Paridade ímpar (retorna false)
  }
}

// Rotina de interrupcao do timer1
// O que fazer toda vez que 1s passou?
ISR(TIMER1_COMPA_vect){
  if(digitalRead(CTS) == HIGH){
    if(bitsTransmitidos == 8){
      digitalWrite(PINO_TX, bitParidade(caractere)); // Envia o bit de paridade
    }else{
      digitalWrite(PINO_TX, bitRead(caractere, bitsTransmitidos));
      bitsTransmitidos += 1;
    }  
  }
}

// Executada uma vez quando o Arduino reseta
void setup(){
  //desabilita interrupcoes
  noInterrupts();

  // Configura porta serial (Serial Monitor - Ctrl + Shift + M)
  Serial.begin(BAUD_RATE);

  // Inicializa pinos
  pinMode(PINO_TX, OUTPUT);
  pinMode(RTS, OUTPUT);
  pinMode(CTS, INPUT);

  configuraTemporizador(BAUD_RATE);

  // habilita interrupcoes
  interrupts();
}

void loop() {
  // seta o rts 
  digitalWrite(RTS, HIGH);  
  while(digitalRead(CTS) == LOW)
    Serial.println('Esperando resposta.');
  iniciaTemporizador();

  caractere = Serial.read(); // Lê o caractere da porta serial
  
  while(bitsTransmitidos != 8)
    Serial.print('.');

  bitsTransmitidos = 0;

  digitalWrite(RTS, LOW);
  paraTemporizador();
}
