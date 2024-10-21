#include "CurveRenderer.h"
#include "Structs.h"
#include "Utils.h"
#include "imgui.h"
#include <iostream>

void CurveRenderer::RenderSprites(std::vector<RenderSDLTexture> textures, SDL_Renderer* renderer) {
  for (RenderSDLTexture t : textures) {
    if (t.doRender) {
      SDL_RenderCopy(renderer, t.texture, nullptr, &t.destrect);
    }
  }
}

void CurveRenderer::RenderBullets(SDL_Renderer* _renderer, FunctionCurve curve, int numBullets) {
  // Draw One bullet going along line
  for (int i = 0; i < numBullets; i++) {
    double t = time - (0.1 * i);
    float startX = curve.points[0].x + windowPosition.x;
    float startY = curve.points[0].y + windowPosition.y;
    float endX = curve.points[3].x + windowPosition.x;
    float endY = curve.points[3].y + windowPosition.y;
    float mid1X = curve.points[1].x + windowPosition.x;
    float mid1Y = curve.points[1].y + windowPosition.y;
    float mid2X = curve.points[2].x + windowPosition.x;
    float mid2Y = curve.points[2].y + windowPosition.y;
    if (t < 0) {
      continue;
    } else if (t >= 1) {
      if (i == numBullets - 1) {
        time = 0;
      }
      continue;
    } else {
      ImVec2 point = {0, 0};
      point.x = pow((1 - t), 3) * startX + 3 * pow((1 - t), 2) * t * mid1X + 3 * (1 - t) * pow(t, 2) * mid2X + pow(t, 3) * endX;
      point.y = pow((1 - t), 3) * startY + 3 * pow((1 - t), 2) * t * mid1Y + 3 * (1 - t) * pow(t, 2) * mid2Y + pow(t, 3) * endY;
      SDL_Rect destination = {static_cast<int>(point.x), static_cast<int>(point.y), 20, 20};
      SDL_RenderCopy(_renderer, BulletTexture.texture, nullptr, &destination);
    }
  }
  ImGuiIO io = ImGui::GetIO();
  double dt = io.DeltaTime;
  time += 0.3 * speed * dt;
}
void CurveRenderer::RenderCurve(const FunctionCurve& _curve) {
  ImDrawList* drawlist = ImGui::GetWindowDrawList();
  ImColor color = ImVec4(0.85, 0.26, 0.96, 1.0);
  drawlist->AddBezierCubic(Utils::Vec2AtWindow(_curve.points[0]), Utils::Vec2AtWindow(_curve.points[1]), Utils::Vec2AtWindow(_curve.points[2]),
                           Utils::Vec2AtWindow(_curve.points[3]), color, 3.0f);
}

void CurveRenderer::RenderEllipse(const Ellipse& _ellipse) {
  ImDrawList* drawlist = ImGui::GetWindowDrawList();
  ImColor color = ImVec4(0.85, 0.26, 0.96, 1.0);
  drawlist->AddEllipse(_ellipse.center, {_ellipse.radiusx, _ellipse.radiusy}, color, _ellipse.rotation, 16, 3.0f);
}

void CurveRenderer::Setup(SDL_Renderer* renderer) {
  SDL_Surface* image = IMG_Load("../Bullet.png");
  BulletTexture.texture = SDL_CreateTextureFromSurface(renderer, image);
  if (BulletTexture.texture == nullptr) {
    std::cout << "Image not found!\n";
  }
  SDL_FreeSurface(image);
  io = ImGui::GetIO();
}
