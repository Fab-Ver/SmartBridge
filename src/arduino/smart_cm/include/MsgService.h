#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"

class Msg {
  private:
    String content;

  public:
    Msg(String content){
      this->content = content;
    }
  
    String getContent() const{
      return content;
    }
};

class MsgServiceClass {
  public: 
  
    Msg* currentMsg;
    bool msgAvailable;

    void init();  

    bool isMsgAvailable();
    Msg* receiveMsg();
  
    void sendMsg(const Msg& msg);
    void sendMsg(const String& msg);
};

extern MsgServiceClass MsgService;

#endif