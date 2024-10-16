#include "PointDragger.h"
#include "imgui.h"
#include "Utils.h"

void PointDragger::RenderPoints()
{
    ImDrawList* drawlist = ImGui::GetWindowDrawList();
    for (int i = 0; i < 4; i++)
    {
        drawlist->AddCircleFilled(points[i],3,ImColor(ImVec4(0.85, 0.26, 0.96, 1.0)));
    }
}

void PointDragger::AddCurve(FunctionCurve* _curve)
{
    curves.push_back(_curve);
}

void PointDragger::DragPoints()
{
    for(int i = 0; i < 4; i++)
    {
        points[i] = Utils::Vec2AtWindow(curves[0]->points[i]);
    }
    ImVec2 mp = ImGui::GetMousePos();
    if(!isDragging && ImGui::IsMouseDown(ImGuiMouseButton_Left))
    {
        int i = 0;
        for(ImVec2 p : points)
        {
            if((mp.x <= (p.x + 3) && mp.x >= (p.x - 3)))
            {
                if((mp.y <= (p.y + 3) && mp.y >= (p.y - 3)))
                {
                    isDragging = true;
                    currentPoint = i;
                    break;
                }
            }
            i++;
        }
    }
    if(isDragging)
    {
        ImGui::Text("Dragging");
        if(!ImGui::IsMouseDown(ImGuiMouseButton_Left))
        {
            isDragging = false;
            points[currentPoint] = {mp.x,mp.y};
            curves[0]->points[currentPoint] = points[currentPoint];
        }
        points[currentPoint] = {mp.x,mp.y};
        curves[0]->points[currentPoint] = points[currentPoint];
    }
}
