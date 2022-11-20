#include "WaterLevelSensor.h"
#include <Arduino.h>

/*Speed of sound in a 20°C environment */
const double SOUND_SPEED = 331.45 + 0.62*20; 

WaterLevelSensor::WaterLevelSensor(int trigPin, int echoPin){
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float WaterLevelSensor::getDistance(){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(3);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    
    long time_micros = pulseInLong(echoPin, HIGH);
    return (time_micros/(2.0*1000000.0))*SOUND_SPEED;
}