#include "WString.h"
#include <math.h>

void setDuty(float D) {
  pwm = 0.4 * D;
}

void mppt() {

  // Printando os valores lidos
  Serial.println("PWM = " + (String)pwm);
  Serial.println("Tensão = " + (String)voltage[k]);
  Serial.println("Potência = " + (String)Pot);
  delay(500);

  voltageDiff = voltage[k - 1] - voltage[k];                                                                                    //Calculando o ∆V
  z_inDiff = z_in[k - 1] - z_in[k];                                                                                             //Calculando o ∆Z
  Pot_rate = (2 * voltage[k] / z_in[k]) - (pow(voltage[k], 2) / (pow(z_in[k], 2) * (z_inDiff / voltageDiff)));                  //Calculando o ∆V/∆P 

  // Alterando o duty cycle beaseado nas leituras
  if (Pot_rate > 0) {
    D[k] = D[k - 1] - delta;
  } else {
    D[k] = D[k - 1] + delta;
  }

  // Limitando no novo duty cycle os valores máximos e mínimos
  if (D[k] < 11) {
    D[k] = 11;
  } else if (D[k] > 30) {
    D[k] = 30;
  }

  // Apicando o novo duty cycle
  setDuty(D[k]);

  // Resetando o ponteio dos vetores para evitar estouro de bytes
  if (k > 100) {
    D[0] = D[k];
    voltage[0] = voltage[k];
    z_in[0] = z_in[k];
    k = 0;
  }
}