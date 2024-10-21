#pragma once
#include "imgui.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
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

inline ImVec2 Vec2AtWindow(const ImVec2& _vec) {
  ImVec2 wp = ImGui::GetWindowPos();

  return {_vec.x + wp.x, _vec.y + wp.y};
}
inline ImVec2 Vec2WindowtoAbsolute(const ImVec2& _vec) {
  ImVec2 wp = ImGui::GetWindowPos();
  return {_vec.x - wp.x, _vec.y - wp.y};
}
// Overloaded version that takes an initial vec, and the pos of the window you want to render to, and puts it there
inline ImVec2 Vec2AtWindow(const ImVec2& _vec, const ImVec2& _wp) { return {_vec.x + _wp.x, _vec.y + _wp.y}; }

} // namespace Utils
namespace SDLUtils {
bool SetupSDL(SDL_Window*& _window, SDL_Renderer*& _renderer);
void FinishSDLFrame(SDL_Window*& _window, SDL_Renderer*& _renderer, ImVec4 _clear_color, ImGuiIO _io);
} // namespace SDLUtils
namespace ImGuiUtils {
ImGuiIO SetupImGui(SDL_Window*& _window, SDL_Renderer*& _renderer);
void ImGuiStartFrame();
void SetCustomImGuiStyle();
} // namespace ImGuiUtils
