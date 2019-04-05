#include<vector>
#include "primitives.h"
#include "ConvexHullGraphix.h"

/**
 * \class JarvisMarch
 * \brief Class for Jarvis March algorithm
 */
class JarvisMarch{
    private:
        bool visualise;/**< visualization on/off*/
        std::vector<Point> input_points;/**< Vector of input points*/
        std::vector<Point> ch_points;/**< Vector of hull points*/

        /**
        * find next point in ordering
        * @param p
        * @return Point object
        */
        Point find_next_point(Point&);
        angle threshold_angle;/**< Threshold for searching next point*/
        Point starting_point;/**< First point*/

    public:
        ConvexHullGraphix* chGfx;/**< graphics stuff*/

        /** constructor for JarvisMarch class
        */
        JarvisMarch();

        /** overloaded constructor for JarvisMarch class
        * @param v initialize vector
        * @param gfx initialize chGfx
        */
        JarvisMarch(std::vector<Point>&, ConvexHullGraphix* gfx = NULL);

        /** computes convex hull and stores in in ch_points
        */
        void compute_convex_hull();

        /** setter method for point vector
        */
        void set_input_points(std::vector<Point>& points);

        /** accessor method for hull vector
        */
        std::vector<Point> get_ch_points(); 
};