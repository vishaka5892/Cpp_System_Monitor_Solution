#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(const int &pid) : pid_(pid) {}

// DONE: Return this process's ID
int Process::Pid() { 
    return pid_; }

// DONE: Return this process's CPU utilization
float Process::CpuUtilization() { return cpu_utils_; }

// Update this process CPU utilization
void Process::UpdateProcVar() {
  user_ = LinuxParser::User(pid_);
  command_ = LinuxParser::Command(pid_);
  ram_= LinuxParser::Ram(pid_);
  uptime_ = LinuxParser::UpTime(pid_);
  long active_time = LinuxParser::ActiveJiffies(pid_);
  double active_time_second = (float)active_time / sysconf(_SC_CLK_TCK);
  if (uptime_ > 0){
    cpu_utils_ = active_time_second/uptime_;
  }
  else {
    cpu_utils_ = 0.0;
  }
}
// DONE: Return the command that generated this process
string Process::Command() { return command_; }

// DONE: Return this process's memory utilization
string Process::Ram() { return ram_; }

// DONE: Return the user (name) that generated this process
string Process::User() { return user_; }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { return uptime_; }

// DONE: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 
    bool res = cpu_utils_ > a.cpu_utils_;
    return res; }

