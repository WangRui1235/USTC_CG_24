#include "comp_warping.h"


#include <Eigen/Dense>


// //std::pair<int, int>CompWarping::fisheye_warping(int x, int y, int width, int height)
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


namespace USTC_CG
{
    std::pair<int, int> warping_IDW::warping_func(int x, int y, int width, int height)
    {
       if(start_points_.size() ==  0)
        {
            return {x, y};
        }

        float w = 0.f; 
        float u = 0.f, v = 0.f;
        for(int i = 0; i < start_points_.size(); i++)
        {
           float dx = x - start_points_[i].x;
           float dy = y - start_points_[i].y;
           float d = (dx * dx + dy * dy);//distance           
            if (d < 1e-6)
                {
                    return { static_cast<int>(start_points_[i].x), static_cast<int>(start_points_[i].y) };
                }
            float weight = static_cast<float>(1.0) / d;
            w += weight;
            u += weight * start_points_[i].x;
            v += weight * start_points_[i].y;
        }
        u /= w;
        v /= w;
        return { static_cast<int>(u), static_cast<int>(v) };
    }

}// namespace USTC_CG