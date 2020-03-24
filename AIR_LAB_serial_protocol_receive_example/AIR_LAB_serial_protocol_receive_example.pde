import processing.serial.*;

Serial myPort;                       // The serial port
int[] serialInArray = new int[3];    // Where we'll put what we receive

// sensor value array
int [] sensorValues = new int [4];  // initialize the sensor array with 4 indexes, meaning 4 sensors

// Serial protocol variables
int value = 0;
int channel;


void setup() {
  println(Serial.list());
  String portName = Serial.list()[10];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  println("S0", sensorValues[0]);
  println("S1", sensorValues[1]);
  println("S2", sensorValues[2]);
  println("S3", sensorValues[3]);
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
      if (channel == 0) sensorValues[0] = value;
      else if (channel == 1) sensorValues[1] = value;
      else if (channel == 2) sensorValues[2] = value;
      else if (channel == 3) sensorValues[3] = value;      
    }
    value = 0;
  }
}
