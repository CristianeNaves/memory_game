#include <QueueList.h>


int LED_RED = 12;
int LED_RED_USER = 3;
int LED_GREEN = 11;
int LED_GREEN_USER = 7;
int BUTTON = 10;
int BUTTON_RED = 2;
int BUTTON_GREEN = 4;
int contador = 1;
int LED;
bool sortLed = false;
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

void removerElementosRandom(){
  while(!listaRandom.isEmpty ()){
    Serial.print(listaRandom.pop());
    //listaRandom.pop();
    }
}
void removerElementosDigitada(){
  while(!listaDigitada.isEmpty ()){
    Serial.print(listaDigitada.pop());
  }
}

void loop() {
  while(!sortLed){ 
  if(digitalRead(BUTTON) == HIGH){
    Serial.print(contador);
    for(int i = 0; i < contador; i++){
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
    sortLed = true;
  }
  }
    for(int i = 0; i < contador; i++){
      while(!digitarLed){
        Serial.print("Digitar Led");
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
      sortLed = false;
      digitarLed = false;
    }
    contador++;  
    removerElementosRandom();
    removerElementosDigitada();
 
  
  
} 
