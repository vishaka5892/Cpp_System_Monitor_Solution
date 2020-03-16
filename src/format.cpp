#include <string>

#include "format.h"

using std::string;
using std::to_string;

// DONE: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  int hour, minute, second;
  string time {};
  hour = seconds/3600;
  second = (seconds % 3600);
  minute = second / 60;
  second = second % 60;
  time += ToString(hour) + ':' + ToString(minute) + ':' + ToString(second);
  return time;
}

string Format::ToString (int t){
  return (t < 10) ? ('0' + to_string(t)) : to_string(t);
}