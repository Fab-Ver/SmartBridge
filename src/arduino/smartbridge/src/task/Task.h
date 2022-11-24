#ifndef __TASK__
#define __TASK__

class Task {
  private:
    int period;
    int timeElapsed;
    bool active;
  
  public:
    /*
      Initialize the task period.
    */
    virtual void init(int period){
      this->period = period;  
      timeElapsed = 0;
    }

    /*
      Execute different action according to the actual implemetation.
    */
    virtual void tick() = 0;

    /*
      Check if the scheduler can execute the task. 
    */
    bool updateAndCheckTime(int basePeriod){
      timeElapsed += basePeriod;
      if (timeElapsed >= period){
        timeElapsed = 0;
        return true;
      } else {
        return false; 
      }
    }

    /*
      Return true if the task is active, false otherwise. 
    */
    bool isActive(){
      return active;
    }

    /*
      Change the task activity status. 
    */
    void setActive(bool active){
      this->active = active;
    }

    /*
      Change task period according to the given argument. 
    */
    void setPeriod(int period){
      this->period = period;
    }

    /*
      Perform different action on the task status depending on the actual implementation. 
    */
    virtual void updateState() = 0;
  
};

#endif