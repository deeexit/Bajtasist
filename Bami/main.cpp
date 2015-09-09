// OneWire test

#include <OneWire.h>


#define ONE_WIRE_BUS 15
#define LED_LIGHT 13;

// OneWire is on pin 15
OneWire ow(ONE_WIRE_BUS);
// State of the pin
int state;

void set_status() 
{
   ow.reset();
   ow.skip();
   ow.write(0x4e);
   ow.write(0x00);
   ow.write(0x0B);
   ow.reset();
   ow.skip();
   ow.write(0x48);
   ow.write(0x00);
   ow.reset();
}

void set_threshold() 
{
   ow.reset();
   ow.skip();
   ow.write(0x4e);
   ow.write(0x00);
   ow.write(0x02);
   ow.reset();
   ow.skip();
   ow.write(0x48);
   ow.write(0x00);
   ow.reset();
}




void setup() {
  Serial.begin(19200);
  Serial.println("Starting...");
  pinMode (13, OUTPUT);
  pinMode (14, OUTPUT);
    digitalWrite(13, LOW);
  digitalWrite(14, HIGH);
   set_status();
//   set_threshold();
  //oneWire.begin();

}

void loop() {
  byte addr[9];
  ow.reset();
  state = digitalRead(14);
   if (state > 0) 
     {
	digitalWrite(14, LOW);
	digitalWrite(13, HIGH);
     }
   
   else 
     {
	digitalWrite(13, LOW);
	digitalWrite(14, HIGH);
     }
   
  if ( ow.search(addr)) {
    Serial.println();
    Serial.print("Found ");
    for (int z=0;z<9;z++) {
      Serial.print(addr[z], HEX);
    }
    Serial.println();
    ow.reset_search();
    delay(250);
    //return;
  }
  // LEts read the voltage on DS2348 (Channel A) page0
  ow.reset();
  ow.skip();
  // Issue a voltage conversion
  ow.write(0xb4);
  delay(50);
  ow.reset();
  ow.skip();
  // Issue a temperature conversion
  ow.write(0x44);
  delay(750);
  ow.reset();
  ow.skip();
  ow.write(0xb8);
  ow.write(0x00);
  delay(50); 
  ow.reset();
  ow.skip();
  ow.write(0xbe);
  ow.write(0x00);
  delay(50);
 
  byte test[8];
  ow.read_bytes(test, 8);
   // Read page 1
   ow.reset();
   ow.skip();
   ow.write(0xb8);
   ow.write(0x01);
   ow.reset();
   ow.skip();
   ow.write(0xbe);
   ow.write(0x01);
   byte page1[8];
   ow.read_bytes(page1, 8);

   // Read page 2
   ow.reset();
   ow.skip();
   ow.write(0xb8);
   ow.write(0x02);
   ow.reset();
   ow.skip();
   ow.write(0xbe);
   ow.write(0x02);
   byte page2[8];
   ow.read_bytes(page2, 8);

   // Read page 7
   ow.reset();
   ow.skip();
   ow.write(0xb8);
   ow.write(0x07);
   ow.reset();
   ow.skip();
   ow.write(0xbe);
   ow.write(0x07);
   byte page7[8];
   ow.read_bytes(page7, 8);
   
   
   Serial.print ("Read ");
   for (int x=0;x<9;x++){
     Serial.print(test[x], BIN);
  }
 
   
   Serial.println();
   Serial.print("Status: ");
   Serial.println(test[0], BIN);
   Serial.print ("Temperature: ");
   Serial.print ((test[2] << 5 | test[1] >> 3) * 0.03125);
   float haha = 0.0;
   haha = (((test[4] << 8) & 0x00300) | (test[3] & 0x0ff)) / 100.0;
   Serial.print (" Voltage: ");
   Serial.println(haha);
   Serial.print( "Current: ");
   
   
   Serial.print(test[5]);
   Serial.println(test[6]);
   float curr = 0.0;
  //char curr;
//   curr = (test[5] |  test[6]);
//   curr = curr / 409.6;
//   curr = (((test[5] & 0x03) << 8) | test[6]) / 409.6;
   Serial.println (test[6], BIN);
   Serial.println (test[5], BIN);
   //curr = ((test[5] & (test[6] >> 6)) / 409.6);
 //  test[6] = test[6] << 6;
   //Serial.println(test[6], BIN);
//   curr = ((test[5] & ~test[6]) / 409.6);
   curr = (test[5] & test[6]) / 409.6;
   Serial.println(curr, BIN);
   Serial.print ( "Translated: ");
   //Serial.println(curr, BIN);
   Serial.print ("Current Threshold: ");
   Serial.println (test[7], HEX);
   Serial.print ("Page 1 ");
   Serial.print(" ICA: ");
   Serial.println(page1[4], BIN);
   Serial.print (" Offset 1: ");
   Serial.println(page1[5], BIN);
   Serial.print (" Offset 2: ");
   Serial.println(page1[6], BIN);
   Serial.print ("Time: ");
   Serial.print (page1[3]);
   Serial.print (":");
   Serial.print (page1[2]);
   Serial.print (":");
   Serial.print (page1[1]);
   Serial.print (":");
   Serial.print (page1[0]);
   // Lets calculate proper time
   
   Serial.println();
   Serial.print ("DFST: ");
   Serial.print (page2[3]);
   Serial.print (":");
   Serial.print (page2[2]);
   Serial.print (":");
   Serial.print (page2[1]);
   Serial.print (":");
   Serial.print (page2[0]);
   
   Serial.println();
   Serial.print ("EOCT: ");
   Serial.print (page2[7]);
   Serial.print (":");
   Serial.print (page2[6]);
   Serial.print (":");
   Serial.print (page2[5]);
   Serial.print (":");
   Serial.print (page2[4]);
   Serial.println();
   
   Serial.println();
   Serial.print ("CCA: ");
   Serial.print (page7[4]);
   Serial.println (page7[5]);
   Serial.print ("DCA: ");
   Serial.print (page7[6]);
   Serial.println (page7[7]);
   Serial.println();
   
   
   
   delay(10000);

}

