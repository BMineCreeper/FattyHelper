#pragma once
#include "Structs.h"
class PointDragger{
public:   
  //Takes a Curve and render's it's points
  void RenderPoints(const FunctionCurve& _curve);
  //Takes a Curve and allows the user to modify its points by dragging
  void DragPoints(FunctionCurve& _curve);
private:
  bool isDragging = false;
  int currentPoint;
};
