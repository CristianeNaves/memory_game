#include <QueueList.h>

const int rgbVermelho = 9;
const int rgbVerde = 8;
const int rgbAzul = 6;
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
 pinMode(rgbVermelho, OUTPUT);
 pinMode(rgbVerde, OUTPUT);
 pinMode(rgbAzul, OUTPUT);
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
      piscarLed(255,0,0);
      delay(5000);
      apagarLed();
      while(listaRandom.count() != 0)
        listaRandom.pop();
      while(listaDigitada.count() != 0)
        listaDigitada.pop();  
      return 1;
    }      
  }
  if (fase == 10){
    piscarLed(255,255,0);
    delay(5000);
    apagarLed();
    return 1;  
  }
  else{
    fase++;
    piscarLed(0,255,0);
    delay(500);
    apagarLed();
    return fase; 
  }

}
void piscarLed(int r, int g, int b){
  digitalWrite(rgbVermelho, r);
  digitalWrite(rgbVerde, g);
  digitalWrite(rgbAzul, b);
}

void apagarLed(){
  digitalWrite(rgbVermelho, LOW);
  digitalWrite(rgbVerde, LOW);
  digitalWrite(rgbAzul, LOW);
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
