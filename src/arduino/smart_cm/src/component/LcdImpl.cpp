#include "LcdImpl.h"

LcdImpl::LcdImpl(){
    lcd.init();
}

void LcdImpl::on(){
    lcd.display();
    lcd.backlight();
}

void LcdImpl::off(){
    lcd.noDisplay();
    lcd.noBacklight();
}

void LcdImpl::writePreAlarm(String msg, float waterLevel){
    lcd.clear();
    lcd.print(msg);
    lcd.setCursor(0,1);
    lcd.print("Water Lev: " + (String) waterLevel + " m");
}

void LcdImpl::writeAlarm(String msg, float waterLevel, int angle){
    lcd.clear();
    lcd.print(msg);
    lcd.setCursor(0,1);
    lcd.print("Water Lev: " + (String) waterLevel + " m");
    lcd.setCursor(0,2);
    lcd.print("Valve's angle: " + (String) angle);
};