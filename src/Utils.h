#pragma once
#include <chrono>
#include "imgui.h"

namespace Utils {
class Timer {
public:
  Timer();
  ~Timer();
private:
  std::chrono::high_resolution_clock::time_point starttime;
  std::chrono::high_resolution_clock::time_point endtime;  
};

inline ImVec2 Vec2AtWindow(const ImVec2& _vec)
{
  ImVec2 wp = ImGui::GetWindowPos();
  return {_vec.x + wp.x, _vec.y + wp.y};
}
} // namespace utils
