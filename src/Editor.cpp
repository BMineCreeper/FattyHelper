#include <algorithm>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string>

#include "AttackHandler.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include "imgui.h"

#include "Editor.h"
#include "FileHandler.h"
#include "SetupUtils.h"
#include "TextDisplay.h"

void DisplayFunctionMaker(AttackHandler &_ah);

Editor::Editor() {
  if (!SDLUtils::SetupSDL(window, renderer)) {
    std::cout << "Editor couldn't start, SDL Failed!\n";
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
  SDL_Surface *image = IMG_Load("../CB.png");
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  CopyTexture = texture;
  // image = IMG_Load()
  ImGuiUtils::SetCustomImGuiStyle();
}

void Editor::Run() {
  bool log = false;
  bool resize = true;
  bool displayFunctionMaker = false;
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
    RunMainGui(displayFunctionMaker);
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize(
        {(float)(Width - MainGuiSize.x), (float)(Height / 2.5f)});
    DisplayFileGui(log);
    ImGui::SetNextWindowPos({0, Height / 2.5f});
    ImGui::SetNextWindowSize(
        {(float)(Width - MainGuiSize.x), (float)(Height - (Height / 2.5))});
    DisplayAttackGui();

    // Rendering
    ImGui::Render();
    SDLUtils::FinishSDLFrame(window, renderer, clear_color, io);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    SDL_RenderPresent(renderer);
  }
  AddError("Path does not exist!");
}

void Editor::RunMainGui(bool &_displayfunctionmaker) {
  // ImGui::SetNextWindowPos(MainGuiPos);
  {
    ImGui::Begin("Main GUI", nullptr, ImGuiWindowFlags_NoMove);
    ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", GUIError.c_str());
    MainGuiSize = ImGui::GetWindowSize();
    ImGui::SetNextItemWidth(MainGuiSize.x / 1.25);
    ImGui::InputText("path", path, 256);
    if (ImGui::IsItemActive()) {
      if (FileHandler::CheckPath(path)) {
        RemoveError("Path does not exist.");
      } else {
        AddError("Path does not exist.");
      }
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip("Specify path to lua file");
    }
    if (ImGui::Button("Click this to close the app",
                      {(float)(MainGuiSize.x / 1.25), 20})) {
      runApp = false;
    }
    if (ImGui::Button("Open Function Maker Window")) {
      _displayfunctionmaker = true;
      ah.AddMovementCurve();
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip("Create a Movement Function");
    }
    if (_displayfunctionmaker) {
      // Need some sort of int displaying which functioncurve needs to be edited
      DisplayFunctionMaker(ah);
    }
    ImGui::End();
  }
}

void Editor::DisplayFileGui(bool &_log) {
  // ImGui::SetNextWindowPos({0,0});
  ImGui::Begin("Text Window", nullptr, ImGuiWindowFlags_NoResize);
  std::ifstream textfile = FileHandler::GetFile(path);
  if (_log == true) {
    ImGui::LogToClipboard();
  }
  TextDisplay::DisplayFromFile(textfile);
  ImGui::LogFinish();
  ImGui::SetCursorPosX(ImGui::GetCursorPosX() +
                       ImGui::GetContentRegionAvail().x - 50);
  if (ImGui::ImageButton("Copy Button", CopyTexture, ImVec2(50, 50))) {
    _log = true;
  } else {
    _log = false;
  }
  ImGui::End();
}

void Editor::DisplayAttackGui() {
  ImU32 col = ImColor(ImVec4(0.85, 0.26, 0.96, 1.0));
  ImGui::Begin("Attack Window", nullptr, ImGuiWindowFlags_NoResize);
  AttackBoxDrawList = ImGui::GetWindowDrawList();
  AttackBoxDrawList->AddCircle({400, 600}, 10, col, 32, 1.0f);
  // ImGui::Image();
  ImGui::End();
}

void Editor::AddError(std::string _error) {
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
// returns true if it was able to remove the error
bool Editor::RemoveError(const std::string &_input) {
  // std::cout << "Calling remove error!\n";
  if (errorStack.empty()) {
    // std::cout << "Empty\n";
    return false;
  } else if (errorStack.top() != _input) {
    // std::cout << "top does not equal input!\n";
    GUIError = errorStack.top();
    return false;
  } else {
    errorStack.pop();
    if (!errorStack.empty()) {
      GUIError = errorStack.top();
    } else {
      GUIError = "";
    }
    // std::cout << "Popped off the error\n";
    return true;
  }
}
void DisplayFunctionMaker(AttackHandler &_ah) {
  ImGui::Begin("Create Function");
  // Ask whether it should be a function or an ellipse
  // Pick two points, connect them with a chosen degree, modify the constants
  //_ah.movementCurves[] = ImGui::GetMousePos();
  if (ImGui::Button("+")) {
    _ah.AddMovementCurve();
  }
  ImGui::BeginListBox("Dollar box", {300, 17});
  for (int i = 0; i < _ah.movementCurves.size(); i++) {
    ImGui::Selectable(_ah.movementCurves[i].CurvePlainText.c_str());
  }
  ImGui::EndListBox();
  // Do options for function show what the current function looks like
  ImGui::BeginChild("Function");
  if (_ah.movementCurves.size() != 0) {
   //ah takes a window and renders lines on it 
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImGui::Image(,windowSize);
    _ah.RenderCurrentCurve(_ah.movementCurves[0]);
  }
  ImGui::EndChild();
  ImGui::End();
}
