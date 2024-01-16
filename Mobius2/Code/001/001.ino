#include <IBusBM.h>
IBusBM IBus; // IBus object

int ch1;
int ch2;
int ch3;
int ch4;
int ch5;
int ch6;
int ch7;
int ch8;
int ch9;
int ch10;

int out1;
int out2;
int out1a;
int out2a;

float RFB;
float RFBa;
float RFBFiltered;
float RLR;
float RLRa;
float RLRFiltered;
float RT;
float RTa;
float RTFiltered;

float LFB;
float LFBa;
float LFBFiltered;
float LLR;
float LLRa;
float LLRFiltered;
float LT;
float LTa;
float LTFiltered;


float stride;
int stride2;

unsigned long currentMillis;
long previousMillis = 0;        // set up timers
long interval = 10;             // time constant for timer


void setup() {

    Serial.begin(115200);    
    IBus.begin(Serial3, IBUSBM_NOTIMER);    // change to Serial1 or Serial2 port when required
    
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
      
}

void loop() {

  currentMillis = millis();
  if (currentMillis - previousMillis >= 10) {  // start timed event    
      previousMillis = currentMillis;

      IBus.loop();

      ch1 = IBus.readChannel(0); // get latest value for servo channel 0
      ch2 = IBus.readChannel(1); // get latest value for servo channel 1
      ch3 = IBus.readChannel(2); // get latest value for servo channel 3
      ch4 = IBus.readChannel(3); // get latest value for servo channel 4
      ch5 = IBus.readChannel(4); // get latest value for servo channel 5
      ch6 = IBus.readChannel(5); // get latest value for servo channel 6
      ch7 = IBus.readChannel(6); // get latest value for servo channel 7
      ch8 = IBus.readChannel(7); // get latest value for servo channel 8
      ch9 = IBus.readChannel(8); // get latest value for servo channel 9
      ch10 = IBus.readChannel(9); // get latest value for servo channel 10

      LFB = ch1;
      RFB = ch4;
      RLR = ch2;
      RT = ch6;
      LLR = ch3;
      LT = ch5;
      
      // threshold sticks

      RFBa = thresholdStick(RFB);
      RLRa = thresholdStick(RLR);
      RTa = thresholdStick(RT);
      LFBa = thresholdStick(LFB);
      LLRa = thresholdStick(LLR);
      LTa = thresholdStick(LT);

      // filter sticks

      RFBFiltered = filter(RFBa, RFBFiltered,20);
      RLRFiltered = filter(RLRa, RLRFiltered,20);
      RTFiltered = filter(RTa, RTFiltered,20);
      LFBFiltered = filter(LFBa, LFBFiltered,20);
      LLRFiltered = filter(LLRa, LLRFiltered,20);
      LTFiltered = filter(LTa, LTFiltered,20);

/*
      Serial.print(RFBFiltered);
      Serial.print(" , ");
      Serial.println(LTFiltered);

*/

      out2 = RFBFiltered*-1;
      out1 = LTFiltered*-1;

      out1 = constrain(out1,-255,255);
      out2 = constrain(out2,-255,255);

      // *** right hand track

      if (out1 >0) {
          analogWrite(4, out1);
          analogWrite(5, 0);
      }

      else if (out1 <0) {
          out1a = abs(out1);
          analogWrite(5, out1a);
          analogWrite(4, 0);
      }

      else {
          analogWrite(5, 0);
          analogWrite(4, 0);
      }

      // *** left hand track

      if (out2 >0) {
          analogWrite(6, out2);
          analogWrite(7, 0);
      }

      else if (out2 <0) {
          out2a = abs(out2);
          analogWrite(7, out2a);
          analogWrite(6, 0);
      }

      else {
          analogWrite(6, 0);
          analogWrite(7, 0);
      }

      



  }   // end of timed loop

}



