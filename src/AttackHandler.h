#pragma once
#include "imgui.h"
#include <SDL_render.h>
#include <string>
#include <vector>

struct FunctionCurve {
  std::string CurveName = " ";
  int degree;
  ImVec2 points[4];
};
// Radius x and y should be the same if it is a regular circle
struct CircleEllipse {
  float radiusx = 1;
  float radiusy = 1;
  ImVec2 center = {0, 0};
};
struct RenderSDLTexture{
  SDL_Texture* texture;
  SDL_Rect destrect = {0,0,0,0};
  bool doRender = false;
};

class AttackHandler {
public:
  void Setup(SDL_Renderer* renderer);
  RenderSDLTexture BulletTexture;
  std::vector<FunctionCurve> movementCurves;
  std::vector<FunctionCurve> speedCurves;
  ImVec2 bulletWindowPosition;
  ImVec2 bulletWindowSize;
  double time = 0.0f;
  float speed = 0.0f;
  // Just rendering the line can be handled by default ImGui utils, but actually
  // rendering the bullet following the path can be done here
  void RenderSprites(std::vector<RenderSDLTexture> textures,SDL_Renderer* _renderer);
  void RenderBullets(SDL_Renderer* _renderer,FunctionCurve curve);
  void RenderCurrentCurve(FunctionCurve curve);
  void AddMovementCurve();
  std::string GetFunctionPlainText(const FunctionCurve &curve);
};
