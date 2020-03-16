#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // DONE: Declare any necessary private members
 private:
  long last_act_jiffies_ = 0; //store last value of active_jiffies
  long last_tot_jiffies_ = 0; //store last value of total_jiffies
};

#endif