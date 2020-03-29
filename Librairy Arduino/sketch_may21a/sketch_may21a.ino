

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



  if (!ts.begin()) {

    while (1);
  }

}



void loop()
{


       

       

  
  int xo, yo, r, total;

 


  total = 0; 

      tft.fillScreen(ILI9341_WHITE);    
    tft.setRotation(0); 
    
    xo = random(10,300);
    yo = random(10,300);
/*
      Serial.print("xo, yo = ");
      Serial.print("("); Serial.print(xo);
      Serial.print(", "); Serial.print(yo);
      Serial.println(")");
*/
    tft.setRotation(0);        
    tft.drawCircle(xo, yo, 5, ILI9341_RED);

      Serial.print("xo, yo = ");
      Serial.print("("); Serial.print(xo);
      Serial.print(", "); Serial.print(yo);
      Serial.println(")");



     TS_Point p = ts.getPoint();

        
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
      p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

      
      

      Serial.print("("); Serial.print(p.x);
      Serial.print(", "); Serial.print(p.y);
      Serial.println(")");

       

      int xo1, xo2, yo2, yo1;
      xo1 = xo - 20;
      xo2 = xo + 20;
      yo1 = yo - 20;
      yo2 = yo + 20;
      
      if (ts.touched()) {  
      if  ( xo1 < int(p.x) && int(p.x) < xo2 ) {
        if ( yo1 < int(p.y) && int(p.y) < yo2 ) {
          
          Serial.println("OUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII");
        
   
            }
          }
      }
      delay(1500);



    
}
    



  
     

