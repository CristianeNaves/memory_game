#include <QueueList.h>


int LED_RED = 12;
int LED_RED_USER = 3;
int LED_GREEN = 11;
int LED_GREEN_USER = 7;
int BUTTON = 10;
int BUTTON_RED = 2;
int BUTTON_GREEN = 4;
int fase_jogo = 1;
int LED;
bool mostrarLed = false;
bool digitarLed = false;
QueueList <int> listaRandom;
QueueList <int> listaDigitada;

void setup() {
 Serial.begin(9600);
 pinMode(LED_RED, OUTPUT);
 pinMode(LED_RED_USER, OUTPUT);
 pinMode(LED_GREEN_USER, OUTPUT);
 pinMode(LED_GREEN, OUTPUT);
 pinMode(BUTTON, INPUT);
 pinMode (BUTTON_RED, INPUT);
 pinMode (BUTTON_GREEN, INPUT);
 randomSeed(analogRead(0));
}

void mostrarSequencia(int fase){
  for(int i = 0; i < fase; i++){
    LED = random(2);
    if(LED == 0){
      listaRandom.push(LED_GREEN);
      digitalWrite(LED_GREEN, HIGH);
      delay(500);
      digitalWrite(LED_GREEN, LOW);
      delay(500);
    }
    else{
      listaRandom.push(LED_RED);
      digitalWrite(LED_RED, HIGH);
      delay(500);
      digitalWrite(LED_RED, LOW);
      delay(500); 
    }  
  }

}

void digitarSequencia(int fase){
  for(int i = 0; i < fase; i++){
    while(!digitarLed){
       if(digitalRead(BUTTON_RED) == HIGH){
          listaDigitada.push(LED_RED);
          digitalWrite(LED_RED_USER, HIGH);
          delay(500);
          digitalWrite(LED_RED_USER, LOW);
          digitarLed = true;
        }
        if(digitalRead(BUTTON_GREEN) == HIGH){
          listaDigitada.push(LED_GREEN);
          digitalWrite(LED_GREEN_USER, HIGH);
          delay(500);
          digitalWrite(LED_GREEN_USER, LOW);
          digitarLed = true;
        }
    }
    digitarLed = false;
  }   
}

int comparar(int fase){
  while(listaRandom.count() != 0){
    int ledListaRandom, ledListaDigitada;
    ledListaRandom = listaRandom.pop();
    ledListaDigitada = listaDigitada.pop();

    if(ledListaRandom != ledListaDigitada){
      //mostra led de game over
      return 1;
    }      
  }
  if (fase == 10){
    //Mostrar led de ganhar o jogo
    //Não apagar o led enquanto não clicar no botao principal
    return 1;  
  }
  else{
    //mostrar LED de proxima fase
    fase++;
    return fase; 
  }

}

void loop() {
  while(!mostrarLed){ 
    if(digitalRead(BUTTON) == HIGH){
      mostrarSequencia(fase_jogo);
      mostrarLed = true;
    }
  }
  digitarSequencia(fase_jogo);
  fase_jogo = comparar(fase_jogo);
  mostrarLed = false;
  
  
} 
