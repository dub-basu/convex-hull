#ifndef CHANS_ALGORITHM
#define CHANS_ALGORITHM

#include<stack>
#include<vector>
#include "primitives.h"
#include "ConvexHullGraphix.h"

/**
 * \class Chans
 * \brief Class for Chan's Algorithm for 2 dimensions
 */
class Chans{
    private:
        bool visualise;/**< visualization on/off*/
        std::vector<Point> input_points;/**< Vector of input points*/
        std::vector<std::vector<Point> > sub_hulls;/**< Vector for storing intermediate hulls*/
        int m_value;
        Point starting_point;
        std::vector<Point> ch_points;/**< Vector of hull points*/
        angle threshold_angle;/**< Threshold for searching next point*/
        bool incomplete;/**< Flag to determine whether convex hull is obtained*/

        /** Utility function for tangent finding function
        */
        float is_left(Point, Point, Point);

        /** Utility function for tangent finding function
        */
        bool above(Point, Point, Point);
        
        /** Utility function for tangent finding function
        */
        bool below(Point, Point, Point);
        
        /** Carries out one iteration of Jarvis March over selected points
         * @param H The upper bound on the number of points to be found
        */
        void find_hull_points(int);

        /** Finds the next point on the convex hull
         * @param point The current point
        */
        Point find_next_point(Point);

        /** Finds the starting point(bottom-most left-most) for convex hull.
         * Stores value in object member variable.
        */
        Point find_starting_point();

        /** Algorithm to find the right tangent to a polygon given
         * a point outside it.
         * @param point External point from which tangent is drawn
         * @param subhull Vector of points in counter clockwise sense
         * which make up the polygon.
        */
        Point find_point_of_Rtangency(Point, std::vector<Point>);

        /** Given a set of points, divides them into sub-groups, each containing
         * at most 'm' elements. Runs Graham Scan on each sub-group to store 
         * Convex Hull of each group into a class member
         * @param points - Set of points to be divided into groups(subhulls)
         * 
        */
        std::vector<std::vector<Point> > divide_into_subhulls(std::vector<Point>, int m);

    public:

        /** Debug utility function to print each sub-hull
        */
        void debug_print_subhulls();

        /** Adds the edges of the subhull of graphix object
         * @param points - Vector of points comprising the subhull
        */
        void draw_subhull(std::vector<Point>);

        ConvexHullGraphix* chGfx;/**< Instance of graphix class for visualisations*/
        
        /** Default constructor for Chans class
        */
        Chans();

        /** Parametrized constructor for JarvisMarch class
        */
        Chans(std::vector<Point>& points, ConvexHullGraphix* gfx = NULL);

        /** computes convex hull and stores in in ch_points
        */
        void compute_convex_hull();

        /** setter method for point vector
        */
        std::vector<Point> get_ch_points(); 

        /** setter method for point vector
        */
        void set_input_points(std::vector<Point>& points);
};

#endif