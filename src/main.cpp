#include <Arduino.h>
#include "microros_communication.hpp"

MicroRosCommunication rosagent;

void setup()
{
  rosagent.init();
  rosagent.setup_subscription();
  rosagent.setup_executor();
}

void loop()
{
  rosagent.spin();
}
