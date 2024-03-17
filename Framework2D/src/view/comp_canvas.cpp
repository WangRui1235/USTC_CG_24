#include "view/comp_canvas.h"

#include <cmath>
#include <iostream>

#include "imgui.h"
#include "view/shapes/line.h"
#include "view/shapes/rect.h"
#include "view/shapes/ellipse.h"
#include "view/shapes/polygon.h"

namespace USTC_CG
{
void Canvas::draw()
{
    ImGuiIO& io = ImGui::GetIO();
    mousepos = io.MousePos;
    

    // if (is_hovered_ && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    //     mouse_click_event();
    // mouse_move_event();
    // if (!ImGui::IsMouseDown(ImGuiMouseButton_Left))
    //     mouse_release_event();
    mouse_poll_event();
    draw_background();
    draw_shapes();

    //hw1_todo: 
    if (current_shape_ && shape_type_ == kPolygon)
        current_shape_->update(mousepos.x, mousepos.y);
}

void Canvas::set_attributes(const ImVec2& min, const ImVec2& size)
{
    canvas_min_ = min;
    canvas_size_ = size;
    canvas_minimal_size_ = size;
    canvas_max_ =
        ImVec2(canvas_min_.x + canvas_size_.x, canvas_min_.y + canvas_size_.y);
}

void Canvas::show_background(bool flag)
{
    show_background_ = flag;
}

void Canvas::set_default()
{
    draw_status_ = false;
    shape_type_ = kDefault;
}

void Canvas::set_line()
{
    draw_status_ = false;
    shape_type_ = kLine;
}

void Canvas::set_rect()
{
    draw_status_ = false;
    shape_type_ = kRect;
}
void Canvas::set_ellipse()
{
    draw_status_ = false;
    shape_type_ = kEllipse;
}
void Canvas::set_polygon()
{
    draw_status_ = false;
    shape_type_ = kPolygon;
}

void Canvas::clear_shape_list()
{
    shape_list_.clear();
}

void Canvas::draw_background()
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    if (show_background_)
    {
        // Draw background recrangle
        draw_list->AddRectFilled(canvas_min_, canvas_max_, background_color_);
        // Draw background border
        draw_list->AddRect(canvas_min_, canvas_max_, border_color_);
    }
    /// Invisible button over the canvas to capture mouse interactions.
    ImGui::SetCursorScreenPos(canvas_min_);
    ImGui::InvisibleButton(
        label_.c_str(), canvas_size_, ImGuiButtonFlags_MouseButtonLeft);
    // Record the current status of the invisible button
    is_hovered_ = ImGui::IsItemHovered();
    is_active_ = ImGui::IsItemActive();
}

