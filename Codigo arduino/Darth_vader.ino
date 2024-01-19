#if defined(__arm__)   // Familia Arduino
#elif defined(__AVR__) // Familia Arduino e outras placas AVR
#else
  #error A Placa selecionada nao e suportada, selecione placas da familia Arduino.
#endif
byte TP = 0b10101010; // Alterna os valores entre 0 e 1, para setar nas portas

ISR(TIMER1_COMPA_vect)
{
  // PORTC contem os bits das portas 0 a 7 analogicas ou as portas PC
  PORTC = TP; // Envie o valor de TP para as portas PORTC
  TP = ~TP; // Inverter TP para a proxima execucao
}

int ledPerma = 7;
int buzzer = 10;

//notas musicais
#define c 261
#define d 294
#define e 329
#define f 349
#define g 391
#define gS 415
#define a 440
#define aS 455
#define b 466
#define cH 523
#define cSH 554
#define dH 587
#define dSH 622
#define eH 659
#define fH 698
#define fSH 740
#define gH 784
#define gSH 830
#define aH 880

void setup() 	 
{ 	 
  pinMode(buzzer, OUTPUT); 	
  delay(8000);
  pinMode(ledPerma, OUTPUT);

  // Registrador DDRC (Data Direction Register) das portas PC (PC1,PC2,PC3..)
  DDRC = 0b11111111; // Define todas as portas PC (PC1,PC2,PC3..) analogicas como saida (OUTPUT)
  
  noInterrupts(); // Desabilita a interrupcao
  // Configuracao do TIMER1
  TCCR1A = 0; // Registrador TCCR1A configurado para o timer1
  TCCR1B = 0; // Registrador TCCR1B configurado para o timer1
  TCNT1 = 0; // Zera o contador TCNT1 de 16bits
  OCR1A = 200; // Define o registrador de comparacao OCR1A (16MHz / 200 = onda quadrada de 80kHz -> onda completa de 40kHz)
  
  TCCR1B |= (1 << WGM12); // Modo CTC (WGM12 bit para o modo de geracao de onda)
  TCCR1B |= (1 << CS10); // Define prescaler para 1 = sem prescaling (CS10 bit para o clock interno - prescaler)
  // TIMSK1 máscara do registrador de interrupção do temporizador/contador
  TIMSK1 |= (1 << OCIE1A); // Habilita a interrupcao por comparação pela igualdade (OCIE1A bit que ativar interrupção de comparação pela igualdade do temporizador/contador1)
  interrupts(); // Ativa interrupcao
} 	 
  	 
void loop()
{
  marcha(); //toca a marcha imperial no buzzer
} 	 

void beep (unsigned char buzzer, int frequencia, long tempomilisegundos)
{   
    int x; 	 
    long tamanhodelay = (long)(1000000/frequencia);
    long duracaoloop = (long)((tempomilisegundos*1000)/(tamanhodelay*2));
    for (x=0;x<duracaoloop;x++) 	 
    { 	
        digitalWrite(buzzer,HIGH);
        delayMicroseconds(tamanhodelay);
        digitalWrite(buzzer,LOW);
        delayMicroseconds(tamanhodelay);
    } 
    delay(50);
} 	 
  	 
void marcha()
{ 	 
    //500ms = 1/4 nota
    
    beep(buzzer, a, 500); 
    beep(buzzer, a, 500);     
    beep(buzzer, a, 500); 
    beep(buzzer, f, 350); 
    beep(buzzer, cH, 150);
    beep(buzzer, a, 500);
    beep(buzzer, f, 350);
    beep(buzzer, cH, 150);
    beep(buzzer, a, 1000);
    //primeira parte
    
    beep(buzzer, eH, 500);
    beep(buzzer, eH, 500);
    beep(buzzer, eH, 500);    
    beep(buzzer, fH, 350); 
    beep(buzzer, cH, 150);
    
    beep(buzzer, gS, 500);
    beep(buzzer, f, 350);
    beep(buzzer, cH, 150);
    beep(buzzer, a, 1000);
    //segunda parte
    
    beep(buzzer, aH, 500);
    beep(buzzer, a, 350); 
    beep(buzzer, a, 150);
    beep(buzzer, aH, 500);
    beep(buzzer, gSH, 250); 
    beep(buzzer, gH, 250);
    
    beep(buzzer, fSH, 125);
    beep(buzzer, fH, 125);    
    beep(buzzer, fSH, 250);
    delay(250);
    beep(buzzer, aS, 250);    
    beep(buzzer, dSH, 500);  
    beep(buzzer, dH, 250);  
    beep(buzzer, cSH, 250);  
    //cont
    
    beep(buzzer, cH, 125);  
    beep(buzzer, b, 125);  
    beep(buzzer, cH, 250);      
    delay(250);
    beep(buzzer, f, 125);  
    beep(buzzer, gS, 500);  
    beep(buzzer, f, 375);  
    beep(buzzer, a, 125); 
    
    beep(buzzer, cH, 500); 
    beep(buzzer, a, 375);  
    beep(buzzer, cH, 125); 
    beep(buzzer, eH, 1000); 
    //cont (?)
    
    beep(buzzer, aH, 500);
    beep(buzzer, a, 350); 
    beep(buzzer, a, 150);
    beep(buzzer, aH, 500);
    beep(buzzer, gSH, 250); 
    beep(buzzer, gH, 250);
    
    beep(buzzer, fSH, 125);
    beep(buzzer, fH, 125);    
    beep(buzzer, fSH, 250);
    delay(250);
    beep(buzzer, aS, 250);    
    beep(buzzer, dSH, 500);  
    beep(buzzer, dH, 250);  
    beep(buzzer, cSH, 250);  
    //.
    
    beep(buzzer, cH, 125);  
    beep(buzzer, b, 125);  
    beep(buzzer, cH, 250);      
    delay(250);
    beep(buzzer, f, 250);  
    beep(buzzer, gS, 500);  
    beep(buzzer, f, 375);  
    beep(buzzer, cH, 125); 
           
    beep(buzzer, a, 500);            
    beep(buzzer, f, 375);            
    beep(buzzer, c, 125);            
    beep(buzzer, a, 1000);       
  	delay(2000);
    //fim
}
