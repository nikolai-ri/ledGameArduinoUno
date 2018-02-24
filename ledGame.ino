#include <Adafruit_NeoPixel.h>

#define PIN 4

int delayMilli = 20;
int buttonLeftPin = 2;
int buttonRightPin = 12;
int kickbackPins = 10;
int delayTime = 5;
boolean gameOver = true;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

void setup() {

  pinMode(buttonLeftPin, INPUT_PULLUP);
  pinMode(buttonRightPin, INPUT_PULLUP);
  
  strip.begin();
  strip.show();
  
}

void loop() {

  gameOverFunc();

  delay(2000);

  if (digitalRead(buttonLeftPin) == LOW && 
      digitalRead(buttonRightPin) == LOW &&
      gameOver == true){

      gameOver = false;
      startGamePreambel();
      startGame();
    }
  
}

void startGame(){

  boolean goingRight = true;
  boolean gameRunning = true;
  boolean correctHit = false;
  int rounds = 0;
  delayTime = delayMilli;
  
  while(gameRunning){

        int32_t c;
        uint32_t c1;
 
        c = strip.Color(0, 255, 0);
        c1 = strip.Color(0,0,0);
        

      while(goingRight){
            
        for(uint16_t i=0; i <= strip.numPixels(); i++) {
          
          runBall(i,c,c1,delayTime);

          if (i < (strip.numPixels() - kickbackPins) && digitalRead(buttonRightPin) == LOW){gameOverFunc();}
          if (i >= (strip.numPixels() - kickbackPins) && i < strip.numPixels() && digitalRead(buttonRightPin) == LOW){ correctHit = true; }
          if (i == strip.numPixels() && !correctHit) {gameRunning = false; gameOverFunc();}
     
        }  

        if (!correctHit || gameOver) {break;}
        goingRight = false;
      }

      
      correctHit = false;
      
      if (gameOver) {gameRunning = false; break;}

      while(!goingRight){

          for(uint16_t i = strip.numPixels(); i > 0; i--) {
            
            runBall(i,c,c1, delayTime);

            if (i > kickbackPins && digitalRead(buttonLeftPin) == LOW){ gameOverFunc();}
            if (i <= kickbackPins && i > 0 && digitalRead(buttonLeftPin) == LOW){ correctHit = true; }
            if (i == 0 && !correctHit) {gameRunning = false;gameOverFunc();}
          }

          if(!correctHit || gameOver) {break;}

          goingRight = true;
      }

      correctHit = false;

      if (delayTime > 2) {
        delayTime -= 2;
      }
     
      rounds++;
      if (gameOver) {gameRunning = false; rounds = 0; delayTime = delayMilli; break;}
    
    }
}

void gameOverFunc(){

  gameOver = true;
  uint32_t c;
  uint32_t c1;
  
  for (int i = 0; i < 1; i++){

        c = strip.Color(255, 0, 0);
        c1 = strip.Color(0,0,0);
        
        for(uint16_t i=0; i <= strip.numPixels(); i++) {
          runBall(i,c,c1, 5);
        }  

        for(uint16_t i = strip.numPixels(); i > 0; i--) {
          runBall(i,c,c1, 5);
        }
  }
}

void startGamePreambel(){
  

  uint32_t c;
  uint32_t c1;
  
  for (int i = 0; i < 1; i++){

    c = strip.Color(0, 0, 255);
    c1 = strip.Color(0,0,0);
        
    for(uint16_t i=0; i <= strip.numPixels(); i++) {

        runBall(i,c,c1, 5);
          
     }  

    for(uint16_t i = strip.numPixels(); i > 0; i--) {

        runBall(i,c,c1, 5);
       
     }
   }
}

void runBall(int i, uint32_t c, uint32_t c1, int delayTime){

  strip.setPixelColor(i, c);
  delay(delayTime);
  strip.show();
  strip.setPixelColor(i,c1);
  delay(delayTime);
  strip.show(); 

}
