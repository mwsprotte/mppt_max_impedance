#include "HardwareSerial.h"
#include "WString.h"
#include <math.h>

void setDuty(float D) {
  pwm = 0.4 * D;
  OCR2B = pwm;
}

void mppt() {

  // Printando os valores lidos
  Serial.println("Tensão = " + (String)voltage[k - 1] + " V");
  Serial.println("Potência = " + (String)Pot + " W");

  voltageDiff = voltage[k] - voltage[k - 1];  //Calculando o ∆V

  z_inDiff = z_in[k] - z_in[k - 1];

  Serial.println("Delta V = " + (String)voltageDiff + " V");
  Serial.println("Zdif = " + (String)z_inDiff);
  Pot_rate[k] = (2 * voltage[k] / z_in[k]) - ((pow(voltage[k], 2) / pow(z_in[k], 2)) * (z_inDiff / voltageDiff));  //Calculando o ∆V/∆P
  // delay(1000);

  Serial.println("Resultado da eq. de rastreamento = " + (String)Pot_rate[k]);
  if (Pot_rate[k] > 0) {

    D[k] = D[k - 1] - delta;
  } else {
    D[k] = D[k - 1] + delta;
  }

  // Limitando no novo duty cycle os valores máximos e mínimos
  if (D[k] < 20) {
    D[k] = 20;
  } else if (D[k] > 70) {
    D[k] = 70;
  }

  // Apicando o novo duty cycle
  setDuty(D[k]);
  Serial.println("D = " + (String)D[k - 1]);

  // Resetando o ponteio dos vetores para evitar estouro de bytes
  if (k + 1 > 59) {
    D[0] = D[k];
    voltage[0] = voltage[k];
    z_in[0] = z_in[k];
    Pot_rate[0] = Pot_rate[k];

    // calculando os valores médios
    for (int i; i + 1 < k; i++) {
      D_sum = D_sum + D[k];
    }

    D_med = D_sum / k;

    Serial.println("************************************************************************************************");
    Serial.println("Duty médio = " + (String)D_med);
    Serial.println("************************************************************************************************");
    D_med = 0;
    D_sum = 0;

    k = 0;
  }
}