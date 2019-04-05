#ifndef GRAHAM_SCAN
#define GRAHAM_SCAN

#include<stack>
#include<vector>
#include "primitives.h"
#include "ConvexHullGraphix.h"

/**
 * \class GrahamScan
 * \brief Class for Graham Scan algorithm
 */
class GrahamScan{
    private:
        bool visualise;/**< visualization on/off*/
        Point pivot_point;/**< Pivot point*/
        std::vector<Point> input_points;/**< Vector of input points*/
        std::vector<PolarPoint> scan_points;/**< Vector of scan points*/
        std::vector<PolarPoint> ch_points;/**< Vector of hull points*/
        
        /** filters points
        * @param v
        * @return filtered points
        */
        std::vector<PolarPoint> filter_points(std::vector<PolarPoint>&);

        /** finds and returns pivot point
        * @return pivot point
        */
        Point find_pivot_point();

        /** Checks wheter the stack top is valid
        * @param stack of points
        * @return boolean stack to valid
        */
        bool is_stack_top_valid(std::stack<PolarPoint>&);

        /** Prepares scan points
        */
        void prep_scan_points();

        /** converts the final stack to ch_points vector
        * @param stack
        */
        void stack_to_ch_points(std::stack<PolarPoint>);

        /** Draws edges on stack
        */
        void draw_edges_on_stack();
    public:
        ConvexHullGraphix* chGfx;/**< graphics stuff*/

        /** constructor for GrahamScan class
        */
        GrahamScan();

        /** overloaded constructor for GrahamScan class
        * @param v initialize vector
        * @param gfx initialize chGfx
        */
        GrahamScan(std::vector<Point>& points, ConvexHullGraphix* gfx = NULL);

        /** computes convex hull and stores in in ch_points
        */
        void compute_convex_hull();

        /** accessor method for hull vector
        */
        std::vector<PolarPoint> get_ch_points(); 

        /** setter method for point vector
        */
        void set_input_points(std::vector<Point>& points);
};

#endif