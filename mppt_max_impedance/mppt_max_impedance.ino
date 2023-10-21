/*SISTEMA DE CONTROLE PWM BASDEADO NO MÉTODO DE IMPEDÂNCIA CARACTERÍSTICA*/

float sensorValue1 = 0;                               // valor inicial do sensor de corrente
float sensorValue2 = 0;                               // valor inicial do sensor de tensao
float voltageValue = 0;                               // valor inicial do calculo da tensao
float currentValue = 0;                               // valor inicial do calculo da corrente
float Power_now = 0, Power_anc = 0, voltage_anc = 0;  // calculo de potencia
float delta = 1;                                      // passo de variacao do PWM
float pwm = 20;                                       // valor de PWM inicial

void setup() {
  Serial.begin(9600);  // inicia Serial
  pinMode(3, OUTPUT);  // define pino 3 como saida PWM

  // set up the 50 kHz output
  TCCR2A = bit(COM2A1) | bit(COM2B1) | bit(WGM21) | bit(WGM20);  // define timer 2 principal
  TCCR2B = bit(WGM22) | bit(00000001);                           // configura a divisao do prescaler do timer2 por 8;
  OCR2A = 40;                                                    // seta a frequencia: Hz/8(prescaler)/40 = 50KHz
  OCR2B = 24;                                                    // ajuste do duty para 60%, com valor 24
}

void loop() {
  sensorValue1 = analogRead(A0);                  // sensor de corrente
  currentValue = (sensorValue1 * 5.0 / 1023.0);   // valor de corrente lido pelo arduino (0 a 5 V)
  sensorValue2 = analogRead(A1);                  // sensor de tensao
  voltageValue = (sensorValue2 * 37.5 / 1023.0);  // valor de tensao lido pelo arduino (0 a 37.5 V)

  Serial.print("PWM = ");
  Serial.println(pwm);  // plota na serial o valor de PWM lido pelo arduino
  Serial.print("Tensao = ");
  Serial.println(voltageValue);  // plota na serial o valor de tensao  arduino
  Serial.print("Corrente = ");
  Serial.println(currentValue);  // plota na serial o valor de corrente arduino
  Serial.print("Potência = ");
  Serial.println(Power_now);  // plota na serial o valor de potencia arduino
  delay(500);

  Power_now = voltageValue * currentValue;

  if (Power_now > Power_anc) {
    if (voltageValue > voltage_anc)
      pwm = pwm - delta;
    else
      pwm = pwm + delta;
  } else {
    if (voltageValue > voltage_anc)
      pwm = pwm + delta;
    else
      pwm = pwm - delta;
  }
  Power_anc = Power_now;
  voltage_anc = voltageValue;
  if (pwm < 30)  // 11% de duty (valor minimo)
    pwm = 30;
  if (pwm > 30)  // 75% de duty (valor maximo)
    pwm = 30;
  OCR2B = pwm;
}
