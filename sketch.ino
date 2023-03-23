//================================================== Imports
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

#include "Arms.h"
#include "Screen.h"
#include "Motor.h"

//===================================================== Pins
#define encoderButtonPin 8
#define encoderAPin 7 // dt
#define encoderBPin 6 // clk

//================================================ Variables
int aState = HIGH;
int bState = HIGH;
int aLast = HIGH;
bool encoderButtonState = false;
bool encoderButtonLast = false;

int currentSetting = 0;
int lastSetting = 0;

bool edition = false;
int rotaryState = 0;

unsigned long lastTime = 0;
unsigned long time = 0;
int mode;

bool motorState = false;
float motorSpeed = 30;
float armsLength = 5;

//================================================== Classes
LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo leftServo;
Servo rightServo;
Servo ESC;

Arms arms(leftServo, rightServo);
Motor motor(ESC);
Screen screen(lcd);

//=================================================== Sketch
void setup()
{
  Serial.begin(9600);
  Serial.println("Initialize system ...");

  pinMode(encoderAPin, INPUT_PULLUP);
  pinMode(encoderBPin, INPUT_PULLUP);
  pinMode(encoderButtonPin, INPUT_PULLUP);

  arms.init();
  motor.init();
  screen.init();

  Serial.println(cos(90));
  Serial.println(degrees(acos(0.5)));
}

void loop()
{
  // Read button state
  encoderButtonState = digitalRead(encoderButtonPin);
  if (encoderButtonState && !encoderButtonLast)
  {
    encoderButtonLast = encoderButtonState;
  }
  else if (!encoderButtonState && encoderButtonLast)
  {
    encoderButtonLast = encoderButtonState;
    updateMenuState();
  }

  // Read encoder movements (+1 or -1)
  aState = digitalRead(encoderAPin);
  if (aState != aLast)
  {
    aLast = aState;
    bState = digitalRead(encoderBPin);
    if (aState == LOW && bState == LOW)
    {
      aState = HIGH;
      rotaryState = 1;
      updateSetting();
    }
    if (aState == LOW && bState == HIGH)
    {
      aState = HIGH;
      rotaryState = -1;
      updateSetting();
    }
  }
  else
  {
    rotaryState = 0;
  }
}

void updateMenuState()
{
  edition = !edition;
  screen.setMenuState(currentSetting, edition);

  if (!edition)
  {
    if (currentSetting == 0)
    {
      motor.changeMotorState(motorState, motorSpeed);
    }
    else if (currentSetting == 1)
    {
      motor.changeMotorState(motorState, motorSpeed);
    }
    else if (currentSetting == 2)
    {
      arms.setArmsDistance(armsLength);
    }
  }
}

void updateSetting()
{
  if (edition) // modification du paramètre choisi
  {
    time = millis();
    // fast
    if (time - lastTime < 100)
    {
      mode = 1;
    }

    // medium
    else if (time - lastTime < 500)
    {
      mode = 2;
    }

    // slow
    else if (time - lastTime > 500)
    {
      mode = 3;
    }
    lastTime = time;

    if (currentSetting == 0)
    {
      motorState = !motorState;
      if (motorState)
      {
        screen.editCurrentSetting(currentSetting, "ON");
      }
      else
      {
        screen.editCurrentSetting(currentSetting, "OFF");
      }
    }
    else if (currentSetting == 1)
    {
      if (mode == 1)
      {
        motorSpeed = motorSpeed + 10 * rotaryState;
      }
      else if (mode == 2)
      {
        motorSpeed = motorSpeed + 5 * rotaryState;
      }
      else if (mode == 3)
      {
        motorSpeed = motorSpeed + 1 * rotaryState;
      }

      if (motorSpeed > 100)
      {
        motorSpeed = 100;
      }
      else if (motorSpeed < 0)
      {
        motorSpeed = 0;
      }

      String value = String(motorSpeed);
      value = value.substring(0, value.length() - 3);

      screen.editCurrentSetting(currentSetting, value);
    }
    else if (currentSetting == 2)
    {
      if (mode == 1)
      {
        armsLength = armsLength + 2 * rotaryState;
      }
      else if (mode == 2)
      {
        armsLength = armsLength + 0.5 * rotaryState;
      }
      else if (mode == 3)
      {
        armsLength = armsLength + 0.1 * rotaryState;
      }

      if (armsLength > 20)
      {
        armsLength = 20;
      }
      else if (armsLength < 1)
      {
        armsLength = 1;
      }

      String value = String(armsLength);
      value = value.substring(0, value.length() - 1);

      screen.editCurrentSetting(currentSetting, value);
    }
  }
  else // changement de paramètre
  {
    lastSetting = currentSetting;
    currentSetting += rotaryState;
    if (currentSetting > 2)
    {
      currentSetting = 0;
    }
    else if (currentSetting < 0)
    {
      currentSetting = 2;
    }

    screen.setCurrentSetting(currentSetting, lastSetting);
  }
}