#ifndef __TASK__
#define __TASK__

class Task {
private:
  int period;
  int timeElapsed;
  bool active;
  
public:
  virtual void init(int period){
    this->period = period;  
    timeElapsed = 0;
  }

  virtual void tick() = 0;

  bool updateAndCheckTime(int basePeriod){
    timeElapsed += basePeriod;
    if (timeElapsed >= period){
      timeElapsed = 0;
      return true;
    } else {
      return false; 
    }
  }

  bool isActive(){
    return active;
  }

  void setActive(bool active){
    this->active = active;
  }

  void setPeriod(int period){
    this->period = period;
  }
  
};

#endif