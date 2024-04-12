#include "BFEArduinoRobotFramework.h"
#include <Arduino.h>

// 1: Links, 2: Rechts, 3: Rückwärts
int getNewDirection()
{
  servoController.setAngle(0);
  unsigned long distanceRight = sensorController.getDistance();

  servoController.setAngle(180);
  unsigned long distanceLeft = sensorController.getDistance();

  servoController.setAngle(90);

  if (distanceRight < 15 && distanceLeft < 15)
    return 3;
  if (distanceLeft >= distanceRight)
    return 1;
  return 2;
}

void setup()
{
  arduinoSetup();
  motorController.setDirection(motorController.FORWARD);
}

void loop()
{
  if (sensorController.getDistance() > 10)
    motorController.drive();
  else
  {
    motorController.setDirection(motorController.NONE);
    int newDirection = getNewDirection();
    if (newDirection == 1)
      motorController.leftTurn(90);
    else if (newDirection == 2)
      motorController.rightTurn(90);
    else if (newDirection == 3)
      motorController.rightTurn(180);
    delay(1000);
  }
}
