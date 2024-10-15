#include "PointDragger.h"
#include "imgui.h"
void PointDragger::RenderPoints()
{
  
    ImVec2 wp = ImGui::GetWindowPos();
    ImDrawList* drawlist = ImGui::GetWindowDrawList();
    for (int i = 0; i < 4; i++)
    {
        drawlist->AddCircleFilled({points[i].x + wp.x,points[i].y + wp.y},3,ImColor(ImVec4(0.85, 0.26, 0.96, 1.0)));
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
        points[i] = curves[0]->points[i];
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
