/**
 * Projeto para irrigaçao automática a cada 3 horas quando estiver na luz do dia
 */

const int ldrPin   =  A0;// LDR pin
const int ledPinRele1 =  8;// RELE1 pin
const int ledPinRele2 =  9;// RELE2 pin

int state = LOW; // estado para led e rele
int ldrValor = 0;

const long interval = 1000; // intervalo de coleta


void setup() {
  pinMode(ledPinRele1, OUTPUT);
  pinMode(ledPinRele2, OUTPUT);
  Serial.begin(9600); //Inicia a comunicação serial
}

void loop() {
  ///ler o valor do LDR
  ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  
  //se o valor lido for maior que 500, liga o led e o rele
  if (ldrValor>= 900) state = HIGH;
  // senão, apaga o led e relé
  else state = LOW;
  
  //aciona os dois reles
  digitalWrite(ledPinRele1, state);
  digitalWrite(ledPinRele2, state);
  
  //imprime o valor lido do LDR no monitor serial
  Serial.println(ldrValor);
  
  //aguarda alguns segundos
  delay(interval);
}

