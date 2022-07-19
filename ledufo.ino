#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
#define indoorOffset 0
#define indoorLength 10
#define frontOffset  10
#define frontLength  16
#define innerRingOffset 26
#define innerRingLength 50
#define outerRingOffset 76
#define outerRingLength 68
#define PIXELS 128

//  The overall fire brightness
//  (this can affect both color levels and power consumption)
int brightness = 32;

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.
// For the ultimate NeoPixel guide, check out:
// https://learn.adafruit.com/adafruit-neopixel-uberguide/overview

uint16_t x=0;
long firstPixelHue = 0;
void setup() {
  strip.begin();
  strip.setBrightness(brightness);
  //strip.show(); // Initialize all pixels to 'off'
}


//nl73ingb0004622114

void rainbow(int offset,int length) {
  // Hue of first pixel runs 5 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
  // means we'll make 5*65536/256 = 1280 passes through this outer loop:
    for(int i=offset; i<offset+length; i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / length);
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
   
}


void loop() {
  
 
  x++;
  if (firstPixelHue > 5*65536) { firstPixelHue=0;}
  firstPixelHue += 256;

  for (int r=indoorOffset; r<indoorOffset+indoorLength; r++)
  {
   
    if (millis()/1000%5==0)
    {
     strip.setPixelColor(r,255,255,0);
    }
    
     if (millis()/1000%5==1)
    {
     strip.setPixelColor(r,255,255,255);
    }

     if (millis()/1000%5==2)
    {
     strip.setPixelColor(r,0,0,0);
    }

     if (millis()/1000%5==3)
    {
     strip.setPixelColor(r,0,0,255);
    }
   
  }
  
  for (int r=frontOffset; r<frontOffset+frontLength; r++)
  {
   
    
    strip.setPixelColor(r,0,0,0);
   
    if ((x/10+r)%32==0  ) {
            strip.setPixelColor(r,255,random(255),0);
            strip.setPixelColor(random(16),0,0,255);
             strip.setPixelColor(random(16),255,255,0);
            
          
          }
          else
          { 
            strip.setPixelColor(r,random(16),random(15),0);
            
          }
    
   
  }

 rainbow(innerRingOffset,innerRingLength);
  for (int r=innerRingOffset; r<innerRingOffset+innerRingLength; r++)
  {
    if (r+x%5==1)
    {
    
    strip.setPixelColor(r,0,0,cos((x-r)/10)*128+128);
    }
    if ((x+r)%50==0  ) {
            //strip.setPixelColor(r,255,0,0);
          }
           if ((x+r+x+x)%50==0  ) {
            strip.setPixelColor(r,0,128,0);
          }

          if ((r+x)%50==0  ) {
            strip.setPixelColor(r,255,255,0);
          }


          if ((r+x+x)%50==0  ) {
            strip.setPixelColor(r,0,128,128);
          }
  }

   rainbow(outerRingOffset,outerRingLength);
  for (int r=outerRingOffset; r<outerRingOffset+outerRingLength; r++)
  {
    //strip.setPixelColor(r,0,0,32);
   
          
          if ((r+x)%50==48  ) {
            strip.setPixelColor(r,255,255,255);
          }


         
  }
 strip.show();
}
