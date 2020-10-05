#include "FastLED.h"

#define NUM_LEDS 45
#define DATA_PIN 6
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

long int kodas;
int laikas=0;

int lemp=4;

int r=255;
int g=255;
int b=255;
int brightness= 255;
int mode=0;
int greitis=120;

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
  FastLED.show();
 
  pinMode(lemp, OUTPUT);
  
 
 
}


// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns


void loop() {
  kodas=0;
  while(digitalRead(2)==1){
    //**** daryti kol laukiama ***
if(mode==1){
  
      // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();  
  // insert a delay to keep the framerate modest
  FastLED.delay(1000/greitis); 

  // do some periodic updates
  EVERY_N_MILLISECONDS( 25 ) { gHue++; } // slowly cycle the "base color" through the rainbow
  //EVERY_N_SECONDS( 30 ) { nextPattern(); } // change patterns periodically

}
    
   //**** daryti kol laukiama**** 
  };
   while(digitalRead(2)==0);
    while(digitalRead(2)==1);
  
  for (int i=0;i<32;i++){
    laikas=0;
    while(digitalRead(2)==0);
    while(digitalRead(2)==1){
      laikas++;
      delayMicroseconds(100);
    }
    
    if (laikas>7)
      kodas+=1;
    else
      kodas+=0;
      
   if(i<32)
    kodas<<=1;
  }
  
    Serial.println(kodas);
  delay(100);
  //******************dekodavimas*******
    switch(kodas){
      case 33505470:{
        Serial.println("versus");
        brightness+=10;
        if (brightness>255){
          FastLED.setBrightness(0);
          FastLED.show();
          delay(50);
          brightness=255; 
        };
        FastLED.setBrightness(brightness);
        break;
      };
      case 33440190:{
        Serial.println("apati");
        brightness-=10;
        if(brightness<10) brightness=10;
        FastLED.setBrightness(brightness);
        break;
      };
      case 33472830:{
        Serial.println("off");
        FastLED.setBrightness(0);
        break;
      };
      case 33538110:{
        Serial.println("on");
        FastLED.setBrightness(brightness); 
        break;
      };
      case 33497310:{
        Serial.println("red");
        mode=0;
        r=255;
        g=0;
        b=0;
        break;
      };
      case 33432030:{
        Serial.println("green");
        mode=0;
        r=0;
        g=255;
        b=0;
        break;
      };
      case 33464670: {
        Serial.println("blue");
        mode=0;
        r=0;
        g=0;
        b=255;
        break;
      };
      case 33529950:{
        Serial.println("white");
        mode=0;
        r=255;
        g=255;
        b=255;
        break;
      };
      case 33513630:{
        Serial.println("r");
        mode=0;
        r=255;
        g=51;
         b=0; 
        break;
      };
      case 33448350:{
        Serial.println("g");
        mode=0;
        r=0;
        g=255;
        b=51;
        break;
      };
      case 33480990:{
        Serial.println("b");
        mode=0;
        r=51;
        g=0;
        b=255;
        break;
      };
      case 33546270:{
        Serial.println("flash");
        mode=1;
        greitis+=10;
        break;
      };
      case 33509550:{
        Serial.println("r");
        mode=0;
        r=255;
        g=153;
        b=0;
        break;
      };
      case 33444270:{
        Serial.println("g");
        mode=0;
        r=0;
        g=255;
        b=153;
        break;
      };
      case 33476910:{
        Serial.println("b");
        mode=0;
        r=153;
        g=0;
        b=255;
        break;
      };
      case 33542190:{
        Serial.println("strobe");
        mode=1;
        greitis-=10;
        break;
      };
      case 33501390:{
        Serial.println("r");
        mode=0;
        r=255;
        g=204;
        b=0;
        break;
      };
      case 33436110:{
        Serial.println("g");
        mode=0;
        r=0;
        g=255;
        b=204;
        break;
      };
      case 33468750:{
        Serial.println("b");
        mode=0;
        r=204;
        g=0;
        b=255;
        break;
      };
      case 33534030:{
        Serial.println("fade");
        digitalWrite(lemp,!digitalRead(lemp));
        break;
      };
      case 33493230:{
        Serial.println("r");
        mode=0;
        r=255;
        g=255;
        b=0;
        break;
      };
      case 33427950:{
        Serial.println("g");
        mode=0;
        r=0;
        g=255;
        b=255;
        break;
      };
      case 33460590:{
        Serial.println("b");
        mode=0;
        r=255;
        g=0;
        b=255;
        break;
      };
      case 33525870:{
        Serial.println("smooth");
        mode=1;
        nextPattern();
        break;
      };
      
      default: Serial.println(kodas);
    };
    //********* switch pabaiga *****
    
    if(mode==0){
      for(int i=0;i<NUM_LEDS;i++){
        leds[i]=CRGB(r,g,b);
      };
    };
     FastLED.show();
 
}







#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(13,0,NUM_LEDS);
  leds[pos] += CHSV( gHue, 255, 192);
}

void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}

void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16(i+7,0,NUM_LEDS)] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}



