

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
  
    tft.setRotation(3); 
    tft.setCursor(coordx, coordy);
    tft.setTextColor(couleur);
    tft.setTextSize(taille);  
    tft.println(message);

}



void setup(void) {

 
  Serial.begin(115200);
  Serial.println(F("Touch Paint!"));
  
  tft.begin();



  if (!ts.begin()) {

    while (1);
  }

}



void loop()
{

      tft.fillScreen(ILI9341_WHITE);

      delay(200);

      ts.begin();

      int w, h;
     
      w = tft.width() - 10;
      h = tft.height();
      
      afficher(5,230,ILI9341_BLACK,1,"Projet RT");
     
      afficher(0,4,ILI9341_BLACK,2,"Score : ");
    
      afficher(90,4,ILI9341_BLACK,2,String(0));
    
      afficher(225,4,ILI9341_BLACK,2,"Vie : ");
    
      afficher(290,4,ILI9341_BLACK,2,String (5));
 
      afficher(50,40,ILI9341_BLACK,2,"Choix de la couleur : ");

      tft.setRotation(0);

      int xcarrehaut = 79, ycarrehaut = 65, x;
      int listcouleur[] = {ILI9341_BLACK, ILI9341_BLUE, ILI9341_YELLOW, ILI9341_GREEN, ILI9341_MAGENTA,ILI9341_CYAN};
            

     for (x = 0; x < 3; x++){
      
       tft.drawRect(xcarrehaut, ycarrehaut, 42, 42,ILI9341_BLACK );
       tft.fillRect(xcarrehaut + 1, ycarrehaut + 1, 40, 40, listcouleur[x]);
  
       ycarrehaut = ycarrehaut + 80;

     }

     int xcarrebas = 150; 
     int ycarrebas = 65; 

     for (x = 3; x < 6; x++){
      
       tft.drawRect(xcarrebas, ycarrebas, 42, 42,ILI9341_BLACK );
       tft.fillRect(xcarrebas + 1, ycarrebas + 1, 40, 40, listcouleur[x]);
  
       ycarrebas = ycarrebas + 80;

     }
     
      int u = 0;
      int couleurchoisit;
 
     do{

             
             TS_Point e = ts.getPoint();

         
             
             e.x = map(e.x, TS_MINX, TS_MAXX, 0, tft.width());
             e.y = map(e.y, TS_MINY, TS_MAXY, 0, tft.height());


   
      
            if (ts.touched()) {
      
              
               if  ( ( 150 <= int(e.x) && int(e.x) <= 192 ) && ( 210 <= int(e.y) && int(e.y) <= 252)) {
          
                  Serial.print("Cyan");
                  couleurchoisit = ILI9341_CYAN;
                  u = 1;
               }
          
               
               if  ( ( 150 <= int(e.x) && int(e.x) <= 192 ) && ( 130 <= int(e.y) && int(e.y) <= 172)) {
          
                  Serial.print("Magenta");
                  couleurchoisit = ILI9341_MAGENTA;
                  u = 1;
               }
          
               
               if  ( ( 150 <= int(e.x) && int(e.x) <= 192 ) && ( 50 <= int(e.y) && int(e.y) <= 92)) {
          
                  Serial.print("Green");
                  couleurchoisit = ILI9341_GREEN;
                  u = 1;
               }
          
               
               if  ( ( 79 <= int(e.x) && int(e.x) <= 121 ) && ( 210 <= int(e.y) && int(e.y) <= 252)) {
          
                  Serial.print("Yellow");
                  couleurchoisit = ILI9341_YELLOW;
                  u = 1;
               }
          
               
               if  ( ( 79 <= int(e.x) && int(e.x) <= 121 ) && ( 130 <= int(e.y) && int(e.y) <= 172)) {
          
                  Serial.print("Blue");
                  couleurchoisit = ILI9341_BLUE;
                  u = 1;
               }
          
               
               if  ( ( 79 <= int(e.x) && int(e.x) <= 121 ) && ( 50 <= int(e.y) && int(e.y) <= 92)) {
          
                  Serial.print("black");
                  couleurchoisit = ILI9341_BLACK;
                  u = 1;
               }
           
           
           }
      
           e.x = NULL;
           e.y = NULL;
         
      } while(u==0);
        
  
      afficher(50,40,ILI9341_WHITE,2,"Choix de la couleur : ");

      tft.setRotation(0);

      xcarrehaut = 79;
      ycarrehaut = 65;

     for (x = 0; x < 3; x++){
      
         tft.drawRect(xcarrehaut, ycarrehaut, 42, 42,ILI9341_WHITE );
         tft.fillRect(xcarrehaut + 1, ycarrehaut + 1, 40, 40,ILI9341_WHITE);
    
         ycarrehaut = ycarrehaut + 80;

     }

     xcarrebas = 150; 
     ycarrebas = 65; 

     for (x = 3; x < 6; x++){
      
         tft.drawRect(xcarrebas, ycarrebas, 42, 42,ILI9341_WHITE);
         tft.fillRect(xcarrebas + 1, ycarrebas + 1, 40, 40 ,ILI9341_WHITE);
    
         ycarrebas = ycarrebas + 80;

     }


  afficher(15,80,ILI9341_BLACK,4,"Touchez pour");

  afficher(90,120,ILI9341_BLACK,4,"jouer !");


  ts.begin();

  
  delay(200);
  int n = 0;
   
  do{
  if (ts.touched()) {

    n = 1;


    afficher(15,80,ILI9341_WHITE,4,"Touchez pour");

    afficher(90,120,ILI9341_WHITE,4,"jouer !");


    float tempsdebut, time; 
    
    time = millis();
    tempsdebut = time;
  
      
    int xo, yo, r;
    float total;
 
    tft.setRotation(0);  
  
    
    h = tft.height() - 30 ;
    w = tft.width() - 30 ;
    
    int score = 0;
    int vie = 5;

    afficher(90,4,ILI9341_WHITE,2,String(0));

    afficher(290,4,ILI9341_WHITE,2,String (5));
    
    afficher(90,4,ILI9341_BLACK,2,String(score));
    afficher(290,4,ILI9341_BLACK,2,String(vie));

    afficher(5,230,ILI9341_WHITE,1,"Projet RT");
  
  
    total = 0;
  
    int erreur;
    float touche = 0 ;
    
    for (int i = 0; i < 100; i++) {
                        
          total = total + 1;     
                 
          xo = random(45,w);
          yo = random(45,h);
       
          for (r = 0; r <= 30; r++) {
      
              tft.setRotation(0);                  
            
              if (r < 20){
                  tft.fillCircle(xo, yo, r, int(couleurchoisit));
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
        
              
              int xo1, xo2, yo2, yo1;
              xo1 = xo - 15;
              xo2 = xo + 15;
              yo1 = yo - 15;
              yo2 = yo + 15;
      
          
              erreur = 0;
              
              if (ts.touched()) {
                
                    touche = touche + 1;   
      
                    if  ( ( xo1 <= int(p.x) && int(p.x) <= xo2 ) && ( yo1 <= int(p.y) && int(p.y) <= yo2 )) {
                    
                        delay(20);
    
                               
                        erreur = 1 ;
                          
                        afficher(90,4,ILI9341_WHITE,2,String(score));
                        
                        score = score + 1;
              
                        afficher(90,4,ILI9341_BLACK,2,String(score));
                        
                        tft.setRotation(0);  
                        
                        tft.drawCircle(xo, yo, r, ILI9341_WHITE);
                        delay(40);
                       
                         break;
                    }
                     
                    
              }   
          }
      
         if (erreur == 0){
            
            afficher(290,4,ILI9341_WHITE,2,String(vie));
            
            vie = vie - 1;
          
            afficher(290,4,ILI9341_BLACK,2,String(vie));
      
         }
      
                    
        tft.setRotation(0); 
        tft.fillCircle(xo, yo, r, ILI9341_WHITE);
      
        if (vie == 0){
          goto resultat;
        }
                  
  
   
   }
   
   goto resultat;
  
  
   resultat : 

      
      afficher(5,230,ILI9341_BLACK,1,"Projet RT");
      afficher(50,45,ILI9341_BLACK,3,"Pourcentage : ");
      
      float pi, sec;
      
      pi = (score / total) * 100 ;
      
      afficher(90,85,ILI9341_BLACK,3,String(pi));  
      afficher(210,85,ILI9341_BLACK,3,"%");
      afficher(10,145,ILI9341_BLACK,3,"Nombre de saisie:");
    
      time = millis();
      sec = time;
  
      float nombretouche;
  
      nombretouche = touche /((sec-tempsdebut)/1000);
    
      afficher(55,193,ILI9341_BLACK,3,String(nombretouche));
      afficher(150,190,ILI9341_BLACK,3,"par sec");
  
      delay(1000);
     
      afficher(50,45,ILI9341_WHITE,3,"Pourcentage : ");
      afficher(90,85,ILI9341_WHITE,3,String(pi));
      afficher(210,85,ILI9341_WHITE,3,"%");  
      afficher(10,145,ILI9341_WHITE,3,"Nombre de saisie:");
      afficher(55,193,ILI9341_WHITE,3,String(nombretouche));
      afficher(150,190,ILI9341_WHITE,3,"par sec");
      
      afficher(32,80,ILI9341_BLACK,4,"Rejouer ? :");
      
      tft.drawRect(65, 145, 65, 45, ILI9341_BLACK);
        
      afficher(73,158,ILI9341_BLACK,3,"OUI");
      
      tft.drawRect(175, 145, 65, 45, ILI9341_BLACK);
      
      afficher(182,158,ILI9341_BLACK,3,"NON"); 
      
      u = 0;
      int sortir = 0;

   
      do{      

         ts.begin();
        
         delay(200);
      
         tft.setRotation(0);  
      
         if (!ts.touched()) { 

             TS_Point q = ts.getPoint();

         
             q.x = map(q.x, TS_MINX, TS_MAXX, 0, tft.width());
             q.y = map(q.y, TS_MINY, TS_MAXY, 0, tft.height());
    
             Serial.print("("); Serial.print(q.x);
             Serial.print(", "); Serial.print(q.y);
             Serial.println(")");
    
              if  ( ( 145 <= int(q.x) && int(q.x) <= 190 ) && (  165 <= int(q.y) && int(q.y) <= 230 )){
                  
                  Serial.println("Oui");
                  Serial.print("("); Serial.print(q.x);
                  Serial.print(", "); Serial.print(q.y);
                  Serial.println(")");
                  q.x = NULL;
                  q.y = NULL;
            
                  goto ecrantvide;
                 
             }
      
            if  ( ( 145 <= int(q.x) && int(q.x) <= 190) && (  65 <= int(q.y) && int(q.y) <= 130 )) {
            
                Serial.println("Non");
                Serial.print("("); Serial.print(q.x);
                Serial.print(", "); Serial.print(q.y);
                Serial.println(")");
                sortir = 1;
                q.x = NULL;
                q.y = NULL;
                goto ecrantvide;
             
            }
          
            else {
                
                Serial.println("OK");
                Serial.print("("); Serial.print(q.x);
                Serial.print(", "); Serial.print(q.y);
                Serial.println(")");
                q.x = NULL;
                q.y = NULL;
                   
           }
         
       }
    } while (u == 0);
    
  
    ecrantvide :
  
      afficher(32,80,ILI9341_WHITE,4,"Rejouer ? :");
    
      tft.drawRect(65, 145, 65, 45, ILI9341_WHITE);
        
      afficher(73,158,ILI9341_WHITE,3,"OUI");
      
      tft.drawRect(175, 145, 65, 45, ILI9341_WHITE);
      
      afficher(182,158,ILI9341_WHITE,3,"NON");

      afficher(90,4,ILI9341_WHITE,2,String(score));
      afficher(290,4,ILI9341_WHITE,2,String(vie));
      
      if (sortir == 1){
        afficher(90,4,ILI9341_BLACK,2,String(score));
        afficher(290,4,ILI9341_BLACK,2,String(vie));
        afficher(60,100,ILI9341_BLACK,4,"Tchao ;-)");
        exit(0);
      }

  }

  }while (n == 0);
  
  
}
