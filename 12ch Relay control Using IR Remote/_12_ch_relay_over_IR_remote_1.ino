#include <IRremote.h>   // IR remote library header file 
 
int RECV_PIN = A1; // connect the output pin of TSOP4838(IRsensor) here

/*----------- control relays using D2 - D13 pin ----------------
   variables 
-------------------------------------------------------------*/
int led1 = 2;     
int led2 = 3;     
int led3 = 4;     
int led4 = 5;    
int led5 = 6;    
int led6 = 7;       
int led7 = 8;
int led8 = 9;
int led9 = 10;
int led10 = 11;
int led11 = 12;
int led12 = 13;
/* --------------------------------------------------
 The initial state of LEDs is OFF (zero) 
the first zero must remain zero but you can 
change the others to 1's if you want a certain
led to light when the board is powered. */
int itsONled[] = {0,0,0,0,0,0,0,0,0,0,0,0,0}; // Status Array declaration
/*----------------------------------------------------------------------*/
  
/*-------------------------------------------------------  
  Define IR codes of remote 
----------------------------------------------------------
 Define each IR codes of your remote.
 Here I am want to use 12ch relay board so I am using
 12 IR code of my remote. you can use any remote of your
 household appliances and find IR codes of that remote by using
 IRrecvDemo from IRremote library examples, and use those 
 IR codes here below. 
------------------------------------------------------------*/
  
#define code1  0xF720DF // code received from button A
#define code2  0xF7A05F // code received from button B
#define code3  0xF7609F // code received from button C
#define code4  0xF7E01F // code received from button D
#define code5  0xF710EF // code received from button E
#define code6  0xF7906F // code received from button F
#define code7  0xF750AF // code received from button G
#define code8  0xF7D02F // code received from button H
#define code9  0xF730CF // code received from button E
#define code10 0xF7B04F // code received from button F
#define code11 0xF7708F // code received from button G
#define code12 0xF7F00F // code received from button H
/*---------------------------------------------------------
 create an object called irrecv and specify the pin number where the IR receiver is connected.
This object will take care of the protocol and processing of the information from the receiver 
-----------------------------------------------------------------------*/
IRrecv irrecv(RECV_PIN);  
/*-------------------------------------------------------------------
create an object called results , from the decode_results class, 
which will be used by the irrecv object to share the decoded information
---------------------------------------------------------------------*/ 
decode_results results;

/*------------------------------------------------
 setup initialize serial monitor baud rate and
 pin mode to output as we are controlling Relays 
-----------------------------------------------*/
void setup()
{
  Serial.begin(9600);   // you can comment this line if you dont want serial monior
  irrecv.enableIRIn();  // Start the receiver by calling the IRrecv member function enableIRIn()
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(led8, OUTPUT);
  pinMode(led9, OUTPUT);
  pinMode(led10, OUTPUT);
  pinMode(led11, OUTPUT);
  pinMode(led12, OUTPUT);
}.

/* -----------------------------Main loop-----------------------------------
  Its main loop and inside main loop Processing based on received IR code             
 Switch case to handle each IR code and control digital pins
 ---------------------------------------------------------------------------*/
void loop() {
  if (irrecv.decode(&results)) // irrecv.decode will return true if a code is received
  {
    unsigned int value = results.value;   // Received code is stored in value from result.value
    switch(value) {
       case code1:
         if(itsONled[1] == 1) {        // if first led is on then
            digitalWrite(led1, LOW);   // turn it off when button is pressed
            itsONled[1] = 0;           // and set its state as off
         } else {                      // else if first led is off
             digitalWrite(led1, HIGH); // turn it on when the button is pressed
             itsONled[1] = 1;          // and set its state as on
         }
          break; 
       case code2:
         if(itsONled[2] == 1) {
            digitalWrite(led2, LOW);
            itsONled[2] = 0;
         } else {
             digitalWrite(led2, HIGH);
             itsONled[2] = 1;
         }
          break;
       case code3:
         if(itsONled[3] == 1) {
            digitalWrite(led3, LOW);
            itsONled[3] = 0;
         } else {
             digitalWrite(led3, HIGH);
             itsONled[3] = 1;
         }
          break;
       case code4:
         if(itsONled[4] == 1) {
            digitalWrite(led4, LOW);
            itsONled[4] = 0;
         } else {
             digitalWrite(led4, HIGH);
             itsONled[4] = 1;
         }
          break; 
        case code5:
         if(itsONled[5] == 1) {
            digitalWrite(led5, LOW);
            itsONled[5] = 0;
         } else {
             digitalWrite(led5, HIGH);
             itsONled[5] = 1;
         }
          break;       
               case code6:
         if(itsONled[6] == 1) {
            digitalWrite(led6, LOW);
            itsONled[6] = 0;
         } else {
             digitalWrite(led6, HIGH);
             itsONled[6] = 1;
         }
          break;  
                 case code7:
         if(itsONled[7] == 1) {
            digitalWrite(led7, LOW);
            itsONled[7] = 0;
         } else {
             digitalWrite(led7, HIGH);
             itsONled[7] = 1;
         }
          break;
        case code8:
         if(itsONled[8] == 1) {
            digitalWrite(led8, LOW);
            itsONled[8] = 0;
         } else {
             digitalWrite(led8, HIGH);
             itsONled[8] = 1;
         }
          break;
          case code9:
         if(itsONled[9] == 1) {
            digitalWrite(led9, LOW);
            itsONled[9] = 0;
         } else {
             digitalWrite(led9, HIGH);
             itsONled[9] = 1;
         }
          break;
          case code10:
         if(itsONled[10] == 1) {
            digitalWrite(led10, LOW);
            itsONled[10] = 0;
         } else {
             digitalWrite(led10, HIGH);
             itsONled[10] = 1;
         }
          break;
          case code11:
         if(itsONled[11] == 1) {
            digitalWrite(led11, LOW);
            itsONled[11] = 0;
         } else {
             digitalWrite(led11, HIGH);
             itsONled[11] = 1;
         }
          break;
          case code12:
         if(itsONled[12] == 1) {
            digitalWrite(led12, LOW);
            itsONled[12] = 0;
         } else {
             digitalWrite(led12, HIGH);
             itsONled[12] = 1;
         }
          break;
// --------------------------------------you can comment this part. It is just to monitor each LED status on serial---------         
          {
           for (int i=1; i <= 13; i++)
           {  
          Serial.println(itsONled[i]);
             } 
           } 
//-------------------------------------- ---------------------------------------------------------------   
    }
    Serial.println(value); // you can comment this line
    irrecv.resume(); //we call irrecv.resume() to reset the receiver and prepare it to receive the next code.
  }
}
