#include<vector>
#include "primitives.h"

class JarvisMarch{
    private:
        std::vector<Point> input_points;
        std::vector<Point> ch_points;
        Point find_next_point(Point&);
        angle threshold_angle;
        Point starting_point;
        void compare_threshold(PolarPoint, PolarPoint);
    public:
        JarvisMarch();
        JarvisMarch(std::vector<Point>&);
        void compute_convex_hull();
        void set_input_points(std::vector<Point>& points);
        std::vector<Point> get_ch_points(); 
};