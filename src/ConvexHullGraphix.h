#ifndef CONVEX_HULL_GRAPHIX
#define CONVEX_HULL_GRAPHIX

#define DEFAULT_COLOR 0,0,0
#define POINT_COLOR 0,0,0
#define PIVOT_COLOR 0,1,0
#define SPOKE_COLOR 0,0,0
#define EDGE_COLOR 0,1,0.4

#include<vector>
#include "Graphix.h"
#include "primitives.h"

/**
 * \class ConvexHullGraphix
 * \brief Class for Visualization
 */
class ConvexHullGraphix: public Graphix {
    private:
        
        std::vector<Point> input_points;
        std::vector<LineSegment> edges;
        Point pivot_point;
        Point event_pt;

        LineSegment sweep_line;

        void draw_point(Point, GLfloat red=0, GLfloat green=0, GLfloat blue=0);
        void draw_init_points();
        void draw_spokes();
        void update_scene();
        void draw_edges();
    public:
        void update_pivot_point(Point&);
        ConvexHullGraphix(std::mutex& mtx);
        void add_edge(LineSegment);
        void add_edge(Point, Point);
        void remove_edge(LineSegment&);
        void remove_edge(Point, Point);
        void init_points(std::vector<Point> points);
        void update_event(Point);
};

#endif