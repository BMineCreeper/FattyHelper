#include <SDL2/SDL.h>
#include <iostream>
//  IMGUI HEADERS TIME 
#include "imgui.h"
#include "imgui/backends/imgui_impl_sdlrenderer2.h"
#include "imgui/backends/imgui_impl_sdl2.h"

bool runApp = true;

int main(){

  if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_TIMER || SDL_INIT_GAMECONTROLLER) != 0){
    std::cout << "Welp, it looks like SDL failed to initialize.\n";
  }
  
  while(runApp){

  }
}
