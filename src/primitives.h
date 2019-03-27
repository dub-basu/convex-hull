#ifndef PRIMITIVES
#define PRIMITIVES

#include<cmath>
#include<limits>
#include<map>

typedef long double coordinate;
typedef long double len;
typedef long double angle;

#define NAN_POINT Point(std::numeric_limits<coordinate>::quiet_NaN(), \
                        std::numeric_limits<coordinate>::quiet_NaN())
#define NAN_LINE LineSegment(NAN_POINT, NAN_POINT)
#define NAN_ANGLE std::numeric_limits<angle>::quiet_NaN()
#define PI 3.14159265358979323846

class Point{
    public:
        coordinate x;
        coordinate y;
        Point();
        Point(coordinate x_in, coordinate y_in);
        bool operator== (const Point& p2);
        bool operator!= (const Point& p2);
        bool is_nan();
        bool operator< (const Point& right) const;
        len euclidean_distance(Point);
};

class LineSegment{
    private:
        Point start_point;
        Point end_point;
    public:
        LineSegment();
        LineSegment(Point p1, Point p2);
        bool contains_point(Point pt) const;
        Point intersects_at(LineSegment ls);
        Point y_projection(Point pt) const;
        bool operator== (const LineSegment& l2);
        //len length();
        Point start_pt();
        Point end_pt();
        bool is_nan();
};

class PolarPoint: public Point{
    private:
        len p_distance;
        angle p_angle;
        // static angle polar_angle(Point);
    public:
        PolarPoint();
        PolarPoint(Point, Point);
        len get_p_distance();
        angle get_p_angle();
        angle get_p_angle_degrees();
        // static angle angle_between_vectors(PolarPoint, PolarPoint);
};

#endif

