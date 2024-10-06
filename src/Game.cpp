
#include <iostream>

#include <SDL2/SDL.h>

#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include "imgui.h"

#include "Game.h"
#include "SetupUtils.h"
#include "FileHandler.h"

Game::Game() {
  if (!SDLUtils::SetupSDL(window, renderer)) {
    std::cout << "Game couldn't start, SDL Failed!\n";
  }

  // Setup Dear ImGui
  io = ImGuiUtils::SetupImGui(window, renderer);
  viewport = ImGui::GetMainViewport();
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  Width = DM.w / 1.5;
  Height = DM.h / 1.5;
  MainGuiSize = {Width / 3.0f, (float)Height};
  MainGuiPos = {Width - MainGuiSize.x, 0};
}

void Game::Run() {
  bool resize = true;
  while (runApp) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        runApp = false;
      if (event.type == SDL_WINDOWEVENT &&
          event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(window))
        runApp = false;
    }
    if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED) {
      SDL_Delay(10);
      continue;
    }
    ImGuiUtils::ImGuiStartFrame();

    // ImGui::ShowDemoWindow();
    if (resize) {
      ImGui::SetNextWindowPos(MainGuiPos);
      ImGui::SetNextWindowSize(MainGuiSize);
      resize = false;
    }
    RunMainGui();
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize(
        {(float)(Width - MainGuiSize.x), (float)(Height / 2.0f)});
    DisplayFileGui();

    // Rendering
    ImGui::Render();
    SDLUtils::FinishSDLFrame(window, renderer, clear_color, io);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
  }
  AddError("Path does not exist!");
}

void Game::RunMainGui() {
  // ImGui::SetNextWindowPos(MainGuiPos);
  {
    ImGui::Begin("Main GUI", nullptr, ImGuiWindowFlags_NoMove);
    ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", GUIError.c_str());
    MainGuiSize = ImGui::GetWindowSize();
    ImGui::SetNextItemWidth(MainGuiSize.x / 1.25);
    ImGui::InputText("path", path, 256);
    if (ImGui::IsItemActive()) {
      if (FileHandler::CheckPath(path)) {
        RemoveError("This path does not exist!");
      }
      else{
        AddError("This path does not exist!");
      }
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip("Specify path to lua file");
    }

    if (ImGui::Button("Click this to close the app",
                      {(float)(MainGuiSize.x / 1.25), 20})) {
      runApp = false;
    }
    ImGui::End();
  }
}

void Game::DisplayFileGui() {
  // ImGui::SetNextWindowPos({0,0});
  ImGui::Begin("Text Window", nullptr, ImGuiWindowFlags_NoResize);
  ImGui::LogToClipboard();
  // Display Text her
  ImGui::End();
}

void Game::AddError(std::string _error) {
  if (!errorStack.empty()) {
    if (errorStack.top() != _error) {
      errorStack.push(_error);
      GUIError = errorStack.top();
    }
  } else {
    errorStack.push(_error);
    GUIError = errorStack.top();
  }
}
// returns the error removed
bool Game::RemoveError(const std::string &_input) {
  if (errorStack.empty()) {
    return false;
  } else if (errorStack.top() != _input) {
    GUIError = errorStack.top();
    return false;
  } else {
    errorStack.pop();
    if (!errorStack.empty()) {
      GUIError = errorStack.top();
    }
    return true;
  }
}
