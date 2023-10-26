void setIO() {
  pinMode(3, OUTPUT);  // Define o pino 3 como saida PWM

  TCCR2A = bit(COM2A1) | bit(COM2B1) | bit(WGM21) | bit(WGM20);  // Define timer 2 principal
  TCCR2B = bit(WGM22) | bit(00000001);                           // Configura a divisao do prescaler do timer2 por 8;
  OCR2A = 40;                                                    // Ajusta da frequencia: Hz/8(prescaler)/40 = 50KHz
  OCR2B = 24;                                                    // Ajuste do duty para 60%, com valor 24

  // Atribuindo variáveis na posição 0:
  D[0] = 60;
  voltage[0] = 0;
  z_in[0] = 0;

// Avança o ponteiro
  k = 1;
}