#include "processor.h"
#include "linux_parser.h"

float Processor::Utilization() { 
  long curr_total = LinuxParser::Jiffies();
  long curr_active = LinuxParser::ActiveJiffies();
  float cpu_utiliz = (curr_active - last_act_jiffies_)/(float)(curr_total - last_tot_jiffies_);
  last_act_jiffies_ = curr_active;
  last_tot_jiffies_ = curr_total;
  return cpu_utiliz;
}