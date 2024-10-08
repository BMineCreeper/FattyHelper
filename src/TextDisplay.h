#pragma once
#include <fstream>
#include "imgui.h"

namespace TextDisplay {
void DisplayFromFile(std::ifstream& _file) {
  std::string line;
  while(std::getline(_file,line)){
    ImGui::Text("%s", line.c_str());
  }
}
} 
