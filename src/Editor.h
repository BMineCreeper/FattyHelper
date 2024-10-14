#pragma once
#include <imgui.h>
#include <SDL2/SDL_render.h>
#include <string>
#include <stack>
#include "AttackHandler.h"
#include "PointDragger.h"

class Editor
{
public:
    Editor();
    void Run();
    void AddError(std::string _error);
    bool RemoveError(const std::string& _input);
private:
    void RunMainGui(bool& _displayfunctionmaker);
    void DisplayFileGui(bool& _log);
    void DisplayAttackGui();
    void DisplayFunctionMaker();
    PointDragger pd;
    ImGuiIO io;
    ImGuiViewport* viewport;
    ImVec2 MainGuiSize{300,100};
    ImVec2 MainGuiPos{490,0};
    ImVec4 clear_color{0.45f, 0.55f, 0.60f, 1.00f};
    ImDrawList* AttackBoxDrawList;
    ImTextureID CopyTexture = nullptr;
    RenderSDLTexture AttackBoxTexture;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool runApp = true;
    bool showError = true;
    bool validPath = false; 
    char path[256] = "";
    std::string GUIError;
    std::stack<std::string> errorStack;
    std::vector<RenderSDLTexture> sdlSprites;
    AttackHandler ah;
    int Width;
    int Height;
};
