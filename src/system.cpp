#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
using std::ifstream;
using std::istringstream;

// DONE: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// DONE: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> pids = LinuxParser::Pids();
  processes_.clear();
  for (const int &i : pids){
    Process p(i);
    p.UpdateProcVar();
    processes_.push_back(p);
  }
  std::sort(processes_.begin(), processes_.end());
  return processes_;
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() { return kernel_; }
// DONE: Return the system's memory utilization
float System::MemoryUtilization() { return mem_util_; }

// DONE: Return the operating system name
std::string System::OperatingSystem() { return os_; }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { return running_procs_; }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { return total_procs_; }

// DONE: Return the number of seconds since the system started running
long int System::UpTime() { return uptime_; }

void System::Update() {
  kernel_ = LinuxParser::Kernel();
  mem_util_ = LinuxParser::MemoryUtilization();
  os_ = LinuxParser::OperatingSystem();
  running_procs_ = LinuxParser::RunningProcesses();
  total_procs_ = LinuxParser::TotalProcesses();
  uptime_ = LinuxParser::UpTime();
}