#include <Wire.h>
#include <Zumo32U4.h>
#include <Keyboard.h>
#include <Zumo32U4Buzzer.h>

Zumo32U4Motors motors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4LineSensors lineSensors;
Zumo32U4Buzzer buzzer;
char action;

unsigned int sensors[5];
bool turningRight = false;
bool turningLeft = false;
uint16_t turnSpeed=100;

uint16_t blackThreshold = 300;

void setup()
{
  Serial.begin(9600);
  ledGreen(1);
  proxSensors.initFrontSensor();
  lineSensors.initFiveSensors();
  Serial.println("Code Initiated");
}

void loop()
{
  //Stores value of line sensors as a variable everytime the program loops.
  uint16_t leftLineValue = sensors[0];
  uint16_t rightLineValue = sensors[4];
  uint16_t centerLineValue = sensors[2];

  uint8_t leftProxValue = proxSensors.countsFrontWithLeftLeds();
  uint8_t rightProxValue = proxSensors.countsFrontWithRightLeds();

  if (Serial.available() > 0) 
  { 
    action = Serial.read();  

    switch (action)
    {
      case '2':
        // go forwards
        //CAUSES THE ROBOT TO HUG THE LEFT WALL.
        while(centerLineValue < blackThreshold)
        {
          motors.setSpeeds(100,0);
        }

        while(rightLineValue > blackThreshold)
        {
          motors.setSpeeds(0,100);
        }

        //TURNS THE ROBOT WHEN IT DRIVES TOWARDS A WALL
        while(rightLineValue && centerLineValue > blackThreshold)
        {
          motors.setSpeeds(0,0);
          delay(200);
        }

        //IF THE ROBOT FINDS A CUP(SURVIVOR) LOG IN THE CONSOLE AND TURN THE ROBOT AWAY FROM IT
        while(leftProxValue && rightProxValue >= 6)
        {
          buzzer.playFrequency(500, 250, 12);
          //delay(100);
          Serial.print("Object Detected!");
        }
        delay(100);
        break;      
      default:
        motors.setLeftSpeed(0);
        motors.setRightSpeed(0);
        ledYellow(0);
        ledRed(0);
        ledGreen(0);
        delay(100);
    }
    delay(500);
  }
}










