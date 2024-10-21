#pragma once
#include "Structs.h"
#include "imgui.h"
#include <SDL_render.h>
#include <vector>
// The job of this class is simply to take a curve and render it with correct positioning on the current window
// Therefore, curves should not have their position on the actual screne built in, but should be adjusted by this
// Probably should only render to one window at a time, so we can just have some sort of variable that keeps track of the current window
class CurveRenderer {
public:
  void RenderSprites(std::vector<RenderSDLTexture> textures, SDL_Renderer* _renderer);
  void RenderBullets(SDL_Renderer* _renderer, FunctionCurve curve, int numBullets);
  void RenderCurve(const FunctionCurve& _curve);
  void RenderEllipse(const Ellipse& _ellipse);
  void Setup(SDL_Renderer* renderer);

public:
  float speed = 0.0f;
  ImVec2 windowPosition;
  ImVec2 windowSize;

private:
  double time = 0.0f;
  RenderSDLTexture BulletTexture;
  ImGuiIO io;
};
