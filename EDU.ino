
/*
*Programa teste do Shield Edu-IFSP
*
*GERSE – Grupo de Estudos em Robótica e Sistemas Embarcados
*http://www.gerserobotica.com
*gerse.robot@gmail.com
*IFSP – Campus Guarulhos
*
*Desenvolvedor:
*Pedro Igor Borçatti
*
*março de 2017
*/


#include <LiquidCrystal.h>    // BIBLIOTECA PARA DISPLAY LCD

#define    A        13        // LCD 7 SEGMENTO A OU LED A
#define    B        12        // LCD 7 SEGMENTO B OU LED B, DISPLAY 16X2 D7
#define    C        11        // LCD 7 SEGMENTO C OU LED C, DISPLAY 16X2 D6
#define    D        5         // LCD 7 SEGMENTO D OU LED D, DISPLAY 16X2 D5
#define    E        4         // LCD 7 SEGMENTO E OU LED E, DISPLAY 16X2 D4
#define    F        3         // LCD 7 SEGMENTO F OU LED F, DISPLAY 16X2 E
#define    G        2         // LCD 7 SEGMENTO G OU LED G, DISPLAY 16X2 RS

#define    POT      A1        // ADC1, POTENCIÔMETRO

#define    BUZZER   6         // BUZZER OU BORNE (PWM6)

#define    ADC2     A2        // BORNE
#define    ADC3     A3        // BORNE
#define    ADC4     A4        // BORNE
#define    ADC5     A5        // BORNE
#define    MOTOR1   9         // BORNE (BC548 - VCC BATERIA E COLETOR)
#define    MOTOR2   10        // BORNE (BC548 - VCC BATERIA E COLETOR)

#define    BT1      A0        // BOTÃO COM TRAVA
#define    BT2      7         // BOTÃO 1
#define    BT3      8         // BOTÃO 2


float         CALC  = 0;      // VARIÁVEL PARA CALCULO
byte          NUM   = 0;      // VARIÁVEL PARA PWM

boolean       bt1   = false;  // VARIÁVEL DO BOTÃO 1
boolean       bt2   = false;  // VARIÁVEL DO BOTÃO 2
boolean       bt3   = false;  // VARIÁVEL DO BOTÃO 3

boolean       cls   = false;  // FLAG PARA CONTROLE DO DISPLAY LCD 16X2

const boolean LCD7[10][7] =   // NÚMEROS DE 0 A 9 PARA LCD DE 7 SEGMENTOS 
              {
             // {A,B,C,D,E,F,G}
                {1,1,1,1,1,1,0},    // 0
                {0,1,1,0,0,0,0},    // 1
                {1,1,0,1,1,0,1},    // 2
                {1,1,1,1,0,0,1},    // 3
                {0,1,1,0,0,1,1},    // 4
                {1,0,1,1,0,1,1},    // 5
                {1,0,1,1,1,1,1},    // 6
                {1,1,1,0,0,0,0},    // 7
                {1,1,1,1,1,1,1},    // 8
                {1,1,1,1,0,1,1},    // 9
             // {A,B,C,D,E,F,G}
              };

//INICIANDO DISPLAY LCD
LiquidCrystal lcd(2, 3, 4, 5, 11, 12);

