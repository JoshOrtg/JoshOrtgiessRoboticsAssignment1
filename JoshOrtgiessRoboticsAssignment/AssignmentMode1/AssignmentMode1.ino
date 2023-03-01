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
char action;

uint16_t blackThreshold = 300;

void setup() 
{
  Serial.begin(9600);
  proxSensors.initFrontSensor();
  lineSensors.initFiveSensors();
  Serial.println("Code Initiated");
}

void loop()
{
  proxSensors.read();
  lineSensors.read(sensors);

  for (int i = 0; i < 5; i++) 
  {
    Serial.print("Line sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(sensors[i]);
    Serial.print("\t");
  }

  //Stores value of line sensors as a variable everytime the program loops.
  uint16_t leftLineValue = sensors[0];
  uint16_t rightLineValue = sensors[4];
  uint16_t centerLineValue = sensors[2];
  
  //stores the values of the proximity sensors.
  uint8_t leftProxValue = proxSensors.countsFrontWithLeftLeds();
  uint8_t rightProxValue = proxSensors.countsFrontWithRightLeds();

  Serial.print("Left prox: ");
  Serial.print(leftProxValue);
  Serial.print(" Right prox: ");
  Serial.print(rightProxValue);
  Serial.print(" leftLineValue: ");
  Serial.print(leftLineValue);
  Serial.print("\t");
  Serial.println();
  
  if(leftProxValue && rightProxValue >= 6)
  {
    buzzer.playFrequency(500, 250, 12);
    Serial.print("Object Detected!");
  }

  if(Serial.available() > 0)
  {
    action = Serial.read();

    switch (action)
    {
      //MODE 1 FORWARD
      case 'w':
        motors.setSpeeds(100,100);
        delay(50);
        break; 

      //MODE 1 STOP
      case 's':
        motors.setSpeeds(-100, -100);
        delay(50);
        break;  
      
      //MODE 1 LEFT
      case 'a':
        motors.setSpeeds(-100, 100);
        delay(50);
        break;   

      //MODE 1 RIGHT
      case 'd':
        motors.setSpeeds(100, -100);
        delay(50);
        break;

      //STOP ALL MODES
      case 'x':
        motors.setSpeeds(0, 0);
        delay(10);
        break;          

      //DEFAULT 
      default:
        motors.setSpeeds(0, 0);
        delay(10);
    }
    //delay(500);
  }    
  }




