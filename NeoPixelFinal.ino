#include <Adafruit_NeoPixel.h>

#define PIN 6
int i=0;
int pot=A0;
int commpin=5;
int pos=100;
int z=0;
int c=98;
int red_blinky = 10;
long previousmillis=0;
long middlepreviousmillis=0;
long cylonpreviousmillis=0;
int dir = 1;
int total=113;
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(113, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void setup() {
  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  pinMode(commpin,INPUT);

}

void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(strip.Color(255, 0, 0), 50); // Red
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  colorWipe(strip.Color(0, 0, 255), 50); // Blue
  // Send a theater pixel chase in...
  //theaterChase(strip.Color(127, 127, 127), 50); // White
  //theaterChase(strip.Color(127,   0,   0), 50); // Red
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue

//  rainbow(20);
//  rainbowCycle(20);
//  theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  int start2=35;
  int start3=62;
  int total=113;
  int numleft=35;
  int nummid=27;
  int numright=36;
  int offset=numright-numleft;
  int numcylon =15;
  int start4=97;
  int val;
 int signal = digitalRead(commpin);
 unsigned long currentmillis=millis();
 unsigned long middlemillis=millis();
 unsigned long cylonmillis=millis();
 
 
  int midinterval= 70;
  int runinterval=1;
  int cyloninterval=3;
  
    
  strip.setPixelColor(i, 100,0,0);
  strip.setPixelColor(start4-i,100,0,0);
  strip.show();

  if(currentmillis-previousmillis>runinterval){
    previousmillis=currentmillis;

   strip.setPixelColor(i,0);
   strip.setPixelColor(start4-i,0);
    i++;
  }
  
  if(i==start2){
      i=0;
  }
   //cylon
  //for(pos=0;pos<=15;pos++){
 //  strip.setPixelColor(pos+98,255,0,0);
 // strip.show(); 
  //}
     
int j;
    // Draw 5 pixels centered on pos. setPixelColor() will clip any
    // pixels off the ends of the strip, we don't need to watch for that.
    strip.setPixelColor(pos - 2, 75,0,0); // Dark red
    strip.setPixelColor(pos - 1, 100,0,0); // Medium red
    strip.setPixelColor(pos , 150,0,0); // Center pixel is brightest
    strip.setPixelColor(pos + 1, 100,0,0); // Medium red
    strip.setPixelColor(pos + 2, 75,0,0); // Dark red
     
	strip.show();
	
if(cylonmillis-cylonpreviousmillis>cyloninterval){
     cylonpreviousmillis=cylonmillis;
     	     
	    // Rather than being sneaky and erasing just the tail pixel,
	    // it's easier to erase it all and draw a new one next time.
	    for(j=-2; j<= 2; j++) 
	    {
	      strip.setPixelColor(pos+j, 0);
	    }
	    
	    pos += dir;
	    if(pos < 99) {
		    pos = 100;
		    dir = -dir;
		} 
		 else if(pos >= 113) {
		    pos = 111;
		    dir = -dir;
	    }
	 
}

//}

 // if(cylonmillis-cylonpreviousmillis>cyloninterval)
   // cylonpreviousmillis=cylonmillis;

   
//for the middle

   if(middlemillis-middlepreviousmillis>midinterval)
   {
     middlepreviousmillis=middlemillis;
         if(red_blinky == 0)
           {
              for(j=0;j<nummid;j++)
              {
               strip.setPixelColor(start2+j, 0, 0, 35);
               strip.show();
             }
             Serial.println("blink");
             red_blinky = 1;
           }//end if
           
         else
         {     
           Serial.println("noblink");
              for(j=0;j<nummid;j++)
              {
                 strip.setPixelColor(start2+j, 0);
                                strip.show();
              }
                  red_blinky = 0;
         }//end else
   }//end milliif
     

       
 if (signal == HIGH){  

   val=analogRead(pot);
   val=map(val,0,1023,0,255);
 
   for(i=0;i<=c;i++)
   {
     strip.setPixelColor(i,val,val,val);
     strip.show();
   }
 }

 } 


//void rainbow(uint8_t wait) {
  //uint16_t i, j;

// for(j=0; j<256; j++) {
  //  for(i=0; i<strip.numPixels(); i++) {
  //    strip.setPixelColor(i, Wheel((i+j) & 255));
  //  }
 //   strip.show();
 //   delay(wait);
  //}
//}

// Slightly different, this makes the rainbow equally distributed throughout
/*void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();
     
      delay(wait);
     
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        strip.show();
       
        delay(wait);
       
        for (int i=0; i < strip.numPixels(); i=i+3) {
          strip.setPixelColor(i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
*/
