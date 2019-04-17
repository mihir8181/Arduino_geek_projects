# Relay control using IR Remote

First we need to understand first what is IR (Infrared radiation) Communication.

IR, or infrared, communication is a common, inexpensive, and easy to use wireless communication technology. IR light is very similar to visible light, except that it has a slightly longer wavelength. This means IR is undetectable to the human eye - perfect for wireless communication. To learn about IR Communication click [here](https://learn.sparkfun.com/tutorials/ir-communication/ir-communication-basics). 

To find IR codes of your remote (any appliances remote). You need TSOP382 IR photo sensor to receive and demodulate the IR signal from a common remote control.
![TSOP382 IR]()



To run this sketch you need IRremote Library. 

## Ken Shirriff's IRremote Library Version - 2.1.0
I have used Ken Shirriff's IRremote library Version 2.1.0 is here in my [lib](https://github.com/mihir8181/Arduino_geek_projects/tree/master/12ch%20Relay%20control%20Using%20IR%20Remote/Lib) folder.

This library enables you to send and receive using infra-red signals on an Arduino.
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

