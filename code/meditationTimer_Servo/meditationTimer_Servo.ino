/*

 */

// include the servo library
#include <Servo.h>
#include <Button.h>

Servo strikeServo;  // create a servo object 

//Instantiate Button on digital pin 2
//pressed = ground (i.e. pulled high with external resistor)
Button startButton = Button(2, LOW);

const int timeKnobPin = A0;
const int servoPin = 9; 

unsigned long timeKnobVal;
unsigned long knobMaxVar = 1023;
unsigned long knobMinVar = 0;
const int unsigned maxTimeVar = 10 * 60000; //10 minutes
const int  unsigned minTimeVar = 1 * 60000; //1 minute


 unsigned long currentTime = 0;
 unsigned long startTime = 0;
 unsigned long endTime = 0;

boolean boing = true;


void setup() {
  strikeServo.attach(servoPin); 
  Serial.begin(9600); 
  startTime = millis();
  
}

void loop() {
  startButton.listen();
  currentTime = millis();

  if (startButton.onRelease()){
    Serial.println("released");
    setTimer();
  }


  if (currentTime > endTime) {
    if (boing) {
      strikeServo.write(90);
      boing = false;
      endTime = currentTime + 100; 
    } 
    else {
      strikeServo.write(0);
      setTimer();
      boing = true;
    }
  }
}


void setTimer() {
  timeKnobVal = analogRead(timeKnobPin);
  Serial.print("\ttimeKnobVal: ");
  Serial.print(timeKnobVal);
  startTime = millis();
  //the map() function was't treating my big numbers correctly so I went back to the equation.
  unsigned long  waitTime = ((timeKnobVal-knobMinVar)*(knobMaxVar-knobMinVar)/(maxTimeVar-minTimeVar)) + minTimeVar;
  endTime = startTime + waitTime;

  Serial.print("\t wait time: ");
  Serial.print(waitTime);
}