void Canvas::draw_shapes()
{
    Shape::Config s = { .bias = { canvas_min_.x, canvas_min_.y } };
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // ClipRect can hide the drawing content outside of the rectangular area
    draw_list->PushClipRect(canvas_min_, canvas_max_, true);
    for (const auto& shape : shape_list_)
    {
        shape->draw(s);
    }
    if (draw_status_ && current_shape_)
    {
        current_shape_->draw(s);
    }
    draw_list->PopClipRect();
}
void Canvas::mouse_poll_event()
{
    if (is_hovered_ && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
    {
        left_click_event();
    }
    if (is_hovered_ && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
    {
        right_click_event();
    }
    if (is_active_ && ImGui::IsMouseDragging(ImGuiMouseButton_Left))
    {
        left_drag_event();
    }
    if (is_hovered_ && ImGui::IsMouseReleased(ImGuiMouseButton_Left))
    {
        left_release_event();
    }
}
void Canvas::left_click_event()
{
    
    if (!draw_status_)
    {
        //draw_status_ = true;
        mouse_click_event();
    }
    else if (current_shape_ && shape_type_ == kPolygon)
    {
        current_shape_->click_callback(mousepos.x, mousepos.y);
    }
}
void Canvas::right_click_event()
{ 
     //mouse_release_event();
    if (draw_status_)
    {
        //draw_status_ = false;
        //mouse_release_event();
        mouse_click_event();
    }
}
void Canvas::left_drag_event()
{
    mouse_move_event();
}
void Canvas::left_release_event()
{
    if (draw_status_ && shape_type_ != kPolygon)
    {
        //draw_status_ = false;
        mouse_click_event();    
    }
}

void Canvas::mouse_click_event()
{
    // HW1_TODO: Drawing rule for more primitives
    if (!draw_status_)
    {
        draw_status_ = true;
        start_point_ = end_point_ = mouse_pos_in_canvas();
        //mousepos = start_point_;
        switch (shape_type_)
        {
            case USTC_CG::Canvas::kDefault:
            {
                break;
            }
            case USTC_CG::Canvas::kLine:
            {
                current_shape_ = std::make_shared<Line>(
                    start_point_.x, start_point_.y, end_point_.x, end_point_.y);
                break;
            }
            case USTC_CG::Canvas::kRect:
            {
                current_shape_ = std::make_shared<Rect>(
                    start_point_.x, start_point_.y, end_point_.x, end_point_.y);
                break;
            }
            case USTC_CG::Canvas::kEllipse:
            {
                current_shape_ = std::make_shared<Ellipse>(
                    start_point_.x, start_point_.y, end_point_.x, end_point_.y);
                break;
            }
            case USTC_CG::Canvas::kPolygon:
            {
                
                // 
                current_shape_ = std::make_shared<Polygon>(
                     mousepos.x, mousepos.y);
                break;
            }
             
            default: break;
        }
    }
    else
    {
        draw_status_ = false;
        if (current_shape_)
        {
            shape_list_.push_back(current_shape_);
            current_shape_.reset();
        }
    }
}

void Canvas::mouse_move_event()
{
    // HW1_TODO: Drawing rule for more primitives
    //Step 3: 在 comp_canvas.cpp 中实现鼠标绘制多边形
    // 可以按照这样的逻辑：鼠标左键单击时，创建一个多边形对象，后续鼠标左键单击的时候为多边形添加顶点，直到鼠标右键单击结束多边形的创建。
    // 相应地要修改 mouse_click_event(), mouse_move_event(), mouse_release_event() 中的中多边形相关的逻辑。
    if (draw_status_)
    {
        //end_point_ = mouse_pos_in_canvas();
        
        // if(current_shape_ && shape_type_ == kPolygon)
        // {
            
        //     //当鼠标左键单击时，创建一个多边形对象，后续鼠标左键单击的时候为多边形添加顶点，直到鼠标右键单击结束多边形的创建。
        //     //鼠标没有右击
        //     while(!ImGui::IsMouseClicked(ImGuiMouseButton_Right)&&ImGui::IsMouseDragging(ImGuiMouseButton_Left))
        //     {
        //         if(ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        //         {        
        //             current_shape_->update(end_point_.x, end_point_.y);
                    
        //         }
        //     }
        //     mouse_release_event();
        // }
         if (current_shape_&&shape_type_ != kPolygon)
        {
                end_point_ = mouse_pos_in_canvas();
                current_shape_->update(end_point_.x, end_point_.y);
            
        }
        else if(current_shape_ && shape_type_ == kPolygon)
        {
            current_shape_->update(mousepos.x, mousepos.y);
        }
        //鼠标左键单击时，创建一个多边形对象，后续鼠标左键单击的时候为多边形添加顶点，直到鼠标右键单击结束多边形的创建。
    }
}

void Canvas::mouse_release_event()
{
    // HW1_TODO: Drawing rule for more primitives
    
}

ImVec2 Canvas::mouse_pos_in_canvas() const
{
    ImGuiIO& io = ImGui::GetIO();
    const ImVec2 mouse_pos_in_canvas(
        io.MousePos.x - canvas_min_.x, io.MousePos.y - canvas_min_.y);
    return mouse_pos_in_canvas;
}
}  // namespace USTC_CG