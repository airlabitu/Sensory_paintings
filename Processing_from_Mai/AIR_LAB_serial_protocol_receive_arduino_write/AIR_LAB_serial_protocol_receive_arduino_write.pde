//This code receives sensor info from the arduino MPR21, plays music and has a simple volume control setup. 
import processing.serial.*;
import processing.sound.*;

//defining pins
int digitalPin = 3;

//defining values
float analogvalue;

// sound objects
SoundFile file1;
SoundFile file2;
Sound s; //this one is used to control volume

Serial myPort;                       // The serial port
int[] serialInArray = new int[3];    // Where we'll put what we receive

int [] sensorValue = new int [4]; // initializes the sensor array with 4 spaces

int value = 0; //thisvalue holds the sensor value
int channel; //this describes the sensor


void setup() {
  size(640, 800);
  background(255);
  file1 = new SoundFile(this, "brushstrokes.wav");
  file2 = new SoundFile(this, "lightrain.wav");
  file1.loop();
  //s = new Sound(this);
  println(Serial.list());
  String portName = Serial.list()[2];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  float amplitude = map(sensorValue[0],180.0, 20.0, 0.0, 1.0);
  file1.amp(amplitude);
  println("S0", sensorValue[0]); //lægges herop, fordi det er her vi kan arbejde med dem. 
  println("S1", sensorValue[1]); 
  println("S2", sensorValue[2]); 
  println("S3", sensorValue[3]);
  println("Volume ", amplitude);
  println();
  
}



void serialEvent(Serial myPort) {
  
  
  // read a byte from the serial port:
  int inByte = myPort.read();
  
   
  if ((inByte>='0') && (inByte<='9')) {
    value = 10*value + inByte - '0';
  } else {
    if (inByte=='c') channel = value;
    else if (inByte=='w') {
      //println("Done reading", channel, value);
      if (channel == 0) sensorValue[0] = value;
      else if (channel ==1) sensorValue[1] = value;
      else if (channel ==2) sensorValue[2] = value;
      else if (channel ==3) sensorValue[3] = value;
    }
    value = 0;
  }
  
  
  /*
  println("BYTE", inByte);

  if (inByte == 'c') {
    println("SUCCES c", inByte);
  }
  if (inByte == 'w') {
    println("SUCCES w", inByte);
  }
  */
}
