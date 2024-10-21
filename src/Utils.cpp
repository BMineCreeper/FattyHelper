#include "Utils.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include "imgui.h"
#include <chrono>
#include <iostream>
Utils::Timer::Timer() { starttime = std::chrono::high_resolution_clock::now(); }
Utils::Timer::~Timer() {
  endtime = std::chrono::high_resolution_clock::now();
  std::chrono::microseconds totaltime = std::chrono::duration_cast<std::chrono::microseconds>(endtime - starttime);
  std::cout << totaltime.count() << "\n";
}

void SDLUtils::FinishSDLFrame(SDL_Window*& _window, SDL_Renderer*& _renderer, ImVec4 _clear_color, ImGuiIO _io) {
  SDL_RenderSetScale(_renderer, _io.DisplayFramebufferScale.x, _io.DisplayFramebufferScale.y);
  SDL_SetRenderDrawColor(_renderer, (Uint8)(_clear_color.x * 255), (Uint8)(_clear_color.y * 255), (Uint8)(_clear_color.z * 255), (Uint8)(_clear_color.w * 255));
  SDL_RenderClear(_renderer);
}
bool SDLUtils::SetupSDL(SDL_Window*& _window, SDL_Renderer*& _renderer) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
    std::cout << "init error";
    return false;
  }
  if ((!IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG) {
    std::cout << "init img error";
    return false;
  }
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  int Width = 1536;
  int Height = 864;
  _window = SDL_CreateWindow("Fatty Helper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_ALLOW_HIGHDPI);
  _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (_window == nullptr) {
    std::cout << "window error";
    return false;
  }
  if (_renderer == nullptr) {
    std::cout << "renderer error";
    return false;
  }

  SDL_SetWindowResizable(_window, SDL_TRUE);
  SDL_RendererInfo info;
  SDL_GetRendererInfo(_renderer, &info);
  SDL_Log("Current SDL_Renderer: %s", info.name);
  return true;
}
ImGuiIO ImGuiUtils::SetupImGui(SDL_Window*& _window, SDL_Renderer*& _renderer) {
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForSDLRenderer(_window, _renderer);
  ImGui_ImplSDLRenderer2_Init(_renderer);
  return io;
}
void ImGuiUtils::ImGuiStartFrame() {
  ImGui_ImplSDLRenderer2_NewFrame();
  ImGui_ImplSDL2_NewFrame();
  ImGui::NewFrame();
}
void ImGuiUtils::SetCustomImGuiStyle() {
  ImGuiStyle& style = ImGui::GetStyle();
  ImVec4* colors = style.Colors;

  // General settings
  style.WindowRounding = 5.0f;    // Rounding for windows
  style.FrameRounding = 4.0f;     // Rounding for frames
  style.ScrollbarRounding = 4.0f; // Rounding for scrollbars
  style.GrabRounding = 4.0f;      // Rounding for grab
  style.TabRounding = 4.0f;       // Rounding for tabs
  style.WindowBorderSize = 1.0f;
  style.FrameBorderSize = 1.0f;
  style.PopupBorderSize = 1.0f;
  style.GrabMinSize = 20.0f; // Size of grab handles

  // Color settings
  colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f); // Dark background
  colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.16f, 0.17f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
  colors[ImGuiCol_Border] = ImVec4(0.30f, 0.30f, 0.30f, 0.65f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.21f, 0.22f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.75f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.18f, 0.20f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.14f, 0.15f, 1.00f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.16f, 0.17f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.20f, 0.70f, 0.30f, 1.00f);        // Green accent
  colors[ImGuiCol_SliderGrab] = ImVec4(0.20f, 0.70f, 0.30f, 1.00f);       // Green accent
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 0.80f, 0.35f, 1.00f); // Brighter when active
  colors[ImGuiCol_Button] = ImVec4(0.20f, 0.70f, 0.30f, 0.60f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.80f, 0.35f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.60f, 0.25f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.20f, 0.70f, 0.30f, 0.70f); // Green for headers
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.80f, 0.35f, 0.80f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.15f, 0.60f, 0.25f, 1.00f);
  colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 1.00f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.78f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.20f, 0.70f, 0.30f, 0.60f); // Subtle green for resize grips
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 0.80f, 0.35f, 0.80f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.15f, 0.60f, 0.25f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.28f, 0.28f, 0.30f, 1.00f);
  colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.70f, 0.30f, 1.00f); // Active tabs greenish
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.18f, 0.18f, 0.19f, 1.00f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.70f, 0.30f, 1.00f);
  // colors[ImGuiCol_DockingPreview]         = ImVec4(0.20f, 0.70f, 0.30f, 0.70f); // Docking preview color
  colors[ImGuiCol_NavHighlight] = colors[ImGuiCol_HeaderHovered];              // Highlight color for keyboard navigation
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f); // White highlight for windowing
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);     // Dim background for windowing
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);      // Dim background for modals
}
