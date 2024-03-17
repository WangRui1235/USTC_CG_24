#include"view/shapes/polygon.h"
#include <imgui.h>


//创建一个const Imvec2类型的数组，用于存储多边形的顶点坐标
//创建一个const int类型的变量，用于存储多边形的顶点数

// Step 2: 实现多边形图形类 Class Polygon
// 思考：多边形的数据应该如何存储？

// 对于多边形，实现 update(float x, float y) 函数可以用于为其添加顶点，绘制函数 draw() 可以将其分解为多段直线绘制

//需要将多边形的顶点坐标存储在一个数组中，然后在draw函数中使用AddPolyline函数绘制多边形
//在update函数中，每次调用update函数时，将传入的坐标存储在数组中，同时更新顶点数


namespace USTC_CG
{
    
    
    void Polygon::draw(const Config& config) const
    {
        std::vector<ImVec2> temp(points_);
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddPolyline(
            temp.data(),
            temp.size(),    
            IM_COL32(
                config.line_color[0],
                config.line_color[1],
                config.line_color[2],
                config.line_color[3]),
            true,
            config.line_thickness);
    }

//在update函数中，每次调用update函数时，将传入的坐标存储在数组中，同时更新顶点数
    void Polygon::update(float x, float y)
    {
        // end_point_x_ = x;
        // end_point_y_ = y;
        // end_point.push_back(std::make_pair(end_point_x_, end_point_y_));
        points_.back().x = x;
        points_.back().y = y;

    }

    void Polygon::click_callback(float x, float y)
    {
        points_.back().x = x;
        points_.back().y = y;
        if(points_.size() < 20) 
            points_.emplace_back(x, y);
    }

    
}  // namespace USTC_CG