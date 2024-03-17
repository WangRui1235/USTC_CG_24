//椭圆类的实现请参考同文件夹下直线类 Line、Rect 类
//你需要为椭圆定义一个数据存储的结构，一个构造方法，
//并实现一个椭圆的绘制函数 draw()，这里 ImGui 为我们提供了一个现有的方法用以绘制椭圆：
//void AddEllipse(const ImVec2& center, float radius_x,
// float radius_y, ImU32 col, float rot = 0.0f, int num_segments = 0, float thickness = 1.0f);
//为了实现椭圆形状的动态更新，
//可以仿照 Line 和 Rect 类写一个 update(float x, float y) 函数，
//它用传入的二维鼠标位置更新椭圆内存储的数据。

#include  "view/shapes/ellipse.h"
#include  <imgui.h>
#include <cmath>

namespace USTC_CG{

    void Ellipse::draw(const Config& config) const
    {
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        draw_list->AddEllipse(
            ImVec2(
                config.bias[0] + (start_point_x_ + end_point_x_) / 2,
                config.bias[1] + (start_point_y_ + end_point_y_) / 2),
            fabsf((end_point_x_ - start_point_x_) / 2),
            fabsf((end_point_y_ - start_point_y_) / 2),//不加上绝对值会生成菱形
            IM_COL32(
                config.line_color[0],
                config.line_color[1],
                config.line_color[2],
                config.line_color[3]),
            0.0f,  // No rotation
            0,
            1.0f);
    }

    void Ellipse::update(float x, float y)
    {
        end_point_x_ = x;
        end_point_y_ = y;
    }



}


