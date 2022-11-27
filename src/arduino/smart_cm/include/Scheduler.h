#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 4

class Scheduler {
  private:  
    int basePeriod;
    int nTasks;
    Task* taskList[MAX_TASKS];  

  public:
    /*
      Initialize scheduler period
    */
    void init(int basePeriod);  

    /*
      Add task to be scheduled.
    */
    virtual bool addTask(Task* task);  

    /*
      Execute the task in the taskList. 
    */
    virtual void schedule();
};

#endif