#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include "imgui.h"

#include "Editor.h"

#include <imgui_internal.h>

#include "AttackHandler.h"
#include "FileHandler.h"
#include "SetupUtils.h"
#include "TextDisplay.h"

void DisplayFunctionMaker(AttackHandler &ah);

Editor::Editor() {
  if (!SDLUtils::SetupSDL(window, renderer)) {
    std::cout << "Editor couldn't start, SDL Failed!\n";
  }
  // Setup Dear ImGui
  io = ImGuiUtils::SetupImGui(window, renderer);
  viewport = ImGui::GetMainViewport();
  SDL_DisplayMode DM;
  SDL_GetCurrentDisplayMode(0, &DM);
  Width = DM.w / 1.25;
  Height = DM.h / 1.25;
  MainGuiSize = {Width / 3.0f, (float)Height};
  MainGuiPos = {Width - MainGuiSize.x, 0};
  SDL_Surface *image = IMG_Load("../CB.png");
  // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, image);
  // CopyTexture = texture;
  image = IMG_Load("../UH.png");
  if (image == nullptr) {
    AddError("Image not found!");
  } else {
    RemoveError("Image not found!");
  }
  sdlSprites.emplace_back(
      RenderSDLTexture{SDL_CreateTextureFromSurface(renderer, image)});
  SDL_FreeSurface(image);
  ImGuiUtils::SetCustomImGuiStyle();
  ah.Setup(renderer);
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
    ah.RenderSprites(sdlSprites, renderer);
    if (!ah.movementCurves.empty()) {
      // std::cout << "Rendering\n";
      ah.RenderBullets(renderer, ah.movementCurves[0],3);
    }
    // REMINDER FOR ME, you gotta put this bit after imgui::render, but you can
    // probably get the imgui window state and then use it here
    SDL_RenderPresent(renderer);
  }
  AddError("Path does not exist!");
}

void Editor::RunMainGui(bool &_displayfunctionmaker) {
  // ImGui::SetNextWindowPos(MainGuiPos);
  {
    ImGui::Begin("Main GUI", nullptr,
                 ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
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
      pd.AddCurve(&ah.movementCurves[0]);
    }
    if (ImGui::IsItemHovered()) {
      ImGui::SetTooltip("Create a Movement Function");
    }
    if (_displayfunctionmaker) {
      // Need some sort of int displaying which functioncurve needs to be edited
      DisplayFunctionMaker();
    }
    ImGui::End();
  }
}

void Editor::DisplayFileGui(bool &_log) {
  // ImGui::SetNextWindowPos({0,0});
  ImGui::Begin("Text Window", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
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
  ImGui::Begin("Attack Window", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
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
void Editor::DisplayFunctionMaker() {
  bool check = false;
  ImGui::SetNextWindowSize({1920,1080});
  ImGui::Begin("Create Function", nullptr,
              ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoResize);
  // Ask whether it should be a function or an ellipse
  // Pick two points, connect them with a chosen degree, modify the
  // constants ah.movementCurves[] = ImGui::GetMousePos();
  if (ImGui::Button("+")) {
    ah.AddMovementCurve();
  }
  if (ImGui::BeginListBox("Dollar box", {300, 17})) {
    check = true;
  }
  for (auto &movementCurve : ah.movementCurves) {
    ImGui::Selectable(movementCurve.CurveName.c_str());
  }
  if (check)
    ImGui::EndListBox();
  ImGui::SameLine();
  ImGui::SetNextItemWidth(ImGui::GetWindowSize().x / 3);
  ImGui::DragFloat("Speed", &ah.speed, 0.1f, 0.0f, 5.0f);
  ImGui::SameLine();
  char curvename[128] = " ";
  ImGui::InputText("Name", curvename, 128);
  ah.movementCurves[0].CurveName = curvename;
  // Do options for function show what the current function looks like
  ImGui::BeginChild("Function");
  ah.bulletWindowPosition = ImGui::GetWindowPos();
  ah.bulletWindowSize = ImGui::GetWindowSize();
  ImVec2 windowsize = ImGui::GetWindowSize();
  ImVec2 windowpos = ImGui::GetWindowPos();
  sdlSprites[0].destrect = {static_cast<int>(windowpos.x + windowsize.x / 2),
                            static_cast<int>(windowpos.y + windowsize.y / 2),
                            20, 20};
  sdlSprites[0].doRender = true;
  pd.DragPoints();
  pd.RenderPoints();
  if (ah.movementCurves.size() != 0) {
    ah.RenderCurrentCurve(ah.movementCurves[0]);
  }
  ImGui::EndChild();
  ImGui::End();
}
