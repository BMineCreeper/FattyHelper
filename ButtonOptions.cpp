#include "ButtonOptions.h"
#include "imgui.h"
#include <iostream>
ButtonOptions::ButtonOptions(){
}

void ButtonOptions::PollButtons(){
  if(ImGui::Button("My First Option")){
    std::cout << "Uhh i think you clicked this button\n";
  }
}
