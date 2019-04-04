#include<vector>
#include "primitives.h"
#include "ConvexHullGraphix.h"

class JarvisMarch{
    private:
        bool visualise;
        std::vector<Point> input_points;
        std::vector<Point> ch_points;
        Point find_next_point(Point&);
        angle threshold_angle;
        Point starting_point;
    public:
        ConvexHullGraphix* chGfx;
        JarvisMarch();
        JarvisMarch(std::vector<Point>&, ConvexHullGraphix* gfx = NULL);
        void compute_convex_hull();
        void set_input_points(std::vector<Point>& points);
        std::vector<Point> get_ch_points(); 
};