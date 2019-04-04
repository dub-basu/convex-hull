#ifndef GRAHAM_SCAN
#define GRAHAM_SCAN

#include<stack>
#include<vector>
#include "primitives.h"
#include "ConvexHullGraphix.h"

class GrahamScan{
    private:
        bool visualise;
        Point pivot_point;
        std::vector<Point> input_points;
        std::vector<PolarPoint> scan_points;
        std::vector<PolarPoint> ch_points;
        
        std::vector<PolarPoint> filter_points(std::vector<PolarPoint>&);
        Point find_pivot_point();
        bool is_stack_top_valid(std::stack<PolarPoint>&);
        void prep_scan_points();
        void stack_to_ch_points(std::stack<PolarPoint>);
        void draw_edges_on_stack();
    public:
        ConvexHullGraphix* chGfx;
        GrahamScan();
        GrahamScan(std::vector<Point>& points, ConvexHullGraphix* gfx = NULL);
        void compute_convex_hull();
        std::vector<PolarPoint> get_ch_points(); 
        void set_input_points(std::vector<Point>& points);
};

#endif