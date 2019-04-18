# Relay control using IR Remote
 IR Communication is widely used communication protocol and easy to use wireless technology for different applications.
 We use this wireless communication daily, like TV/settop box/audio player/video player Remote control. 

First we need to understand first what is IR (Infrared radiation) Communication before controlling relay using IR remote.

IR, or infrared, communication is a common, inexpensive, and easy to use wireless communication technology. IR light is very similar to visible light, except that it has a slightly longer wavelength. This means IR is undetectable to the human eye - perfect for wireless communication. To learn about IR Communication click [here](https://learn.sparkfun.com/tutorials/ir-communication/ir-communication-basics). 

For this project you can use any remote or old tv remote too. To find IR codes of your remote (any appliances remote). You need TSOP382 IR photo sensor(Receiver) to receive and demodulate the IR signal from a common remote control and to process this signal we need microcontroller. So, we are using Arduino uno microcontroller as its easy to use. Image shown below is TSOP IR Receiver.

<img src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/12ch%20Relay%20control%20Using%20IR%20Remote/TSOP382%20IR%20sensor.jpeg" width="350" hight="250"/> 

#  

## Components/Hardware/parts 

1) TSOP382 IR sensor/receiver  Approx $0.53 [here](https://www.alliedelec.com/product/vishay-dale/tsop38238/70331872/?gclid=CjwKCAjwndvlBRANEiwABrR32IOTydD3KtKM1kgRFPIFdYcZSVGTDUAJz0x2V7v3q4aTXxHf_2D5-BoCq68QAvD_BwE&gclsrc=aw.ds)
2) Arduino Uno Approx $16.90 [Amazon](https://www.amazon.com/RoboGets-Compatible-ATmega328P-Microcontroller-Electronics/dp/B01N4LP86I/ref=asc_df_B01N4LP86I/?tag=hyprod-20&linkCode=df0&hvadid=309707619534&hvpos=1o1&hvnetw=g&hvrand=18224100230185066445&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9051519&hvtargid=pla-570706401833&psc=1)
3) 8-channel or 12-channel Relay Board Approx $10.88 [Amazon](https://www.amazon.com/8-Channel-Shield-Module-Optocoupler-Arduino/dp/B01ARS8OVQ/ref=asc_df_B01ARS8OVQ/?tag=hyprod-20&linkCode=df0&hvadid=241973970700&hvpos=1o6&hvnetw=g&hvrand=17922889264405877427&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9051519&hvtargid=pla-395268347022&psc=1) 
4) Bunch of M-M M-F jumper wires Approx $5.79 [Amazon](https://www.amazon.com/EDGELEC-Breadboard-Optional-Assorted-Multicolored/dp/B07GD2BWPY/ref=sr_1_4?crid=2HVSFC7OD3LH2&keywords=breadboard+wires&qid=1555539468&s=electronics&sprefix=breadboard+wire%2Celectronics%2C222&sr=1-4)
5) Remote Controller(Used here for project) Approx $3.72 [Ebay](https://www.ebay.com/itm/For-3528-5050-RGB-LED-Strip-Light-Mini-3-24-44-Key-IR-Remote-Wireless-Controller/152286320967?var=451484065414&hash=item2374f8d947:m:mRcNXQbJlG1xPvFdzzDc-eQ)


Then first step to run any sketch from this repository you need IRremote Library to be installed. 

## Ken Shirriff's IRremote Library Version - 2.1.0
I have used Ken Shirriff's IRremote library Version 2.1.0 is here in my [lib](https://github.com/mihir8181/Arduino_geek_projects/tree/master/12ch%20Relay%20control%20Using%20IR%20Remote/Lib) folder.

This library enables you to send and receive using infra-red signals on an Arduino. This IR remote library lets you both send and receive IR remote codes in multiple protocols. It supports NEC, Sony SIRC, Philips RC5, Philips RC6, and raw protocols.
Check [here](http://z3t0.github.io/Arduino-IRremote/) for more information.

Navigate to the new [Releases](https://github.com/z3t0/Arduino-IRremote/releases), and installed updated library.

## Ken Shirriff's IRremote Library Installation
You can obtain this library through the Arduino Library Manager. Search for IRremote by shirriff and you should be able to install the latest version. If you prefer downloading the libraries manually you can grab them from the [GitHub repository](https://github.com/z3t0/Arduino-IRremote)

or follow the steps: 
1. Navigate to the [Releases](https://github.com/z3t0/Arduino-IRremote/releases) on [GitHub repository](https://github.com/z3t0/Arduino-IRremote) page.
2. Download the latest release.
3. Extract the zip file
4. Move the "IRremote" folder that has been extracted to your libraries directory.
5. Make sure to delete Arduino_Root/libraries/RobotIRremote. Where Arduino_Root refers to the install directory of Arduino. The library RobotIRremote has similar definitions to IRremote and causes errors.



## How to receive IR code

Each time you press a button on the remote control, a unique hexadecimal code is generated. This is the information that is modulated and sent over IR to the receiver. In order to decipher which key is pressed, the receiving microcontroller needs to know which code corresponds to each key on the remote.

Different remotes send different codes for the keypresses, so you’ll need to determine the code generated for each key on your particular remote. If you can find the datasheet, the IR key codes should be listed. If not though, there is a simple Arduino sketch that will read most of the popular remote controls and print the hexadecimal codes to the serial monitor when you press a key. Lets go in details of IRremote library and IR receive sketch.

IRrecv receives and decodes an IR message which is received on digital pin from TSOP IR sensor/receiver. IRrecv uses an infrared detector connected to any digital input pin. You can find IRrecvDemo sketch in your installed IRremote Library =>  Arduino/libraries/IRremote/examples/IRrecvDemo/IRrecvDemo.ino

The examples/IRrecvDemo sketch provides a simple example of how to receive IR codes:

```
#include <IRremote.h>

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}
```

The IRrecv class performs the decoding, and is initialized with enableIRIn(). The decode() method is called to see if a code has been received; if so, it returns a nonzero value and puts the results into the decode_results structure. (For details of this structure, see the examples/IRrecvDump sketch.) Once a code has been decoded, the resume() method must be called to resume receiving codes.
So, this sketch we are using to find IR code of each button you press on your remote controller.
You will get IR code printed on serial monitor when you press button and thats how you can find IR code for your remote controller.

Here are all IR codes for my remote controller.
```
code1  0xF720DF  code received from button A 
code2  0xF7A05F  code received from button B 
code3  0xF7609F  code received from button C 
code4  0xF7E01F  code received from button D 
code5  0xF710EF  code received from button E 
code6  0xF7906F  code received from button F 
code7  0xF750AF  code received from button G 
code8  0xF7D02F  code received from button H 
code9  0xF730CF  code received from button E 
code10 0xF7B04F  code received from button F 
code11 0xF7708F  code received from button G 
code12 0xF7F00F  code received from button H 
code13 0xF740BF  code received from button OFF ---> to turn OFF all the Digital pins 
code14 0xF7C03F  code received from button ON ----> to turn ON all the digital pins 
```

## How to setup Hardware

  Arduino     | TSOP IR Sensor| Relay Board
------------- | ------------- |-------------
   5v pin     |    Vs pin     |  VCC pin
   GND pin    |    GND Pin    |  GND pin
Analog A1 pin |    OUT pin    |     -
D2 - D13 pin  |      -        |In1 - In12 Pin      


