#include <Adafruit_NeoPixel.h>

#define MIC A0 // Microphone is connected at analog pin A0
#define LED_PIN 6 // WS2812b LED's DataIn pin is connected to arduino's Digital pin D6
#define N_PIXELS 300 // Number of LED in Addressable LED strip
#define N 200 // Number of samples 
#define fadeDelay 1 // fade delay amount
#define noiseLevel 2 // Amount of noice we want to ignore/chop off

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

int samples[N]; // variable to storage of a sample 
int periodFactor = 0; // For period calculation
int t1 = -1; 
int T;  
int slope; 
byte periodChanged = 0;

/*------------------------------------------------
 setup initialize serial monitor baud rate and
 begin neopixel library
-----------------------------------------------*/

void setup() {
  Serial.begin(9600);
  strip.begin(); // This initializes the NeoPixel library.
  ledsOff(); // call function ledoff to turn all LED off at the begning
  delay(500); // Delay of half second
  displayColor(Wheel(100)); 
  strip.show(); // To push color data to the strip
  delay(500); // Delay of half second
}

//----------------------continous loop------------------------------
void loop() 
{
  Samples(); // to call sample function
}

//------------------------ Sample function---------------------------------

void Samples()      
{
  for(int i=0; i<N; i++) 
  {
    samples[i] = analogRead(0);   // read analog input from analog pin A0 and take a N samples
    if(i>0) 
    {
      slope = samples[i] - samples[i-1];   // Find slope of N samples
      //Serial.println(abs(slope));
    }
    else 
    {
      slope = samples[i] - samples[N-1];
    }
    
    if(abs(slope) > noiseLevel) // Check if abs(slop) is greater than noiseLevel(noise Level which we want to ignore) 
    { 
      if(slope < 0)  
      { 
        calculatePeriod(i);
        if(periodChanged == 1) 
        {
          displayColor(getColor(T));
        }
      }
    }
    else 
    {
      ledsOff();
    }
    periodFactor += 1;
    delay(1);
  }
}
//----------------------------period calculation----------------
void calculatePeriod(int i) {
  if(t1 == -1) 
  {
    t1 = i;
  }
  else 
  {
    int period = periodFactor*(i - t1);
    periodChanged = T==period ? 0 : 1;
    T = period;
    //Serial.println(T);
   
    t1 = i;
    periodFactor = 0;
  }
}
//-----------------------------
uint32_t getColor(int period) 
{
  if(period == -1)
    return Wheel(0);  //pass wheel pos to 0
  else if(period > 400)
    return Wheel(5);  // pass wheel pos to 5
  else
    return Wheel(map(-1*period, -400, -1, 50, 255));
}
//------------------fade out effect--------------------------
void fadeOut()
{
  for(int i=0; i<5; i++) 
  {
    strip.setBrightness(110 - i*20);  // reduce brightness in for loop
    strip.show(); // Update strip by pushing color data to the strip
    delay(fadeDelay);  // fade delay
    periodFactor +=fadeDelay;
  }
}
//-------------------fade in effect------------------------
void fadeIn() 
{
  strip.setBrightness(100); // set brightess 
  strip.show();  // Update strip by pushing color data to the strip
  for(int i=0; i<5; i++) 
  {
    //strip.setBrightness(20*i + 30);  // turn comment off if you want fade in
    strip.show(); // Update strip by pushing color data to the strip
    delay(fadeDelay);  // fade delay
    periodFactor+=fadeDelay;
  }
}
// ------------blank when no sound detects--------------------
void ledsOff() 
{
  fadeOut();  // fade out before turn off all LEDs to give smooth effect of turning off lights
  for(int i=0; i<N_PIXELS; i++) 
  {
    strip.setPixelColor(i, 0, 0, 0);  // to save power Trun off all LED even if the brightness is 0 by the fadeout function
  }
}
//------------------------- set pixel color------------------------------
void displayColor(uint32_t color) 
{
  for(int i=0; i<N_PIXELS; i++) 
  {
    strip.setPixelColor(i, color);  // color is 32bit type that merges the red, green, bule values into a single number
  }
  fadeIn(); // fade in effect apply
}

//---------------------adafruits wheel() function---------------------
//Input WheelpPos value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
//--------------------------------------------------------
uint32_t Wheel(byte WheelPos) {
  // Serial.println(WheelPos);
  if(WheelPos < 85)
  {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3,0); // set strip color based on wheel pos value
  } 
  else if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3 ); // set strip color based on wheel pos value
  } 
  else
  {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3); // set strip color based on wheel pos value
  }
}

/*
--------------------------------Improved wheel function------------------------
// Adopted from https://votecharlie.com/blog/2018/08/improved-color-wheel-function.html
// Input values 0 to 255 to get color values that transition R->G->B. 0 and 255
// are the same color. This is based on Adafruit's Wheel() function, which used
// a linear map that resulted in brightness peaks at 0, 85 and 170. This version
// uses a quadratic map to make values approach 255 faster while leaving full
// red or green or blue untouched. For example, Wheel(42) is halfway between
// red and green. The linear function yielded (126, 129, 0), but this one yields
// (219, 221, 0). This function is based on the equation the circle centered at
// (255,0) with radius 255:  (x-255)^2 + (y-0)^2 = r^2
unsigned long Wheel(byte position) {
  byte R = 0, G = 0, B = 0;
  if (position < 85) {
    R = sqrt32((1530 - 9 * position) * position);
    G = sqrt32(65025 - 9 * position * position);
  } else if (position < 170) {
    position -= 85;
    R = sqrt32(65025 - 9 * position * position);
    B = sqrt32((1530 - 9 * position) * position);
  } else {
    position -= 170;
    G = sqrt32((1530 - 9 * position) * position);
    B = sqrt32(65025 - 9 * position * position);
  }
  return strip.Color(R, G, B);
}

// Adapted from https://www.stm32duino.com/viewtopic.php?t=56#p8160
unsigned int sqrt32(unsigned long n) {
  unsigned int c = 0x8000;
  unsigned int g = 0x8000;
  while(true) {
    if(g*g > n) {
      g ^= c;
    }
    c >>= 1;
    if(c == 0) {
      return g;
    }
    g |= c;
  }
}

*/
