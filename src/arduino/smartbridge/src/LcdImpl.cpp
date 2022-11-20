#include "LiquidCrystal_I2C.h"
#include "LcdImpl.h"
#include <Arduino.h>

LcdImpl::LcdImpl(){
    lcd.init();
    lcd.backlight();
}

void LcdImpl::on(){
    lcd.display();
}

void LcdImpl::off(){
    lcd.noDisplay();
}

void LcdImpl::writePreAlarm(String msg, int waterLevel){
    lcd.clear();
    lcd.print(msg);
    lcd.setCursor(1,0);
    lcd.print("Water Lev:" + (String) waterLevel);
}

void LcdImpl::writeAlarm(String msg, int waterLevel, int angle){
    lcd.clear();
    lcd.print(msg);
    lcd.setCursor(1,0);
    lcd.print("Water Lev:" + (String) waterLevel);
    lcd.setCursor(2,0);
    lcd.print("Valve's angle:" + (String) angle);
};