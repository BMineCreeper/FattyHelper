#include "Utils.h"
#include <chrono>
#include <iostream>
Utils::Timer::Timer() {
  starttime = std::chrono::high_resolution_clock::now();
}
Utils::Timer::~Timer() {
  endtime = std::chrono::high_resolution_clock::now();
  std::chrono::microseconds totaltime = std::chrono::duration_cast<std::chrono::microseconds>(endtime - starttime);
  std::cout << totaltime.count() << "\n";
}
