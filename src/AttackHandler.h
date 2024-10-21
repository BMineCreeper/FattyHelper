#pragma once
#include "Structs.h"
#include <vector>
// The job of this class should be to combine and control aspects of combined curves, it should then export all the curves as one attack to the file writer

class AttackHandler {
public:
  void AddCurve();
  void AddEllipse();
  void SaveCurve();
  void SaveEllipse();
public:
  FunctionCurve currentCurve;
  Ellipse currentEllipse;
  bool hasCurve = false;
  bool hasEllipse = false;
private:
  std::vector<FunctionCurve> Curves;
  std::vector<Ellipse> Ellipses;
};
