#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      30

// Neopixel lib
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, A1, NEO_GRB + NEO_KHZ800);

// internal var
struct Color {int r, g, b;};
Color toReach = {random(1,255),random(1,255),random(1,255)};
Color current = {0,0,0};
int pos = 0;

void setup(){
  Serial.begin(9600);
  
  // End of trinket special code
  pixels.setBrightness(50);
  pixels.begin();
  pixels.show(); // Initialize all pixels to 'off'
}

void loop(){
  pos++;
  if (pos == NUMPIXELS){
    pos = 0;
  }
  
  if(current.r == toReach.r &&current.g == toReach.g &&current.b == toReach.b){
    toReach = {random(1,255),random(1,255),random(1,255)};
  }
  
  //R
  if(current.r < toReach.r){
    current.r++;
  }
  if(current.r > toReach.r){
    current.r--;
  }
  
  //G
  if(current.g < toReach.g){
    current.g++;
  }
  if(current.g > toReach.g){
    current.g--;
  }
  
  //B
  if(current.b < toReach.b){
    current.b++;
  }
  
  if(current.b > toReach.b){
    current.b--;
  }
  
  Serial.print(current.r);
  Serial.print(";");
  Serial.print(current.g);
  Serial.print(";");
  Serial.println(current.b);
  
  pixels.setPixelColor(pos,pixels.Color(current.r, current.g, current.b));
  pixels.show();
}
