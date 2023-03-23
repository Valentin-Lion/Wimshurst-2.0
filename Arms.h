#ifndef Arms_h
#define Arms_h

#define leftServoPin 11
#define rightServoPin 10

#include <Arduino.h>
#include <Servo.h>

class Arms
{
  public:
    Arms(Servo leftServo, Servo rightServo)
    {
      _leftServo = leftServo;
      _rightServo = rightServo;
    }

    void init()
    {
      _leftServo.attach(leftServoPin);
      _leftServo.write(120);

      _rightServo.attach(rightServoPin);
      _rightServo.write(60);
    }
    
    void setArmsDistance(float length)
    {
      int a = int(degrees(acos((10 - length) / (2 * 5))));
      _leftServo.write(180-a);
      _rightServo.write(a);
    }

  private:
    Servo _leftServo;
    Servo _rightServo;
};

#endif