#pragma once
#include <imgui.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <stack>

class Game
{
public:
    Game();
    void Run();
    void AddError(std::string _error);
    bool RemoveError(const std::string& _input);
private:
    void RunMainGui();
    void DisplayFileGui();
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
    char path[256];
    std::string GUIError;
    std::stack<std::string> errorStack;
    int Width;
    int Height;
};
