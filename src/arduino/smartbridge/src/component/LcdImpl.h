#ifndef __LCD_IMPL__
#define __LCD_IMPL__

#include "Lcd.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LcdImpl : public Lcd {
    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
    public:
        LcdImpl();
        void on();
        void off();
        void writePreAlarm(String msg, float waterLevel);
        void writeAlarm(String msg, float waterLevel, int angle);
};
#endif