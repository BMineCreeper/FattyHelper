#include "AttackHandler.h"
#include "imgui.h"
#include <SDL_render.h>
#include <SDL_image.h>
#include <iostream>

void AttackHandler::Setup(SDL_Renderer* renderer)
{
  SDL_Surface *image = IMG_Load("../Bullet.png");
  BulletTexture = RenderSDLTexture{SDL_CreateTextureFromSurface(renderer,image)};
  if(image == nullptr){
    std::cout << "Image not found!\n";
  }
  SDL_FreeSurface(image);
}
void AttackHandler::AddMovementCurve() {
  FunctionCurve curve;
  curve.degree = 1;
  movementCurves.push_back(curve);
}
std::string AttackHandler::GetFunctionPlainText(const FunctionCurve &curve) {
  std::string plaintextstring;
  for (int i = 0; i < curve.degree; i++) {
    plaintextstring = "Dollar test 13";
  }
  return plaintextstring;
}

void AttackHandler::RenderSprites(std::vector<RenderSDLTexture> textures,
                                  SDL_Renderer *renderer) {
  for (RenderSDLTexture t : textures) {
    if (t.doRender) {
      SDL_RenderCopy(renderer, t.texture, nullptr, &t.destrect);
    }
  }
}

void AttackHandler::RenderBullets(SDL_Renderer* _renderer,FunctionCurve curve,int numBullets)
{ using namespace std;
  //Draw One bullet going along line
  for(int i = 0; i < numBullets; i++){
  double t = time - (0.1 * i);
  float startX = curve.points[0].x + bulletWindowPosition.x;
  float startY = curve.points[0].y + bulletWindowPosition.y;
  float endX = curve.points[3].x + bulletWindowPosition.x;
  float endY = curve.points[3].y + bulletWindowPosition.y;
  float mid1X = curve.points[1].x + bulletWindowPosition.x;
  float mid1Y = curve.points[1].y + bulletWindowPosition.y;
  float mid2X = curve.points[2].x + bulletWindowPosition.x;
  float mid2Y = curve.points[2].y + bulletWindowPosition.y;
  if(time >= 1) time = 0;
  //Calculate current point
  ImVec2 point = {0,0};
  point.x = pow((1-t),3)*startX + 3*pow((1-t),2)*t*mid1X + 3*(1-t)*pow(t,2)*mid2X + pow(t,3)*endX;
  point.y = pow((1-t),3)*startY + 3*pow((1-t),2)*t*mid1Y + 3*(1-t)*pow(t,2)*mid2Y + pow(t,3)*endY;
  SDL_Rect destination = {static_cast<int>(point.x),static_cast<int>(point.y),20,20};
  SDL_RenderCopy(_renderer,BulletTexture.texture,nullptr,&destination);
  }
  ImGuiIO io = ImGui::GetIO();
  double dt = io.DeltaTime;
  time += 0.3 * speed * dt;
}

