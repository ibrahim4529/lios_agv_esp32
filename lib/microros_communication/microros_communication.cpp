#include "microros_communication.hpp"

rcl_subscription_t  pwm_sub;
rclc_executor_t executor;
rcl_node_t node;
rclc_support_t support;
rcl_allocator_t allocator;
pwm_messages__msg__Pwm pwm_msg;

Motor motor1(14, 27);
Motor motor2(13, 12);
Motor motor3(26, 25);
Motor motor4(33, 32);

#define RCCHECK(fn)                                                                                                    \
  {                                                                                                                    \
    rcl_ret_t temp_rc = fn;                                                                                            \
    if ((temp_rc != RCL_RET_OK))                                                                                       \
    {                                                                                                                  \
      error_loop();                                                                                                    \
    }                                                                                                                  \
  }
#define RCSOFTCHECK(fn)                                                                                                \
  {                                                                                                                    \
    rcl_ret_t temp_rc = fn;                                                                                            \
    if ((temp_rc != RCL_RET_OK))                                                                                       \
    {                                                                                                                  \
    }                                                                                                                  \
  }

void error_loop()
{
  while (1)
  {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(100);
  }
}

MicroRosCommunication::MicroRosCommunication()
{
}

void MicroRosCommunication::init()
{
  motor1.setup();
  motor2.setup();
  motor3.setup();
  motor4.setup();
  pinMode(LED_BUILTIN, OUTPUT);
  IPAddress ip(192, 168, 88, 234);
  size_t port = 8888;
  char wifi_ssid[] = "hanif-labs";
  char wifi_password[] = "hanifgan123";

  set_microros_wifi_transports(wifi_ssid, wifi_password, ip, port);
  delay(2000);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("Starting Micro-ROS agent");

  allocator = rcl_get_default_allocator();
  RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));

  RCCHECK(rclc_node_init_default(&node, "lios_agv", "", &support));
}

void MicroRosCommunication::setup_subscription()
{
  RCCHECK(rclc_subscription_init_default(&pwm_sub, &node, ROSIDL_GET_MSG_TYPE_SUPPORT(pwm_messages, msg, Pwm), "pwm"));
  pwm_msg.pwm1 = 0;
  pwm_msg.pwm2 = 0;
  pwm_msg.pwm3 = 0;
  pwm_msg.pwm4 = 0;
}

void MicroRosCommunication::setup_publisher()
{ 
  // define the publisher here
}

void MicroRosCommunication::setup_executor()
{
  RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator));
  RCCHECK(rclc_executor_add_subscription(&executor, &pwm_sub, &pwm_msg, &MicroRosCommunication::pwm_sub_cb, ON_NEW_DATA));
}

void MicroRosCommunication::spin()
{
  RCCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
  delay(100);
}

void MicroRosCommunication::pwm_sub_cb(const void *msgin)
{
  const pwm_messages__msg__Pwm *msg = (const pwm_messages__msg__Pwm *)msgin;

  motor1.setSpeed(msg->pwm1);
  motor2.setSpeed(msg->pwm2);
  motor3.setSpeed(msg->pwm3);
  motor4.setSpeed(msg->pwm4);
}
