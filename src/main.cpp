#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <iostream>
//  IMGUI HEADERS TIME 
#include "imgui.h"
#include "../imgui/backends/imgui_impl_sdlrenderer2.h"
#include "../imgui/backends/imgui_impl_sdl2.h"
//  My Includes
#include "BUtils.cpp"

bool runApp = true;

int main(){

  if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER || SDL_INIT_GAMECONTROLLER) != 0){
    std::cout << "Welp, it looks like SDL failed to initialize.\n";
  }
  SDL_Window* window = SDL_CreateWindow("Fatty Helper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_ALLOW_HIGHDPI);
  if(window == nullptr){
    std::cout << "SDL Failed to create a window!\n";
  }
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if(renderer == nullptr){
    std::cout << "SDL Failed to create a renderer!\n";
  }

  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  SDL_Log("Current SDL_Renderer: %s", info.name);
  
  //IMGUI CREATION
  
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer2_Init(renderer);
  

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  
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
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImVec2 MainGuiPos = {100,100};
        ImVec2 MainGuiSize = {100,100};
        ImGui::SetNextWindowPos(MainGuiPos);
        {
          ImGui::Begin("Main GUI",NULL,ImGuiWindowFlags_NoMove);
          ImGui::End();          
        }
        // Rendering
        //ImGui::ShowDemoWindow();
        ImGui::Render();
        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
        SDL_RenderPresent(renderer);
  }
}
