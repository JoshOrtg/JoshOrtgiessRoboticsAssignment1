//ASSIGNMENT MODE 3 FULLY AUTONOMOUS MAZE NAVIGATION
#include <Wire.h>
#include <Zumo32U4.h>
#include <Keyboard.h>
#include <Zumo32U4Buzzer.h>

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4LineSensors lineSensors;
Zumo32U4Buzzer buzzer;

unsigned int sensors[5];
bool turningRight = false;
bool turningLeft = false;
uint16_t turnSpeed=100;

uint16_t blackThreshold = 300;

void setup() 
{
  proxSensors.initFrontSensor();
  lineSensors.initFiveSensors();
  Serial.println("Code Initiated");
}

void loop() 
{
  proxSensors.read();
  lineSensors.read(sensors);

  //Stores value of line sensors as a variable everytime the program loops.
  uint16_t leftLineValue = sensors[0];
  uint16_t rightLineValue = sensors[4];
  uint16_t centerLineValue = sensors[2];

  uint8_t leftProxValue = proxSensors.countsFrontWithLeftLeds();
  uint8_t rightProxValue = proxSensors.countsFrontWithRightLeds();

  delay(50);

  //CAUSES THE ROBOT TO HUG THE LEFT WALL.
  if(centerLineValue < blackThreshold)
  {
    motors.setSpeeds(150,0);
  }

  //TURNS THE ROBOT AWAY FROM THE BLACK LINE.
  if(rightLineValue > blackThreshold)
  {
    motors.setSpeeds(0,150);
  }

  //TURNS THE ROBOT WHEN IT DRIVES TOWARDS A WALL
  if(rightLineValue && centerLineValue > blackThreshold)
  {
    motors.setSpeeds(-250,100);
    delay(250);
  }

  //IF THE ROBOT FINDS A CUP(SURVIVOR) LOG IN THE CONSOLE AND TURN THE ROBOT AWAY FROM IT
  if(leftProxValue && rightProxValue >= 6)
  {
    buzzer.playFrequency(500, 250, 8);
    delay(200);
    Serial.print("\nPerson Detected!");
  }
}
