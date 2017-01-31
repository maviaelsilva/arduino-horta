/**
 * Projeto para irrigaçao automática a cada 3 horas quando estiver na luz do dia
 */

const int ldrPin   =  A0;// LDR pin
const int ledPinRele1 =  8;// RELE1 pin
const int ledPinRele2 =  9;// RELE2 pin

int envLightState = LOW; // estado para led e rele
int ldrValor = 0;
int currentPowerOnCount = 0;
int currentPowerOffCount = 0;

const long interval = 1; // intervalo de coleta em segundos
const int intervalPowerOnRele = 60 * 10; // intervalo power on rele
const int intervalPowerOffRele = 60 * 60 * 3; // intervalo power off rele


void setup() {
  pinMode(ledPinRele1, OUTPUT);
  pinMode(ledPinRele2, OUTPUT);
  //digitalWrite(ledPinRele1, LOW);
  //digitalWrite(ledPinRele2, LOW);
  Serial.begin(9600); //Inicia a comunicação serial
}

void loop() {
  ///ler o valor do LDR
  ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  if (ldrValor>= 900)
    envLightState = HIGH;
  else
    envLightState = LOW;    // senão, apaga o led e relé

  Serial.print("luz envLightState: ");
  Serial.print(envLightState);
  Serial.println();
  if(currentPowerOnCount >= intervalPowerOnRele){
    Serial.println("ligado");
    //se o valor lido for maior que 500, liga o led e o rele

    //aciona os dois reles
    digitalWrite(ledPinRele1, envLightState);
    digitalWrite(ledPinRele2, envLightState);
    //delay(intervalPowerOnRele * 1000);
    if(currentPowerOffCount >= intervalPowerOffRele)
      currentPowerOnCount = 0;
    currentPowerOffCount++; 
  }else{
    Serial.print("Desligado, currentPowerOnCount: ");
    Serial.print(currentPowerOnCount);
    Serial.print(", intervalPowerOnRele: ");
    Serial.print(intervalPowerOnRele);
    Serial.println();
     //aciona os dois reles
    digitalWrite(ledPinRele1, HIGH);
    digitalWrite(ledPinRele2, HIGH);
    currentPowerOffCount = 0;
    currentPowerOnCount++;
  }
  
  //imprime o valor lido do LDR no monitor serial
  Serial.println(ldrValor);
  
  //aguarda alguns segundos
  delay(interval * 1000);
}
