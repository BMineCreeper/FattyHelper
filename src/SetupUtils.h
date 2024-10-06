#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include "imgui.h"
#include "backends/imgui_impl_sdlrenderer2.h"
#include "backends/imgui_impl_sdl2.h"
namespace SDLUtils
{
    bool SetupSDL(SDL_Window*& _window, SDL_Renderer*& _renderer)
    {
        if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
        {
            std::cout << "init error";
            return false;
        }
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        int Width = DM.w;
        int Height = DM.h;
        _window = SDL_CreateWindow("Fatty Helper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width/1.5, Height/1.5, SDL_WINDOW_ALLOW_HIGHDPI);
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
        if(_window == nullptr){
            std::cout << "window error";
            return false;
        }
        if(_renderer == nullptr){
            std::cout << "renderer error";
            return false;
        }

        SDL_SetWindowResizable(_window,SDL_TRUE);
        SDL_RendererInfo info;
        SDL_GetRendererInfo(_renderer, &info);
        SDL_Log("Current SDL_Renderer: %s", info.name);
        return true;
    }

    void FinishSDLFrame(SDL_Window*& _window, SDL_Renderer*& _renderer, ImVec4 _clear_color,ImGuiIO _io)
    {
        SDL_RenderSetScale(_renderer, _io.DisplayFramebufferScale.x, _io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(_renderer, (Uint8)(_clear_color.x * 255), (Uint8)(_clear_color.y * 255), (Uint8)(_clear_color.z * 255), (Uint8)(_clear_color.w * 255));
        SDL_RenderClear(_renderer);
    }
}

namespace ImGuiUtils
{
    //Always succeeds
    ImGuiIO SetupImGui(SDL_Window*& _window, SDL_Renderer*& _renderer)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForSDLRenderer(_window, _renderer);
        ImGui_ImplSDLRenderer2_Init(_renderer);
        return io;
    }

    inline void ImGuiStartFrame()
    {
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }
}
