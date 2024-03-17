#pragma once

#include "shape.h"
#include  <vector>
#include  <utility>
#include <imgui.h>



//创建一个const Imvec2类型的数组或指针
//创建一个int类型的变量，用于存储多边形的顶点数




namespace USTC_CG
{
    class Polygon : public Shape
    {
        public:
            Polygon() = default;

            // Constructor to initialize a polygon with start and end coordinates
        //HWI_TODO
            Polygon(float start_point_x, float start_point_y) 
        {
            //创建两次的目的是：第一次存储起始点，第二次存储终点
            points_.reserve(20);
            points_.emplace_back(start_point_x, start_point_y);
            points_.emplace_back(start_point_x, start_point_y);
        }
            
            virtual ~Polygon() = default;

            // Overrides draw function to implement polygon-specific drawing logic
            void draw(const Config& config) const override;

            // Overrides Shape's update function to adjust the end point during
            // interaction
            void update(float x, float y) override;
            void click_callback(float x, float y) override;

            private:
            
                //float start_point_x_, start_point_y_, end_point_x_, end_point_y_;
                // std::vector<std::pair<float, float>> end_point;
                // int num_points_;
                std::vector<ImVec2> points_;
    };
}