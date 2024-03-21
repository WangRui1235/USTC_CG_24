#include "comp_warping.h"


#include <Eigen/Dense>

// std::pair<int, int>CompWarping::fisheye_warping(int x, int y, int width, int height)
// {
//     float center_x = width / 2.0f;
//     float center_y = height / 2.0f;
//     float dx = x - center_x;
//     float dy = y - center_y;
//     float distance = std::sqrt(dx * dx + dy * dy);

//     // Simple non-linear transformation r -> r' = f(r)
//     float new_distance = std::sqrt(distance) * 10;

//     if (distance == 0)
//     {
//         return { static_cast<int>(center_x), static_cast<int>(center_y) };
//     }
//     // (x', y')
//     float ratio = new_distance / distance;
//     int new_x = static_cast<int>(center_x + dx * ratio);
//     int new_y = static_cast<int>(center_y + dy * ratio);

//     return { new_x, new_y };
// }
// }  // namespace USTC_CG



//- 没有点时，恒等变换（ $\boldsymbol{A}=\boldsymbol{I},\boldsymbol{b}=\boldsymbol{0}$ ）
// - 一个点时，平移变换（ $\boldsymbol{A}=\boldsymbol{I}, \boldsymbol{b}=\boldsymbol{y}_i-\boldsymbol{x}_i$ ）
// - 两个点时，平移+缩放
// - 三个点时，一般仿射变换
// - 多个点时，用最小二乘法求仿射变换


//f(\boldsymbol{p} _ j)=\sum _ {i=1}^n\boldsymbol{\alpha} _ i R(\Vert\boldsymbol{p} _ j-\boldsymbol{p} _
// i\Vert)+A\boldsymbol{p} _ j+\boldsymbol{b}=\boldsymbol{q} _ j,\quad j=1,\dots,n.
//
//



namespace USTC_CG
{
    std::pair<int, int> warping_RBF::warping_func(int x, int y, int width, int height)
    {
        int n = start_points_.size();
        using namespace Eigen;
        MatrixXf A(2,2);
        VectorXf B(2);
        VectorXf C(2);
        if(n ==  0)
        {
            return {x, y};
        }
        if(n == 1)
        {
            return {x + end_points_[0].x - start_points_[0].x, y + end_points_[0].y - start_points_[0].y};
        }
        if(n == 2)
        {
            Matrix2f T1;
            T1 << start_points_[0].x, start_points_[0].y, start_points_[1].x, start_points_[1].y;
            Matrix2f T2;
            T2 << end_points_[0].x, end_points_[0].y, end_points_[1].x, end_points_[1].y;
            A = T2 * T1.inverse();

            B = Vector2f::Zero();

            C = A * Vector2f(x, y) + B;

            return {static_cast<int>(C(0)), static_cast<int>(C(1))};

        }
        if(n == 3)
        {
            Matrix2f T1;
            T1 << start_points_[0].x, start_points_[0].y, start_points_[1].x, start_points_[1].y;
            Matrix2f T2;
            T2 << end_points_[0].x, end_points_[0].y, end_points_[1].x, end_points_[1].y;
            A = T2 * T1.inverse();

            B = A * Vector2f(start_points_[2].x, start_points_[2].y) - Vector2f(end_points_[2].x, end_points_[2].y);

            C = A * Vector2f(x, y) + B;

            return {static_cast<int>(C(0)), static_cast<int>(C(1))};

        }

        else 
        {
            return {x, y};
        }

         
       

    }

}// namespace USTC_CG