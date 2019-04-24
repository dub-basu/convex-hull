#ifndef CHANS_ALGORITHM
#define CHANS_ALGORITHM

#include<stack>
#include<vector>
#include "primitives.h"
#include "ConvexHullGraphix.h"

class Chans{
    private:
        bool visualise;
        std::vector<Point> input_points;
        std::vector<std::vector<Point> > sub_hulls;
        int m_value;
        Point starting_point;
        std::vector<Point> ch_points;
        float is_left(Point, Point, Point);
        bool above(Point, Point, Point);
        bool below(Point, Point, Point);
        angle threshold_angle;

        Point find_next_point(Point);
        Point find_starting_point();
        Point find_point_of_Rtangency(Point, std::vector<Point>);
        std::vector<std::vector<Point> > divide_into_subhulls(std::vector<Point>, int m);

    public:
        void debug_print_subhulls();
        void debug_draw_subhull(std::vector<Point>);
        ConvexHullGraphix* chGfx;
        Chans();
        Chans(std::vector<Point>& points, ConvexHullGraphix* gfx = NULL);

        void compute_convex_hull();

        std::vector<Point> get_ch_points(); 

        void set_input_points(std::vector<Point>& points);
};

#endif