#pragma once
#include <imgui.h>
#include <SDL_render.h>

#include <iostream>
#include <stack>

#include "FileHandler.h"
#include "TextDisplay.h"

class Game
{
public:
    Game();
    void Run();
    void AddError(std::string _error);
    bool RemoveError(const std::string& _input);
private:
    void RunMainGui();
    void DisplayFileGui(TextDisplay& _textDisplay);
    ImVec4 clear_color{0.45f, 0.55f, 0.60f, 1.00f};
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    ImGuiIO io;
    ImGuiViewport* viewport;
    ImVec2 MainGuiSize{300,100};
    ImVec2 MainGuiPos{490,0};
    bool runApp = true;
    bool showError = true;
    bool validPath = false;
    std::string GUIError;
    std::stack<std::string> errorStack;
    FileHandler fileHandler{this};
    int Width;
    int Height;
};
