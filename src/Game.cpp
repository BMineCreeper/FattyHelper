
#include <iostream>

#include <SDL2/SDL.h>

#include "imgui.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include "backends/imgui_impl_sdl2.h"

#include "Game.h"
#include "SetupUtils.h"

Game::Game()
{
    if(!SDLUtils::SetupSDL(window,renderer))
    {
        std::cout << "Game couldn't start, SDL Failed!\n";
    }

    //Setup Dear ImGui
    io = ImGuiUtils::SetupImGui(window,renderer);
    viewport = ImGui::GetMainViewport();
}

void Game::Run()
{
    ImGui::SetNextWindowSize({MainGuiSize});
    while(runApp){
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                runApp = false;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                runApp = false;
        }
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            continue;
        }
        ImGuiUtils::ImGuiStartFrame();
        
        RunMainGui();
        
        // Rendering
        ImGui::Render();
        SDLUtils::FinishSDLFrame(window,renderer,clear_color,io);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
    }
    AddError("Path does not exist!");
}

void Game::RunMainGui()
{
    
    ImGui::SetNextWindowPos(MainGuiPos);
    {
        ImGui::Begin("Main GUI",nullptr,ImGuiWindowFlags_NoMove);
        MainGuiSize = ImGui::GetItemRectSize();
        //ImGui::Text("Specify a path leading to a .lua file");
        
        ImGui::TextColored(ImVec4(1,0,0,1), GUIError.c_str());
        
        ImGui::SetNextItemWidth(MainGuiSize.x/3);
        ImGui::InputText("path",fileHandler.FilePath,256);
        if (ImGui::IsItemActive()) {
            fileHandler.CheckPath(fileHandler.FilePath);
        }
        if(ImGui::Button("Click this to close the app",{MainGuiSize.x/3,20}))
        {
            runApp = false;
        }
        ImGui::End();          
    }
}

void Game::DisplayFileGui()
{
    
}

void Game::AddError(std::string _error)
{
    if(!errorStack.empty())
    {
        if(errorStack.top() != _error)
        {
            errorStack.push(_error);
            GUIError = errorStack.top();
        }
    }else
    {
        errorStack.push(_error);
        GUIError = errorStack.top();
    }
}
//returns the error removed
bool Game::RemoveError(const std::string& _input)
{
    if(errorStack.empty())
    {
        return false;
    }else if(errorStack.top() != _input)
    {
        GUIError = errorStack.top();
        return false;
    }else
    {
        errorStack.pop();
        if(!errorStack.empty())
        {
            GUIError = errorStack.top();
        }
        return true;
    }
}