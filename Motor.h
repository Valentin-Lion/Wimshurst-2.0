#ifndef Motor_h
#define Motor_h

#define ESCPin 9

#include <Arduino.h>
#include <Servo.h>

class Motor
{
  public:
    Motor(Servo ESC) : _ESC(ESC) {}

    void init()
    {
      _ESC.attach(9);
      _ESC.write(0);
    }

    void changeMotorState(bool state,int speed)
    {
      if (state)
      {
        _ESC.write(map(speed, 0, 100, 1, 180));
      }
      else
      {
        _ESC.write(0);
      }
    }

    float speed = 0;

  private:
    Servo _ESC;
};

#endif