#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELSBAND      65
#define NUMPIXELSLOOP      60
#define N_SEGMENT_LOOP     3
#define SENS_ROTATION      -1 // from -1 to 1
#define V_CHGT_COULEUR     0.05 // from 0 to 1

// Neopixel lib
Adafruit_NeoPixel pixelsBand = Adafruit_NeoPixel(NUMPIXELSBAND, A0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsLoop = Adafruit_NeoPixel(NUMPIXELSLOOP, A1, NEO_GRB + NEO_KHZ800);

// internal var
struct Color {int r, g, b;};
Color toReach = {random(1,254),random(1,254),random(1,254)};
Color current = {0,0,0};
int pos = 0;
int tmp = 0;
double ampli = 0;

void setup(){
  Serial.begin(9600);
  
  // End of trinket special code
  pixelsBand.setBrightness(10);
  pixelsBand.begin();
  for(int i = 0; i< NUMPIXELSBAND; i++){
    pixelsBand.setPixelColor(i,pixelsBand.Color(255, 255, 255));
  }
  pixelsBand.show();
  pixelsLoop.setBrightness(50);
  pixelsLoop.begin();
  pixelsLoop.show();
}

void loop(){
  pos++;
  if(pos>=NUMPIXELSLOOP){
    pos=0;
  }
  
  if(current.r == toReach.r &&current.g == toReach.g &&current.b == toReach.b){
    toReach = {tmp==6||tmp>=0&&tmp<=2?255:0,tmp>=2&&tmp<=4?255:0,tmp>=4&&tmp<=6?255:0};
    tmp ++;
    if(tmp>=6){
      tmp=0;
    }
  }
  
  //R
  if(current.r < toReach.r){
    current.r+=1+abs(toReach.r-current.r)*V_CHGT_COULEUR;
  }
  if(current.r > toReach.r){
    current.r-=1+abs(toReach.r-current.r)*V_CHGT_COULEUR;
  }
  
  //G
  if(current.g < toReach.g){
    current.g+=1+abs(toReach.g-current.g)*V_CHGT_COULEUR;
  }
  if(current.g > toReach.g){
    current.g-=1+abs(toReach.g-current.g)*V_CHGT_COULEUR;
  }
  
  //B
  if(current.b < toReach.b){
    current.b+=1+abs(toReach.b-current.b)*V_CHGT_COULEUR;
  }
  
  if(current.b > toReach.b){
    current.b-=1+abs(toReach.b-current.b)*V_CHGT_COULEUR;
  }
  
  for(int i = 0; i<NUMPIXELSLOOP; i++){
    ampli = 1/(1+exp(-(3*cos((double)(pos+SENS_ROTATION*i)/NUMPIXELSLOOP*N_SEGMENT_LOOP*2*PI))));
    pixelsLoop.setPixelColor(i,pixelsBand.Color(ampli*current.r, ampli*current.g, ampli*current.b));
  }
    
  pixelsLoop.show();
}
