#ifndef __UTIL__
#define __UTIL__

#include "Arduino.h"

bool isNumber(String str){
    if(str.length() == 0){
        return false;
    }
    for(unsigned int i=0;i<str.length();i++){
        if(!isDigit(str.charAt(i))) return false;
    }
    return true;
}

#endif