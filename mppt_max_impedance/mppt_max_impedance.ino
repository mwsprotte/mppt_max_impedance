// SISTEMA DE CONTROLE PWM BASEADO NO MÉTODO DE IMPEDÂNCIA CARACTERÍSTICA

#include "variables.h"
#include "startup.h"
#include "mppt_ctrl.h"
#include "io_ctrl.h"

void setup() {
  Serial.begin(9600);       // Inciando a serial
  setIO();                  // Configura as leituras e os parâmetros iniciais 
} 
 
void loop() { 
  readSensors();            // Faz a leitura dos valores de tensão, impedância e potência 
  mppt();                   // Aplicando  o controle do duty cycle
  k++;                      // Somando no ponteiro das variáveis 
} 
