#pragma once
#include <chrono>

namespace Utils {
class Timer {
public:
  Timer();
  ~Timer();
private:
  std::chrono::high_resolution_clock::time_point starttime;
  std::chrono::high_resolution_clock::time_point endtime;  
};
} // namespace utils
