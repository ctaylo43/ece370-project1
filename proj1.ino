// Define Pins //
#define FWDPIN 10
#define BWDPIN 9
#define IRPIN 12

// Global Variables //
int serialAngle;
float rotations;
int tickNum;
int curTick = 0;
int irDetection = LOW;
int detectionCount = 0;

// Set pins and begin serial
void setup() {
  Serial1.begin(9600);
  pinMode(FWDPIN, OUTPUT);
  pinMode(BWDPIN, OUTPUT);
  pinMode(IRPIN, INPUT);
}

/* 
 *  Reads in angle value from serial and converts to number of ticks
 *  Using the number of ticks, rotates the motor in the corresponding
 *  direction. Stops the motor once the required amount of ticks is reached
 */
void loop() {
  // If the serial is available, reads input value
  if (Serial.available() > 0) {
    serialAngle = Serial.parseInt();

    if (serialAngle < -720) {
      Serial.println("Given angle exceeds the minimum value, setting to -720");
      serialAngle = -720;
    }

    else if (serialAngle > 720) {
      Serial.println("Given angle exceeds the maximum value, setting to 720");
      serialAngle = 720;
    }
    
    setTickNum(serialAngle);
    
  }
  
  irDetection = digitalRead(IRPIN);
  
  if (tickNum != 0) {
    // stops motor once the current number of ticks reaches the number of ticks needed
    if (abs(tickNum) == curTick) {
      stopMotor();
    }

    // rotates clockwise (forward) when the tick number is positive
    else if (tickNum > 0) {
      rotateClockwise();
    }

    // rotates counter-clockwise (backward) when the tick number is negative
    else if (tickNum < 0) {
      rotateCounterClockwise();
    }
    
    // when the wheel is detected, increment count
    if (irDetection == LOW){
      detectionCount++;
    }
  }

  // wheel rotates completely after 2 detections, increment current tick
  if (detectionCount == 2){
    curTick++;
    detectionCount = 0;
  }
}

// Functions //

// calculates and sets the number of ticks from the given angle
void setTickNum(int angle) {
  rotations = ((float)serialAngle) / 360.0;
  tickNum = (int)(rotations * 75);
}

// stops motor from rotating
void stopMotor() {
  analogWrite(FWDPIN, 127);
  analogWrite(BWDPIN, 127);
  tickNum = 0;
  curTick = 0;
}

// rotates the motor clockwise
void rotateClockwise() {
  analogWrite(FWDPIN, 255);
  analogWrite(BWDPIN, 127);
}

// rotates the motor counter-clockwise
void rotateCounterClockwise() {
  analogWrite(FWDPIN, 255);
  analogWrite(BWDPIN, 127);
}
