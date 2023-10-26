#include <math.h>
void readSensors() {
  RAW_Voltage = analogRead(A1);                                       // Leitua analógica da tensão 
  voltage[k] = (RAW_Voltage * 4 * 37.5 / 1023.0);                     // Converte o valor de tensao lido pelo arduino (0 a 37.5 V)
 
  z_in[k] = R_OUT / pow((pwm / 40) / (1 - pwm / 40), 2);              //Calcula a impedância baseado da leitura prévia 
  Pot = pow(voltage[k], 2) / z_in[k];                                 //Calcula a ptência baseado da leitura prévia
}