#ifndef PRIMITIVES
#define PRIMITIVES

#include<cmath>
#include<iostream>
#include<limits>
#include<map>

typedef long double coordinate;
typedef long double len;
typedef long double angle;

#define NAN_POINT Point(std::numeric_limits<coordinate>::quiet_NaN(), \
                        std::numeric_limits<coordinate>::quiet_NaN())
#define NAN_LINE LineSegment(NAN_POINT, NAN_POINT)
#define NAN_ANGLE std::numeric_limits<angle>::quiet_NaN()
#define NAN_LEN std::numeric_limits<len>::quiet_NaN()
#define PI 3.14159265358979323846

class Point{
    public:
        coordinate x;/**< abcissa*/
        coordinate y;/**< ordinate*/

        /** constructor for Point class
        */
        Point();

        /** overloaded constructor
        * @param x_in initialize x
        * @param y_in initialize y
        */
        Point(coordinate x_in, coordinate y_in);

        /**
        * equality
        * @param p2
        * @return boolean current object and param are equal
        */
        bool operator== (const Point& p2);

        /**
        * non equality
        * @param p2
        * @return boolean current object and param are not equal
        */
        bool operator!= (const Point& p2);

        /**
        * checks for illegal line/point/angle/length
        */
        bool is_nan();

        /** 
        * checks for point ordering according to algorithm design
        * @param right
        * @return boolean current object less than parameter
        */
        bool operator< (const Point& right) const;

        /**
        * Difference
        * @return point object
        */
        Point operator- (const Point& ) const;

        /**
        * Euclidean distance
        * @param Point object
        * @return Distance between points
        */
        len euclidean_distance(Point);

        /**
        * Angle between vectors in [0,2*PI]
        * @param Point object
        * @param Point object
        * @return Distance between points
        */
        static angle angle_between_vectors(Point&, Point&);

        /**
        * Checks for co-linearity
        * @param Point object
        * @param Point object
        * @param Point object
        * @return boolean co-linear
        */
        static bool are_collinear(Point, Point, Point);
        friend std::ostream& operator<<(std::ostream& os, const Point& pt);

};

class LineSegment{
    private:
        Point start_point;/**< usually top*/
        Point end_point;/**< usually bottom*/
    public:
        /** constructor for LineSegment class
        */
        LineSegment();

        /** overloaded constructor
        * @param p1 initialize start_point
        * @param p2 initialize end_point
        */
        LineSegment(Point p1, Point p2);

        /** 
        * checks wheter point is on line
        * @param pt
        * @return boolean contains point
        */
        bool contains_point(Point pt) const;

        /** 
        * checks wheter point is on line
        * @param ls LineSegment object
        * @return Point of intersection
        */
        Point intersects_at(LineSegment ls);

        /** 
        * Finds horizontal projection
        * @param pt Point
        * @return Point of horizontal projection
        */
        Point horizontal_projection(const Point &pt) const;

        /** 
        * Finds vertical projection
        * @param pt Point
        * @return Point of vertical projection
        */
        Point vertical_projection(const Point &pt) const;

        /** 
        * checks for same line segment
        * @param l2 LineSegment object
        * @return boolean same line
        */
        bool operator== (const LineSegment& l2);
        //len length();


        Point start_pt();
        Point end_pt();

        /**
        * checks for illegal line/point/angle/length
        */
        bool is_nan();

        /**
        * slope of the line segment
        */
        coordinate slope();
};

class PolarPoint: public Point{
    private:
        len p_distance;/**< radius*/
        angle p_angle;/**< theta*/
        // static angle polar_angle(Point);
    public:
        /** constructor for LineSegment class
        */
        PolarPoint();

        /** overloaded constructor
        * @param p1
        * @param p2
        */
        PolarPoint(Point, Point);

        /** accessor method for p_distance
        */
        len get_p_distance() const;
        
        /** accessor method for p_angle in radians
        */
        angle get_p_angle() const;

        /** accessor method for p_angle in degrees
        */
        angle get_p_angle_degrees() const;

        /** checks for ordering in polar points
        * @param right PolarPoint object
        * @return boolean order
        */
        bool operator< (const PolarPoint& right) const;

        /** setter method for p_angle
        */
        void set_p_angle(angle);
        // static angle angle_between_vectors(PolarPoint, PolarPoint);
};

#endif

