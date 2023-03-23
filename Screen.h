#ifndef Screen_h
#define Screen_h

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

byte blank[8] = {
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000};

byte normal[8] = {
    B00000,
    B11111,
    B10001,
    B10001,
    B10001,
    B11111,
    B00000,
    B00000};

byte cursor[8] = {
    B00000,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B00000,
    B00000};

byte selected[8] = {
    B00000,
    B01110,
    B11111,
    B11111,
    B11111,
    B01110,
    B00000,
    B00000};

class Screen
{
public:
  String lines[4] = {
      "Motor       :   OFF",
      "Speed    (%):    30",
      "Length  (cm):   5.0",
      "Tension (kV):   NaN"};

  Screen(LiquidCrystal_I2C lcd) : _lcd(lcd) {}
  void init()
  {
    _lcd.init();
    _lcd.clear();
    _lcd.backlight();

    _lcd.createChar(0, normal);
    _lcd.createChar(1, cursor);
    _lcd.createChar(2, selected);
    _lcd.createChar(3, blank);

    _writeLine(0, 1);
    _writeLine(1, 0);
    _writeLine(2, 0);
    _writeLine(3, 3);
  }

  void setCurrentSetting(int currentSetting, int lastSetting)
  {
    _writeLine(lastSetting, 0);
    _writeLine(currentSetting, 1);
  }

  void setMenuState(int currentSetting, bool state)
  {
    if (state)
    {
      _writeLine(currentSetting, 2);
    }
    else
    {
      _writeLine(currentSetting, 1);
    }
  }

  void editCurrentSetting(int currentSetting, String value)
  {
    String setting = lines[currentSetting].substring(0, 14);
    for (int i = 0; i < 5 - value.length(); i++)
    {
      setting += " ";
    }
    setting += value;
    lines[currentSetting] = setting;
    _writeLine(currentSetting, 2);
  }

private:
  LiquidCrystal_I2C _lcd;

  void _writeLine(int row, int mode)
  {
    _lcd.setCursor(0, row);
    _lcd.write(mode);
    _lcd.print(lines[row]);
  }
};

#endif