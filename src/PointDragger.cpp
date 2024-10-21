#include "PointDragger.h"
#include "Utils.h"
#include "imgui.h"
// Render points with window offset
void PointDragger::RenderPoints(const FunctionCurve& _curve) {
  ImDrawList* drawlist = ImGui::GetWindowDrawList();
  ImColor color;
  for (int i = 0; i < 4; i++) {
    if (i == currentPoint && isDragging) {
      color = ImVec4(0.85, 0.26, 0.96, 1.0);
    } else {
      color = ImVec4(0.85, 0.5, 0.96, 1.0);
    }
    drawlist->AddCircleFilled(Utils::Vec2AtWindow(_curve.points[i]), 5, color);
  }
}
// Drag points with window offset, and modify the original curve to the new positon, but without the window offset
void PointDragger::DragPoints(FunctionCurve& _curve) {
  ImVec2 points[4];
  for (int i = 0; i < 4; i++) {
    points[i] = Utils::Vec2AtWindow(_curve.points[i]);
  }
  ImVec2 mp = ImGui::GetMousePos();
  if (!isDragging && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
    int i = 0;
    for (ImVec2 p : points) {
      if ((mp.x <= (p.x + 3) && mp.x >= (p.x - 3))) {
        if ((mp.y <= (p.y + 3) && mp.y >= (p.y - 3))) {
          isDragging = true;
          currentPoint = i;
          break;
        }
      }
      i++;
    }
  }
  if (isDragging) {
    ImGui::Text("Dragging");
    if (!ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
      isDragging = false;
    }
    ImVec2 Point = _curve.points[currentPoint];
    points[currentPoint] = {mp.x, mp.y};
    _curve.points[currentPoint] = Utils::Vec2WindowtoAbsolute(points[currentPoint]);
  }
}
