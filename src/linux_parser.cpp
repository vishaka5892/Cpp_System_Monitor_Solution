#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;
using std::istringstream;
using std::ifstream;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  ifstream meminfo_file (kProcDirectory + kMeminfoFilename);
  string line, key, units;
  long memory;
  long mem_total, mem_free;
  if (meminfo_file.is_open()){
    while (getline(meminfo_file, line)){
      istringstream linestream (line);
      while (linestream >> key >> memory >> units){ 
        if (key == "MemTotal:"){
          mem_total = memory;
        }
        else if (key == "MemFree:"){
          mem_free = memory;
          float x = (1.0 * (mem_total - mem_free)/mem_total);
          return x;
        }
      }
    }
  }
  return 0.0;
}

// DONE: Read and return the system uptime
long LinuxParser::UpTime() {
  ifstream uptime_file (kProcDirectory + kUptimeFilename);
  string line;
  long uptime = 0;
  if (uptime_file.is_open()){
    if (getline(uptime_file, line)){
      std::replace (line.begin(), line.end(), '.', ' ');
      istringstream linestream (line);
      linestream >> uptime;
      return uptime;
    }
  }
  return uptime;
}

// DONE: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  vector<string> tick = LinuxParser::CpuUtilization();
  long jiffies = 0;
  for (int state = kUser_; state <=kSteal_; state++){
    jiffies += stol(tick[state]);
  }
  return jiffies;
}

// DONE: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
ifstream process_stat_file (kProcDirectory + to_string(pid) + kStatFilename);
  string line, str;
  long active_time = 0;
  if (process_stat_file.is_open()){
    if (getline(process_stat_file,line)){
      istringstream linestream (line);
      int count = 0;
      while(linestream >> str){
        if (count >= 13 && count <= 16){
          active_time += stol(str);
        }
        else if (count >= 17) {
          break;
        }
        count++;
      }
    }
  }
  return active_time;  
}//  return 0; }

// DONE: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {
   
   return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { return 0; }

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { return 0; }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid[[maybe_unused]]) { return string(); }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) { return 0; }