void setup() 
{   
    lcd.begin(16, 2);               // CONFIGURANDO TAMANHO DO DISPLAY 16X2
    
    pinMode(A,      OUTPUT);        // CONFIGURANDO COMO SAÍDA O PINO 13
    pinMode(B,      OUTPUT);        // CONFIGURANDO COMO SAÍDA O PINO 12
    pinMode(C,      OUTPUT);        // CONFIGURANDO COMO SAÍDA O PINO 11
    pinMode(D,      OUTPUT);        // CONFIGURANDO COMO SAÍDA O PINO 5
    pinMode(E,      OUTPUT);        // CONFIGURANDO COMO SAÍDA O PINO 4
    pinMode(F,      OUTPUT);        // CONFIGURANDO COMO SAÍDA O PINO 3
    pinMode(G,      OUTPUT);        // CONFIGURANDO COMO SAÍDA O PINO 2
    pinMode(BUZZER, OUTPUT);        // CONFIGURANDO COMO SAÍDA O PINO 6
    pinMode(MOTOR1, OUTPUT);        // CONFIGURANDO COMO SAÍDA O PINO 9
    pinMode(MOTOR2, OUTPUT);        // CONFIGURANDO COMO SAÍDA O PINO 10

    pinMode(BT1,    INPUT_PULLUP);  // CONFIGURANDO COMO ENTRADA O PINO A0 EM PLLU UP
    pinMode(BT2,    INPUT_PULLUP);  // CONFIGURANDO COMO ENTRADA O PINO 7  EM PLLU UP
    pinMode(BT3,    INPUT_PULLUP);  // CONFIGURANDO COMO ENTRADA O PINO 8  EM PLLU UP
    pinMode(POT,    INPUT);         // CONFIGURANDO COMO ENTRADA O PINO A1
    //pinMode(ADC2, );              // PINO DISPONÍVEL NO BORNE
    //pinMode(ADC3, );              // PINO DISPONÍVEL NO BORNE
    //pinMode(ADC4, );              // PINO DISPONÍVEL NO BORNE
    //pinMode(ADC5, );              // PINO DISPONÍVEL NO BORNE
    
}

void loop() 
{
    
    bt1 = !digitalRead(BT1);  // AQUISITANDO VALOR DO BOTÃO 1
    bt2 = !digitalRead(BT2);  // AQUISITANDO VALOR DO BOTÃO 2
    bt3 = !digitalRead(BT3);  // AQUISITANDO VALOR DO BOTÃO 3
    
    CALC = analogRead(POT);   // AQUISITANDO VALOR DO POTENCIÔMETRO

    if(bt1)                   // SE BOTÃO 1 APERTADO 
    {
      if(cls)                 // CONTROLE DO DISPLAY LCD 16X2
      {
          lcd.clear();        // LIMPAR DISPLAY 16X2
          delay(20);
          
          cls = false;        // FLAG DE CONTROLE P. DISPLAY 16X2 
      }
      
      NUM = (CALC/1023)*9;    // 0 -> 0   1023 -> 9
      digitalWrite(A,  LCD7[NUM][0]);   
      digitalWrite(B,  LCD7[NUM][1]);
      digitalWrite(C,  LCD7[NUM][2]);
      digitalWrite(D,  LCD7[NUM][3]);
      digitalWrite(E,  LCD7[NUM][4]);
      digitalWrite(F,  LCD7[NUM][5]);
      digitalWrite(G,  LCD7[NUM][6]);
    }
    else          // SE BOTÃO 1 NÃO APERTADO
    {
      
      if(!cls)    // CONTROLE DO DISPLAY LCD 16X2
      {
          digitalWrite(A,  LOW);
          digitalWrite(B,  LOW);
          digitalWrite(C,  LOW);
          digitalWrite(D,  LOW);
          digitalWrite(E,  LOW);
          digitalWrite(F,  LOW);
          digitalWrite(G,  LOW);
          
          lcd.clear();    
          delay(10);
          lcd.print("<     GERSE    >");  // ESCREVER EM DISPLAY 16X2
          delay(10);

          cls = true;
      }

      if(bt3)                             // SE BOTÃO 3 PRESSIONADO
      {                                   
        NUM = (CALC/1023)*255;            // 0 -> 0   1023 -> 255
        analogWrite(MOTOR1, NUM);         // SETAR VALOR DO PWM NO MOTOR1
        analogWrite(MOTOR2, NUM);         // SETAR VALOR DO PWM NO MOTOR2

        lcd.setCursor(0, 1);              // POSICIONAR CURSOR NA COLUNA 0, LINHA 1
        lcd.print("   ");
        lcd.setCursor(0, 1);
        lcd.print(NUM);                   // ESCREVER VALOR DE NUM NO DISPLAY 16X2
      }   
    }

 
    if(bt2)                               // SE BOTAO2 PRESSIONADO
    {
      NUM = (CALC/1023)*255;
      analogWrite(BUZZER, NUM);           // SETAR VALOR DO PWM NO BUZZER
    }

    delay(100);                           // ESPERAR 100ms
}
