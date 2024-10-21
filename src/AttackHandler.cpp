#include "AttackHandler.h"
#include <SDL_image.h>
#include <SDL_render.h>

void AttackHandler::AddCurve() {
  FunctionCurve curve;
  curve.degree = 1;
  currentCurve = curve;
  hasCurve = true;
}
void AttackHandler::AddEllipse() {
  Ellipse ellipse;
  currentEllipse = ellipse;
  hasEllipse = true;
}
void AttackHandler::SaveCurve() {
  Curves.push_back(currentCurve);
  hasCurve = false;
}
void AttackHandler::SaveEllipse() {
  Ellipses.push_back(currentEllipse);
  hasEllipse = false;
}
