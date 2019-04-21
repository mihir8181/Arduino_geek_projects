# Sound Active WS2812b (Addressable) LED

<p align="center"><img src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/Sound%20Active%20WS2812b%20LED/Result.gif" width="400" hight="100"/></p>

This DIY project is to make sound active WS2812b addressable LED.
For that we get signals from microphone sound detector sensor, process detector's analog output into arduino and control WS2812b addressable LED with sound.


## Components/Hardware/parts 

1) Microphone Sound Detection Sensor for Approx $1.50 [Hobbyking](https://hobbyking.com/en_us/keyes-microphone-sound-detection-sensor-module-for-arduino.html?countrycode=US&gclid=Cj0KCQjwhuvlBRCeARIsAM720HovdCHMOsqVcQKAN5QPI1nz0cJw2SFfm2kv25AZecH4VzD5YO_hwEQaAk-PEALw_wcB&gclsrc=aw.ds)
2) Arduino Uno Approx $16.90 [Amazon](https://www.amazon.com/RoboGets-Compatible-ATmega328P-Microcontroller-Electronics/dp/B01N4LP86I/ref=asc_df_B01N4LP86I/?tag=hyprod-20&linkCode=df0&hvadid=309707619534&hvpos=1o1&hvnetw=g&hvrand=18224100230185066445&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9051519&hvtargid=pla-570706401833&psc=1)
3) Bunch of M-M, M-F jumper wires Approx $5.79 [Amazon](https://www.amazon.com/EDGELEC-Breadboard-Optional-Assorted-Multicolored/dp/B07GD2BWPY/ref=sr_1_4?crid=2HVSFC7OD3LH2&keywords=breadboard+wires&qid=1555539468&s=electronics&sprefix=breadboard+wire%2Celectronics%2C222&sr=1-4)
4) WS2812B Addressable LED strip(5m 30LED/1M) Approx 32.99 [Amazon](https://www.amazon.com/Individually-Addressable-Digital-30IC-30LED-Waterproof/dp/B014QKWJDU/ref=asc_df_B014QKWJDU/?tag=hyprod-20&linkCode=df0&hvadid=232831470222&hvpos=1o1&hvnetw=g&hvrand=17243202234086439094&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9051519&hvtargid=pla-391531182889&psc=1)

Then first step to run any sketch from this repository you need Adafruit Neopixel Library to be installed. 

## Adafruit's NeoPixel Library
I have used Adafrit's NeoPixel library is here in my [library](https://github.com/mihir8181/Arduino_geek_projects/tree/master/Sound%20Active%20WS2812b%20LED/Library/Adafruit_NeoPixel-master) folder.

Navigate to the new [Releases](https://github.com/adafruit/Adafruit_NeoPixel), and installed updated library.

## Adafruit's NeoPixel Library Installation via Library Manager
Recent versions of the Arduino IDE (1.6.2 and later) make library installation super easy via the Library Manager interface. 
From the **Sketch menu**, > **Include Library** > **Manage Libraries**...  
In the text input box type in **"NeoPixel"**. Look for **"Adafruit NeoPixel by Adafruit"** and select the latest version by clicking on the popup menu next to the Install button. 
Then click on the **Install** button. After it's installed, you can click the **"close"** button.

If you prefer downloading the libraries manually you can grab them from the [GitHub repository](https://github.com/adafruit/Adafruit_NeoPixel)

## Manually install Adafruit_NeoPixel Library
If you’re using an older version of the IDE, or just want to set things up manually, “classic” installation of the library is as follows: you can visit the [Adafruit_NeoPixel library](https://github.com/adafruit/Adafruit_NeoPixel) page at Github 
and download from there, or just click [Here](https://github.com/adafruit/Adafruit_NeoPixel/archive/master.zip)

1. Download the latest release.
2. Extract the zip file
3. The resulting folder should contain the files **Adafruit_NeoPixel.cpp**, **Adafruit_NeoPixel.h** and an “**examples**” sub-folder. Sometimes in Windows you’ll get an intermediate-level folder and need to move things around.
4. Rename the folder (containing the .cpp and .h files) to **Adafruit_NeoPixel** (with the underscore and everything), and place it alongside your other Arduino libraries, typically in your (home folder)/Documents/Arduino/Libraries folder. Libraries should never be installed in the “Libraries” folder alongside the Arduino application itself…put them in the subdirectory of your home folder.
5. Re-start the Arduino IDE if it’s currently running.

## Microphone Sound Detection Sensor.

<p align="center"><img src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/Sound%20Active%20WS2812b%20LED/Sound%20Sensor.jpg" width="350" hight="250"/></p> 


## How to setup Hardware
Now we need to connect WS2812B LED Strip and Microphone Sound Sensor to Arduino Uno. 

  Arduino     | Microphone Sound Sensor   | WS2812B LED Strip
------------- | --------------------------|------------------
   +5V pin    |           Vs pin          |   +5V pin
   GND pin    |           GND Pin         |   GND pin
Analog A0 pin |       AnalogOUT A0 pin    |     -
   D6 pin     |             -             |   Data In Pin      

<p align="center"><img src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/Sound%20Active%20WS2812b%20LED/Arduino.jpeg" width="500" hight="150"/></p> 
<p align="center"><img src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/Sound%20Active%20WS2812b%20LED/Setup.jpg" width="500" hight="250"/></p> 

Here is the connection to connect WS2812B LED Strip and Microphone Sound Sensor to Arduino Uno.

1) Connect Arduino's digital output pins **D6** to the WS2812B LED Strip's **DataIn** pin
2) Connect arduino's **GND & 5V pins** to the WS2812B LED Strip's **GND & 5V pin** respectively.
3) Connect Arduino's Analog **A0 pin** to the Microphone Sound Detector Sensor 's **Analog OUT A0 pin**.
4) Connect Arduino's **5V pin** to the Microphone Sound Detector Sensor's **Vs pin**.
5) Connect Arduino's **GND pin** to the Microphone Sound Detector Sensor's **GND pin**


