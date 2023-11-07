
float RAW_Voltage = 0;  // Representação análogica da tensão medida
float voltage[60];      // Valor da tensão medida
float z_in[60];         // Valor da impedância calculada
float D[60];            // Valor do duty cycle atual
float Pot;              // Valor da potência calculada
float voltageDiff = 0;  // Valor do ∆V
float z_inDiff = 0;     // Valor do ∆Z
float R_OUT = 12.5;     // Valor fixo da carga
float Pot_rate[60];     // Valor de ∆P/∆V calculado
long k;                 // Ponteiro dos vetores
float delta = 4;        // Passo de variacao do PWM
float pwm = 20;         // Valor de PWM inicial (50%)
                        // bool usePotRate = true;

float D_med = 0;
float D_sum = 0;