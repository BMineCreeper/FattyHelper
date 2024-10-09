#pragma once
#include <string>
#include "imgui.h"
#include <vector>

struct FunctionCurve {
  std::string CurvePlainText = "x^2 + x + 1";
  float constants[8];
  int degree;
  ImVec2 startPoint = {0,0}; 
};
//Radius x and y should be the same if it is a regular circle
struct CircleEllipse {
  float radiusx = 1;
  float radiusy = 1;
  ImVec2 center = {0,0}; 
};

class AttackHandler {
public:
  std::vector<FunctionCurve> movementCurves;
  std::vector<FunctionCurve> speedCurves;
  //Just rendering the line can be handled by default ImGui utils, but actually rendering the bullet following the path can be done here
  void RenderCurrentCurve();
  FunctionCurve* AddFunctionCurve();
};
