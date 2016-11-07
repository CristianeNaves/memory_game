#include <QueueList.h>


int LED_RED = 12;
int LED_GREEN = 11;
int BUTTON = 10;
int count = 1;
int LED;
QueueList <int> listaRandom;
//QueueList <int> listaDigitada;

void setup() {
 Serial.begin(9600);
 pinMode(LED_RED, OUTPUT);
 pinMode(LED_GREEN, OUTPUT);
 pinMode(BUTTON, INPUT);
 randomSeed(analogRead(0));
}

void removerElementos(){
  while(!listaRandom.isEmpty ()){
    listaRandom.pop();
    }
}


void loop() {
  if(digitalRead(BUTTON) == HIGH){
    for(int i = 0; i < count; i++){
      LED = random(2);
      if(LED == 0){
        //listaRandom.push(LED_GREEN);
        digitalWrite(LED_GREEN, HIGH);
        delay(500);
        digitalWrite(LED_GREEN, LOW);
        delay(500);
      }
      else{
        //listaRandom.push(LED_RED);
        //Serial.print(listaRandom.peek());
        digitalWrite(LED_RED, HIGH);
        delay(500);
        digitalWrite(LED_RED, LOW);
        delay(500); 
      }
    }
    //fazer só até 10 depois voltar
    count++;
    //removerElementos();
  }
  else{
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, LOW);
  }
} 
