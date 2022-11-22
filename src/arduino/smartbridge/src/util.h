#ifndef __UTIL__
#define __UTIL__

#include "Arduino.h"

bool isNumeric(String str){
    if(str.length() == 0){
        return false;
    }
    for(int i=0;i<str.length();i++){
        if(!isDigit(str.charAt(i))) return false;
    }
    return true;
}

#endif