## How the code works
```
#include <Adafruit_NeoPixel.h>

#define MIC A0 // Microphone is connected at analog pin A0
#define LED_PIN 6 // WS2812b LED's DataIn pin is connected to arduino's Digital pin D6
#define N_PIXELS 300 // Number of LED in Addressable LED strip
#define N 200 // Number of samples 
```
All NeoPixel sketches begin by including the header file **"#include <Adafruit_NeoPixel.h>"**
The first few lines assign numbers to the symbols "MIC",“LED_PIN”,“N_PIXELS” and "N" for later reference. It doesn’t need to be done this way, but makes it easier to change the pin and length where the NeoPixels are connected without digging deeper into the code.
Here Microphone's pin is define as **MIC** and it is connected to **A0** analog pin of Arduino. WS2812B's DataIn pin is connected to arduino's D6 pin which is define as **LED_PIN**
Number of LED in WS2812b is defined as **N_PIXELS**. 
```
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
```
When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals. 
The line before void setup() **declares a NeoPixel object**. We’ll refer to this by name later to control the strip of pixels. There are three parameters or arguments in parenthesis:
The number of sequential NeoPixels in the strip. In the example this is set to **N_PIXELS**, which was defined as 300 above, equal to 5 meter of medium-density strip. Change this to match the actual number you’re using.
The pin number to which the NeoPixel strip (or other device) is connected. Normally this would be a number, but we previously declared the symbol **LED_PIN** to refer to it by name here.
A value indicating the type of NeoPixels that are connected. In most cases you can leave this off and pass just two arguments; the example code is just being extra descriptive. 
```
void setup() 
{
  Serial.begin(9600);
  strip.begin(); // This initializes the NeoPixel library.
  strip.show(); // To push color data to the strip
}
```
Then, in the setup() function, call begin() to prepare the data pin for NeoPixel output
In **void setup()** We begins Serial connection with buad rate of 9600. Then the **strip.begin()** call to initializes the NeoPixel library.
The second line, **strip.show()**, isn’t absolutely necessary, it’s just there to be thorough. That function pushes data out to the pixels…since no colors have been set yet, this initializes all the NeoPixels to an initial “off” state in case some were left lit by a prior program.

The Project Sketch have mostly all descriptive comments. So its easy to undersand. 

<video width="320" height="240" controls>
  <source src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/Sound%20Active%20WS2812b%20LED/IMG_5165.MOV" type="video/mp4">
</video> 

## Other applications

Finally, I showed you how to control WS2812B with Voice using Arduino Uno.

_**Have a fun with this DIY stuff**_
