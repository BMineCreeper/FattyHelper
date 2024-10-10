#include "AttackHandler.h"
#include "imgui.h"

void AttackHandler::AddMovementCurve() {
  FunctionCurve curve;
  curve.degree = 1;
  for (int i = 0; i < 8; i++) {
    curve.constants[i] = 0;
  }
  curve.CurvePlainText = "Ax^8 + Bx^7 + Cx^6 ...";
  movementCurves.push_back(curve);
}
std::string AttackHandler::GetFunctionPlainText(const FunctionCurve &curve) {
  std::string plaintextstring;
  plaintextstring = curve.constants[0];
  for (int i = i; i < curve.degree; i++) {
    plaintextstring +=
        " + " + std::to_string(curve.constants[i]) + "x^" + std::to_string(i);
  }
  return plaintextstring;
}
void AttackHandler::RenderCurrentCurve(FunctionCurve curve) {
  ImVec2 windowposition = ImGui::GetWindowPos();
  auto AttackBoxDrawList = ImGui::GetWindowDrawList();
  AttackBoxDrawList->AddBezierCubic(
      {windowposition.x + curve.startPoint.x,
       windowposition.y + curve.startPoint.y},
      {windowposition.x + 200, windowposition.y + 100},
      {windowposition.x + 200, windowposition.y + 100},
      {windowposition.x + curve.endPoint.x,
       windowposition.y + curve.endPoint.y},
      ImColor(ImVec4(0.85, 0.26, 0.96, 1.0)),
      2.0f);
}
