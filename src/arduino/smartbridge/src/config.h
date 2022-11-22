#ifndef __CONFIG__
#define __CONFIG__

#define LA_PIN 12
#define LB_PIN 13
#define LC_PIN 8
#define POT_PIN A0
#define PIR_PIN 2
#define PHORES_PIN A1
#define TRIG_PIN 6
#define ECHO_PIN 5
#define SERVO_PIN 4
#define BUTTON_PIN 7

#define BLINK_PERIOD 0
#define SMART_LIGHT_PERIOD 0 
#define WATER_LEVEL_NORMAL_PERIOD 0 
#define WATER_LEVEL_PREALARM_PERIOD 0
#define WATER_LEVEL_ALARM_PERIOD 0

typedef enum State {LIGHT_ON, LIGHT_OFF, FSM_OFF} State;

#endif