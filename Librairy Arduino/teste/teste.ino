

#include <Adafruit_GFX.h>    // Core graphics library
#include <SPI.h>
#include <Wire.h>      // this is needed even tho we aren't using it
#include <Adafruit_ILI9341.h>
#include <Adafruit_STMPE610.h>

// This is calibration data for the raw touch data to the screen coordinates
#define TS_MINX 150
#define TS_MINY 130
#define TS_MAXX 3800
#define TS_MAXY 4000

// The STMPE610 uses hardware SPI on the shield, and #8
#define STMPE_CS 8
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

// The display also uses hardware SPI, plus #9 & #10
#define TFT_CS 10
#define TFT_DC 9
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);


void afficher(int coordx, int coordy, int couleur, int taille, String message){
    
    tft.setCursor(coordx, coordy);
    tft.setTextColor(couleur);
    tft.setTextSize(taille);  
    tft.println(message);

}



void setup(void) {

 
  Serial.begin(9600);
  Serial.println(F("Touch Paint!"));
  
  tft.begin();

  tft.fillScreen(ILI9341_WHITE);

  int w, h;
 
  w = tft.width() - 10;
  h = tft.height();

  tft.setRotation(3);
  
  afficher(5,w,ILI9341_BLACK,1,"Projet RT");
 
  w = tft.width() - 30;
  h = tft.height() - 30;
  


  afficher(0,4,ILI9341_BLACK,2,"Score : ");

  afficher(90,4,ILI9341_BLACK,2,String(0));
  

  if (!ts.begin()) {

    while (1);
  }

}



void loop()
{


  afficher(15,80,ILI9341_BLACK,4,"Touchez pour");

  afficher(90,120,ILI9341_BLACK,4,"jouer !");
  
  if (ts.bufferEmpty()) {
    return;
  }
       

  tft.fillScreen(ILI9341_WHITE);
     
  int w, h;

  w = tft.width() - 10;
  h = tft.height();
  

  
  afficher(5,w,ILI9341_BLACK,1,"Projet RT");
  
  int xo, yo, r, total;

  tft.setRotation(0);  

  h = tft.height() - 30;
  w = tft.width() - 30 - 20;

//  h est y et w est x
  
  tft.setRotation(3); 
  afficher(0,4,ILI9341_BLACK,2,"Score : ");

  int score = 0;

  afficher(90,4,ILI9341_BLACK,2,String(score));
  

  total = 0; 
  
  for (int i = 80; i < 100; i++) {
                  
    total = total + 1;

    
    tft.setRotation(3); 
    
    xo = random(30,w);
    yo = random(30,h);
     
    for (r = 0; r < 30; r++) {

      tft.setRotation(0);                  
      
      if (r < 20){
        tft.fillCircle(xo, yo, r, ILI9341_GREEN);
      }
      else {
        tft.fillCircle(xo, yo, r, ILI9341_RED);
      }
    
      delay(30);
                                
      TS_Point p = ts.getPoint();
        
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

      Serial.print("("); Serial.print(p.x);
      Serial.print(", "); Serial.print(p.y);
      Serial.println(")");
    
              
      if  ((p.x - xo - r <= p.x <= p.x - xo + r) && (p.y - yo - r <= p.y <=  p.y - yo + r) ){

          delay(30);
          Serial.println("OUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");

          tft.setRotation(3);      
          afficher(90,4,ILI9341_WHITE,2,String(score));
          
          score = score + 1;

          afficher(90,4,ILI9341_BLACK,2,String(score));
          
          tft.setRotation(0);  
          
          tft.drawCircle(xo, yo, r, ILI9341_WHITE);
          delay(50);
         
           break;
        }
    
      tft.setRotation(0);               
      tft.drawCircle(xo, yo, r, ILI9341_WHITE);
  
    
   }
    delay(10);
       
   
    tft.setRotation(0); 
    tft.fillCircle(xo, yo, r, ILI9341_WHITE);
  
  }

  tft.setRotation(3);  

  afficher(50,45,ILI9341_BLACK,3,"Pourcentage : ");


  float pi, sec,time;
  
  pi = (score / total) * 100 ;
  
  afficher(90,85,ILI9341_BLACK,3,String(pi));

  afficher(210,85,ILI9341_BLACK,3,"%");

  afficher(10,145,ILI9341_BLACK,3,"Nombre de saisie:");

  time = millis();
  sec = time/1000;
  

  afficher(40,195,ILI9341_BLACK,3,String(sec));

  afficher(160,190,ILI9341_BLACK,3,"par sec");
  

  exit(0);
  
     
}
