#pragma once
#include "imgui.h"
#include <SDL.h>
struct FunctionCurve {
  char CurveName[128] = " ";
  int degree;
  ImVec2 points[4] = {{500, 500}, {500, 750}, {1000, 500}, {1000, 750}};
};
// Radius x and y should be the same if it is a regular circle
struct Ellipse {
  char EllipseName[128] = " ";
  float radiusx = 10;
  float radiusy = 10;
  ImVec2 center = {500, 500};
  float rotation = 0.0f;
};
struct RenderSDLTexture {
  SDL_Texture* texture;
  SDL_Rect destrect = {0, 0, 0, 0};
  bool doRender = false;
};
