#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>
class Motor
{
public:
  Motor(int lpwm, int rpwm);
  void setup();
  void setSpeed(int speed, int direction);

private:
  int m_lpwm;
  int m_rpwm;
};

#endif  // MOTOR_HPP