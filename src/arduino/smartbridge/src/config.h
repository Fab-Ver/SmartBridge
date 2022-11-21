#ifndef __CONFIG__
#define __CONFIG__

#define LA_PIN 0 
#define LB_PIN 0
#define LC_PIN 0
#define POT_PIN A0
#define PIR_PIN 0
#define PHORES_PIN 0 
#define TRIG_PIN 0
#define ECHO_PIN 0
#define SERVO_PIN 0
#define BUTTON_PIN 0

#define BLINK_PERIOD 0
#define SMART_LIGHT_PERIOD 0 
#define WATER_LEVEL_NORMAL_PERIOD 0 
#define WATER_LEVEL_PREALARM_PERIOD 0
#define WATER_LEVEL_ALARM_PERIOD 0

typedef enum State { LIGHT_ON, LIGHT_OFF, FSM_OFF} State;

#endif