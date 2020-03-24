#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit))
#endif

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

//constant variables
const int vibroPin1 = 3;
const int vibroPin2 = 5;
const int vibroPin3 = 6;
const int vibroPin4 = 9;

//variables
int sensorMapped1 = 0;
int sensorMapped2 = 0;
int sensorMapped3 = 0;
int sensorMapped4 = 0;

int sensArray[] = {sensorMapped1,sensorMapped2,sensorMapped3,sensorMapped4};
int vibeArray[] = {vibroPin1, vibroPin2, vibroPin3, vibroPin4};



void setup() {
  pinMode (vibroPin1, OUTPUT);
  Serial.begin(9600);

  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
  }

  Serial.println("Adafruit MPR121 Capacitive Touch sensor test");

  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

  cap.setThresholds(1, 1); //Sets threshold, comment out or change to 12,6 for standard sensitivity.
}

void loop() {
  for (int i = 0; i < sensArray.length; i++){
    Serial.print(i);
    Serial.print('c');
    Serial.print(senseArray[i]);
    Serial.print('w'); 
  }

  
  // Get the currently touched pads
  currtouched = cap.touched();

  /* for (uint8_t i = 0; i < 12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
      int sensorMapped = int(map(cap.filteredData(i),80, 160, 255,50));
      Serial.print("sensor mapped ");
      Serial.println(sensorMapped);
      if ((currtouched & _BV(0)) && !(lasttouched & _BV(0)) ) {
        analogWrite(vibroPin1, sensorMapped); //original

      }
      if ((currtouched & _BV(11)) && !(lasttouched & _BV(11)) ) {

        analogWrite(vibroPin2, sensorMapped);
      }
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
      delay(2000);
      analogWrite(vibroPin1, 0);
      analogWrite(vibroPin2, 0);


    }
    }
  */

  // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  //return;


  // maps the sensor data to the output range

  //sensorMapped1 = int(map(cap.filteredData(0), 80, 144, 255, 0)); Original

  //reads sensor data, constrains sensor mappings to vibe input vallues and sends it to the motors
  for (int i = 0; i<4 ; i++){
    sensArray[i] = int(map(cap.filteredData(i),66,130, 255, 0));
    sensArray[i]= constrain(sensArray[i], 0, 255);
    analogWrite(vibeArray[i],sensArray[i]);
    Serial.print("sensor mapped  ");
    Serial.println(sensArray[i]);
 
    }
 

 


  //analogWrite(vibroPin1, sensorMapped); //writes the mapped sensordata to the pin


  // debugging info, what - changed array size to 4, since this code only focuses on pin 0-3
  return;
 
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i = 0; i < 4; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i = 0; i < 4; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");

  }
  Serial.println();

  // put a delay so it isn't overwhelming
  delay(2000);
 
}
