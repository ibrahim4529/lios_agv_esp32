#ifndef MICROROS_COMMUNICATION
#define MICROROS_COMMUNICATION

#include "motor.hpp"
#include <micro_ros_platformio.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <std_msgs/msg/string.h>
#include <geometry_msgs/msg/twist.h>
#include <pwm_messages/msg/pwm.h>

class MicroRosCommunication {
  public:
    MicroRosCommunication();
    void init();
    void setup_subscription();
    void setup_publisher();
    void setup_executor();
    void spin();
    static void pwm_sub_cb(const void * msgin);

};
#endif //MICROROS_COMMUNICATION
