# Relay control using IR Remote
 **IR Communication** is a widely used communication protocol and easy to use wireless technology for different applications.
 We use this wireless communication daily, like TV/set-top box/audio player/video player Remote control. 

First, we need to understand first what is IR (Infrared radiation) Communication before controlling a relay using IR remote.

IR or infrared, communication is a common, inexpensive, and easy to use wireless communication technology. IR light is very similar to visible light, except that it has a slightly longer wavelength. This means IR is undetectable to the human eye - perfect for wireless communication. To learn about IR Communication click [here](https://learn.sparkfun.com/tutorials/ir-communication/ir-communication-basics). 

#  

## Components/Hardware/parts 

1) TSOP1738 IR sensor/receiver  2pc for Approx $2.07 [Ebay](https://www.ebay.com/p/5pcs-Sensor-Vishay-Dip-3-TSOP1738-Modules-for-PCM-Remote-Control/1709875306?iid=233148444905&chn=ps)
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

## TSOP IR sensor/receiver
For this project, you can use any remote or old tv remote too. To find IR codes of your remote (any appliances remote). You need TSOP1738 IR photosensor(Receiver) to receive and demodulate the IR signal from a common remote control and to process this signal we need a microcontroller. So, we are using Arduino Uno microcontroller as its easy to use. Image shown below is TSOP IR Receiver.

<p align="center"><img src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/12ch%20Relay%20control%20Using%20IR%20Remote/TSOP382%20IR%20sensor.jpeg" width="350" hight="250"/></p> 

## How to receive IR code

Each time you press a button on the remote control, a unique hexadecimal code is generated. This is the information that is modulated and sent over IR to the receiver. In order to decipher which key is pressed, the receiving microcontroller needs to know which code corresponds to each key on the remote.

Different remotes send different codes for the keypresses, so you’ll need to determine the code generated for each key on your particular remote. If you can find the datasheet, the IR key codes should be listed. If not though, there is a simple Arduino sketch that will read most of the popular remote controls and print the hexadecimal codes to the serial monitor when you press a key. Let's go in details of IRremote library and IR receive sketch.

IRrecv receives and decodes an IR message which is received on a digital pin from TSOP IR sensor/receiver. IRrecv uses an infrared detector connected to any digital input pin. You can find IRrecvDemo sketch in your installed IRremote Library =>  Arduino/libraries/IRremote/examples/IRrecvDemo/IRrecvDemo.ino

The examples/IRrecvDemo sketch provides a simple example of how to receive IR codes:

```
#include <IRremote.h>

int RECV_PIN = 7;
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

The IRrecv class performs the decoding and is initialized with enableIRIn(). The decode() method is called to see if a code has been received; if so, it returns a nonzero value and puts the results into the decode_results structure. (For details of this structure, see the examples/IRrecvDump sketch.) Once a code has been decoded, the resume() method must be called to resume receiving codes.
So, this sketch we are using to find an IR code of each button you press on your remote controller.
You will get IR code printed on the serial monitor when you press a button and that's how you can find IR code for your remote controller.

![](https://github.com/mihir8181/Arduino_geek_projects/blob/master/12ch%20Relay%20control%20Using%20IR%20Remote/arduino%20IR%20receive.png)

  Arduino     | TSOP1738 IR Sensor|
--------------|-------------------|
   5v pin     |    Vs pin         |
   5v pin     |    Vs pin         |
   GND pin    |    GND Pin        | 
   D7 pin     |    OUT pin        |
   
    
Do the need needful connection shown in the picture above.
Connect Arduino to IDE. Compile and upload sketch "IRrecvDemo.ino" from examples.
Then open the serial monitor and press remote buttons in front of sensors, you will receive IR codes of each button on the serial monitor when you press any buttons. For this project I am using remote of my old remote control LED strip shown below.

<p align="center"><img src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/12ch%20Relay%20control%20Using%20IR%20Remote/Remote%20Control.jpg" width="200" hight="80"/></p>

You will receive IR codes on the serial monitor like shown below. So, we need to use this IR codes in the main sketch to control relays when the particular button is pressed and received the respective IR code for it.
<p align="center"><img src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/12ch%20Relay%20control%20Using%20IR%20Remote/Serial%20Monitor.png" width="900" hight="150"/></p>

And here are all IR codes for my remote controller.
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
Now we need to connect relay board and TSOP 1738 IR Sensor/Receiver to Arduino Uno. 

  Arduino     | TSOP 1738 IR Sensor| Relay Board
------------- | -------------------|---------------
   5v pin     |    Vs pin          |   VCC pin
   GND pin    |    GND Pin         |   GND pin
Analog A1 pin |    OUT pin         |     -
D2 - D13 pin  |      -             | In1 - In12 Pin      

<img src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/12ch%20Relay%20control%20Using%20IR%20Remote/IR%20Realy%20Control.png" width="900" hight="300"/> 

Here is the connection to connect Relay Board and TSOP1738 IR sensor to Arduino Uno.
Connect Arduino's digital output pins **D2 - D13** of Arduino to the 12ch-5v relay board input pins **In1-In12**.
Connect arduino's **GND & 5V pins** to the 12ch-5v relay board's **GND & VCC pin** respectively.
Connect Arduino's Analog **A1 pin** to the TSOP IR's **OUT pin**.
Connect Arduino's **5v pin** to the TSOP IR's **Vs pin**.
Connect Arduino's **GND pin** to the TSOP IR's **GND pin**

<p align="center"><img src="https://github.com/mihir8181/Arduino_geek_projects/blob/master/12ch%20Relay%20control%20Using%20IR%20Remote/Relay%20board%20Image.jpeg" width="400" hight="100"/></p>

I have created 2 versions of code for IR remote controlled 12ch 5v Relay. This relay has 12 channel and operates on 5 volt DC supply. In version v1 12-Relays can turn On or OFF using 12 remote buttons(one button per relay to turn On & OFF). When button A is pressed, then IR code 0xF720DF for button A is received on the serial monitor. Then we are processing those in cases and relay 1 will turn On and it will turn off if the same button is pressed again. Use this[_12_ch_relay_over_IR_remote_v1.ino](https://github.com/mihir8181/Arduino_geek_projects/blob/master/12ch%20Relay%20control%20Using%20IR%20Remote/sketch/_12_ch_relay_over_IR_remote_v1.ino). 


Version v2 is almost the same as v1 just the one functionality is different than v1. In this version of the code. It will work as same as V1, but when Button On or Off is press on the remote I am wirelessly turning On and Off all relay together respectively. For this functionality  use[_12ch_Relay_control_over_remote_v2.ino](https://github.com/mihir8181/Arduino_geek_projects/blob/master/12ch%20Relay%20control%20Using%20IR%20Remote/sketch/_12ch_Relay_control_over_remote_v2.ino).
Defining code 13 and code 14 for turn OFF and ON all relays respectively 
```
code13 0xF740BF  code received from button OFF ---> to turn OFF all the Digital pins 
code14 0xF7C03F  code received from button ON ----> to turn ON all the digital pins
```
Handling each code separately with **CASE structure**. And using **FOR loop** to write digital output OFF or ON (High or LOW) for all 12 digital output pins of Arduino one after one.

```
          case code13: // all Relay OFF when this IR code received
          {
            for (int i=1; i <= 13; i++){
             digitalWrite(i-1, HIGH);
             delay(100);
             itsONled[i] = 0;
             Serial.println(itsONled[i]);
             }
           }
          
           break;
          case code14: // all Relay ON when this IR code received
          {
           for (int i=1; i <= 13; i++){
             digitalWrite(i-1, LOW);
             delay(100);
             itsONled[i] = 1;
             Serial.println(itsONled[i]);
             } 
           } 
          break;
```          

## How the code works

For any IR communication using the IRremote library, first we need to create an object called **irrecv** and specify the pin number where the IR receiver is connected (line 60). This object will take care of the protocol and processing of the information from the receiver.

The next step is to create an object called **results** , from the **decode_results class**, which will be used by the **irrecv object** to share the decoded information with this application (line 65).

In the **void setup()** block, first we configure the serial monitor baud rate. Next we start the **IR receiver** by calling the IRrecv member function **enableIRIn()** (line 73).

In the **void loop()** block, the function **irrecv.decode** (line 104) will return true if a code is received and the program will execute the code in the if statement. The received code is stored in **results.value**(line 106). Then I used a **switch case** to handle each IR code and print the corresponding key value.

At the end of the **void loop()** section, we call **irrecv.resume()** (line 241) to reset the receiver and prepare it to receive the next code.

## Other applications

Based on this you can control 12 number of appliances and also you can modify it to more or less number of relay control as per your application. You can build part of your home automation using this sketch. You can control 12 Solenoid valve instead of relay, etc. There are many application of daily uses for which you can use these sketches. The soley purpose of this project is to control relays using IR remote which is achieved.   

So far we have learned the properties of IR(infrared radiation) and how we can communicate between transmitter and receiver using IR receiver(TSOP sensor/receiver) and remote controller (transmitter). Also learned to find the IR codes of any remote controller and how to use them for any application. Finally, I showed you how to control relays with IR remote using Arduino Uno.

_**Have a fun with this DIY stuff**_
