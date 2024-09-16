#include "motor.hpp"

Motor::Motor(int lpwm, int rpwm)
{
  this->m_lpwm = lpwm;
  this->m_rpwm = rpwm;
}

void Motor::setup()
{
    pinMode(m_lpwm, OUTPUT);
    pinMode(m_rpwm, OUTPUT);

    analogWrite(m_lpwm, 0);
    analogWrite(m_rpwm, 0);
}

void Motor::setSpeed(int speed, int direction)
{
  if (direction == 0)
  {
    analogWrite(m_lpwm, speed);
    analogWrite(m_rpwm, 0);
  }
  else
  {
    analogWrite(m_lpwm, 0);
    analogWrite(m_rpwm, speed);
  }
}
