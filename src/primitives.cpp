#include<cmath>
#include "primitives.h"

Point::Point(){
    x = 0;
    y = 0;
}

Point::Point(coordinate x_in, coordinate y_in){
    x = x_in;
    y = y_in;
}

bool Point::operator==(const Point &p2) {
    // TODO: Floating point errors handle? Some epsilon
    return this -> x == p2.x && this -> y == p2.y;
}

bool Point::operator!=(const Point &p2) {
    return this->x != p2.x || this->y != p2.y;
}

bool Point::operator< (const Point& right) const{
    if(y < right.y)
        return true;
    else if( y > right.y)
        return false;
    else
        return x < right.x;
}

Point Point::operator- (const Point& right) const{
    Point difference(x - right.x, y - right.y);
    return(difference);
}

bool Point::is_nan(){
    return(std::isnan(x) || std::isnan(y));
}

len Point::euclidean_distance(Point pt){
    len dist = pow((this->x - pt.x),2) + pow((this->y - pt.y),2);
    dist = sqrt(dist);
    return dist;
}

angle Point::angle_between_vectors(Point& pt1, Point& pt2){
    Point origin(0,0);
    angle cos_theta = (pt1.x * pt2.x) + (pt1.y * pt2.y);
    cos_theta /= pt1.euclidean_distance(origin);
    cos_theta /= pt2.euclidean_distance(origin);
    return(acos(cos_theta));
}

bool Point::are_collinear(Point pt1, Point pt2, Point pt3){
    len det_val =   pt1.x * (pt2.y - pt3.y) +
                    pt2.x * (pt3.y - pt1.y) +
                    pt3.x * (pt1.y - pt2.y);
    if(det_val == 0) return true;
    else return false;
}

std::ostream& operator<<(std::ostream& os, const Point& pt){
    os << "(" << pt.x << ", " << pt.y << ")";
    return os;
}

bool LineSegment::contains_point(Point pt) const{
    coordinate slope_diff = (pt.x - start_point.x) * (pt.y - end_point.y)
                          - (pt.x - end_point.x) * (pt.y - start_point.y);

    if(slope_diff != 0){
        return false;
    }
    else {
        if(start_point.x == end_point.x)
            return(pt.y <= end_point.y && pt.y >= start_point.y);
        else{
            coordinate t = (pt.x - start_point.x) / (end_point.x - start_point.x);
            return (t >= 0 && t <= 1);
        }
    }
}

Point LineSegment::intersects_at(LineSegment ls){
    Point p1 = this -> start_point,
          p2 = this -> end_point,
          p3 = ls.start_point,
          p4 = ls.end_point;

    coordinate denr = (p4.x - p3.x)*(p1.y - p2.y) - (p1.x - p2.x)*(p4.y - p3.y);
    
    if( denr == 0 ){
        return (NAN_POINT);
    }

    coordinate ta, tb;
    ta = (p3.y - p4.y)*(p1.x - p3.x) + (p4.x - p3.x)*(p1.y - p3.y);
    tb = (p1.y - p2.y)*(p1.x - p3.x) + (p2.x - p1.x)*(p1.y - p3.y);
    ta /= denr;
    tb /= denr;

    if(0 <= ta && ta <= 1 && 0 <= ta && ta <= 1){
        return Point(p1.x + ta * (p2.x - p1.x), p1.y + ta * (p2.y - p1.y));
    }
    else {
        return (NAN_POINT); 
    }

}

LineSegment::LineSegment(){
    this->start_point = NAN_POINT;
    this->end_point = NAN_POINT;
}

LineSegment::LineSegment(Point p1, Point p2){
    if(p1.x < p2.x){
        start_point = p1;
        end_point = p2;
    } else if (p1.x == p2.x && p1.y < p2.y) {
        start_point = p1;
        end_point = p2;
    } else {
        start_point = p2;
        end_point = p1;
    }
}


bool LineSegment::operator==(const LineSegment &l2) {
    return (this->start_point == l2.start_point && this->end_point == l2.end_point);
}


Point LineSegment::start_pt(){
    return(start_point);
}

Point LineSegment::end_pt(){
    return(end_point);
}

Point LineSegment::horizontal_projection(const Point &pt) const{
    if(end_point.y == start_point.y){
        return NAN_POINT;
    }
    else {
        coordinate x_coord = (pt.y - start_point.y) / (end_point.y - start_point.y);
        x_coord *= (end_point.x - start_point.x);
        x_coord += start_point.x;
        Point retPt = Point(x_coord, pt.y);
        return this -> contains_point(retPt) ? retPt : NAN_POINT ;
    }
}

Point LineSegment::vertical_projection(const Point &pt) const {
    if(start_point.x == end_point.x){
        return NAN_POINT;
    }
    else{
        coordinate y_coord = (pt.x - start_point.x) / (end_point.x - start_point.x);
        y_coord *= (end_point.y - start_point.y);
        y_coord += start_point.y;
        Point retPt = Point(pt.x, y_coord);
        return this -> contains_point(retPt) ? retPt : NAN_POINT ;
    }

    //return Point();
}

bool LineSegment::is_nan(){
    return(start_point.is_nan() || end_point.is_nan());
}

PolarPoint::PolarPoint(){
    this -> p_angle = NAN_ANGLE;
    this -> p_distance = NAN_LEN;
}
coordinate LineSegment::slope() {
    return (start_point.y - end_point.y) / (start_point.x - end_point.x) ;
}


PolarPoint::PolarPoint(){}

PolarPoint::PolarPoint(Point pt, Point origin){
    x = pt.x;
    y = pt.y;
    p_distance = pt.euclidean_distance(origin);
    if (p_distance == 0)
        p_angle = NAN_ANGLE;
    else{
        p_angle = acos( (pt.x - origin.x) / p_distance );
        if(pt.y < origin.y) p_angle = 2*PI - p_angle;
    }
}

len PolarPoint::get_p_distance() const{ return(this -> p_distance); }

angle PolarPoint::get_p_angle() const{ return(this -> p_angle); }

angle PolarPoint::get_p_angle_degrees() const {return((this -> p_angle) * (180 / PI));}

bool PolarPoint::operator< (const PolarPoint& right) const{

    if(std::isnan(right.get_p_angle())) return true;
    else if(std::isnan(this -> p_angle)) return false;

    if(this->get_p_angle() < right.get_p_angle())
        return true;
    else if( this->get_p_angle() > right.get_p_angle())
        return false;
    else
        return this->get_p_distance() >= right.get_p_distance();
}

void PolarPoint::set_p_angle(angle new_angle){
    this -> p_angle = new_angle;
}
