#pragma once

#include "view/comp_image.h"

namespace USTC_CG
{
// Image component for warping and other functions
class warping
{
    public:
     
    
    
    protected:
     std::vector<ImVec2> start_points_, end_points_;
    
     ImVec2 start_, end_;
     bool flag_enable_selecting_points_ = false;
     bool draw_status_ = false;

    public:
    warping(
        std::vector<ImVec2> start_points_,
        std::vector<ImVec2> end_points_,
        ImVec2 start_,
        ImVec2 end_,
        bool flag_enable_selecting_points_,
        bool draw_status_)
        : start_points_(start_points_),
          end_points_(end_points_),
          start_(start_),
          end_(end_),
          flag_enable_selecting_points_(false),
          draw_status_(false)
        {

        }
    virtual ~warping() noexcept = default;
    
    public:
     // A simple "fish-eye" warping function
    virtual std::pair<int, int> warping_func(int x, int y, int width, int height) = 0;
     //std::pair<int, int> idw_warping(int x, int y, int width, int height);
    };
    class warping_IDW : public warping
    {
        public:
        warping_IDW(
            std::vector<ImVec2> start_points_,
            std::vector<ImVec2> end_points_,
            ImVec2 start_,
            ImVec2 end_,
            bool flag_enable_selecting_points_ = false,
            bool draw_status_ = false)
            : warping(start_points_, end_points_, start_, end_, flag_enable_selecting_points_, draw_status_)
        {
        }
        std::pair<int, int> warping_func(int x, int y, int width, int height) override;//void idw_warping(int x, int y, int width, int height);
    };
    class warping_ANN : public warping
    {
        public:
        warping_ANN(
            std::vector<ImVec2> start_points_,
            std::vector<ImVec2> end_points_,
            ImVec2 start_,
            ImVec2 end_,
            bool flag_enable_selecting_points_ = false,
            bool draw_status_ = false)
            : warping(start_points_, end_points_, start_, end_, flag_enable_selecting_points_, draw_status_)
        {
        }
        //void ann_warping(int x, int y, int width, int height);
        std::pair<int, int> warping_func(int x, int y, int width, int height) override;
    };
    class warping_RBF : public warping
    {
        public:
        warping_RBF(
            std::vector<ImVec2> start_points_,
            std::vector<ImVec2> end_points_,
            ImVec2 start_,
            ImVec2 end_,
            bool flag_enable_selecting_points_ = false,
            bool draw_status_ = false)
            : warping(start_points_, end_points_, start_, end_, flag_enable_selecting_points_, draw_status_)
        {
        }
        //void rbf_warping(int x, int y, int width, int height);
        std::pair<int, int> warping_func(int x, int y, int width, int height) override;
    };

    class warping_fisheye : public warping
    {
        public:
        warping_fisheye(
            std::vector<ImVec2> start_points_,
            std::vector<ImVec2> end_points_,
            ImVec2 start_,
            ImVec2 end_,
            bool flag_enable_selecting_points_ = false,
            bool draw_status_ = false)
            : warping(start_points_, end_points_, start_, end_, flag_enable_selecting_points_, draw_status_)
        {
        }
        //void fisheye_warping(int x, int y, int width, int height);
        std::pair<int, int> warping_func(int x, int y, int width, int height) override;
    };

class CompWarping : public ImageEditor
{
   public:
    explicit CompWarping(const std::string& label, const std::string& filename);
    virtual ~CompWarping() noexcept = default;

    std::shared_ptr<warping> my_warping = nullptr;

    void draw() override;

    // Simple edit functions
    void invert();
    void mirror(bool is_horizontal, bool is_vertical);
    void gray_scale();
    void warping();
    // void idw();
    // void rbf();
    void restore();

    // Point selecting interaction
    void enable_selecting(bool flag);
    void select_points();
    void init_selections();

    enum class WarpingType
    {
        FISHEYE,
        IDW,
        RBF
    };
    // Store the original image data
    std::shared_ptr<Image> back_up_;
    // The selected point couples for image warping
    std::vector<ImVec2> start_points_, end_points_;

    ImVec2 start_, end_;
    bool flag_enable_selecting_points_ = false;
    bool draw_status_ = false;

   private:
    // A simple "fish-eye" warping function


    //std::pair<int, int> fisheye_warping(int x, int y, int width, int height);

    //std::pair<int, int> idw_warping(int x, int y, int width, int height);
};

}  // namespace USTC_CG