#pragma once
#include "AttackHandler.h"
#include "imgui.h"
class PointDragger{
public:   
  void RenderPoints();
  void AddCurve(FunctionCurve* _curve);
  void DragPoints();
private:
  ImVec2 points[4] = {{500,500},{500,500},{500,500},{500,500}};
  std::vector<FunctionCurve*> curves;
  bool isDragging = false;
  int currentPoint;
};
