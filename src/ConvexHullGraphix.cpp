#include<algorithm>
#include "ConvexHullGraphix.h"

ConvexHullGraphix::ConvexHullGraphix(std::mutex& mtx):Graphix(mtx){
    Point start(-WIN_BREADTH / 2, WIN_HEIGHT);
    Point end(WIN_BREADTH / 2, WIN_HEIGHT);
    pivot_point = NAN_POINT;
}

void ConvexHullGraphix::init_points(std::vector<Point> points){
    this -> input_points = points;
    draw_init_points();
}

void ConvexHullGraphix::draw_init_points(){
    for(auto i: input_points){
        draw_point(i, POINT_COLOR);
    }
}

void ConvexHullGraphix::update_pivot_point(Point& pt){
    this -> pivot_point = pt;
    update_scene();
}

void ConvexHullGraphix::update_scene(){
    clear();
    draw_init_points();
    if(!(this -> pivot_point).is_nan()){
        draw_point(this -> pivot_point, PIVOT_COLOR);
        draw_spokes();
    }
    draw_edges();
}

void ConvexHullGraphix::add_edge(LineSegment ln){
    edges.push_back(ln);
    update_scene();
}

void ConvexHullGraphix::add_edge(Point pt1, Point pt2){
    LineSegment ln(pt1, pt2);
    add_edge(ln);
}

void ConvexHullGraphix::remove_edge(LineSegment& ln){
    edges.erase(std::remove(edges.begin(), edges.end(), ln), edges.end());
    update_scene();
}

void ConvexHullGraphix::remove_edge(Point pt1, Point pt2){
    LineSegment ln(pt1, pt2);
    remove_edge(ln);
}

void ConvexHullGraphix::draw_edges(){
    for(auto edge: this -> edges){
        draw_line(edge, EDGE_COLOR);
    }
}

void ConvexHullGraphix::draw_spokes(){
    for(auto pt: this -> input_points){
        LineSegment ln(pivot_point, pt);
        draw_dashed_line(ln, SPOKE_COLOR);
    }
}

void ConvexHullGraphix::draw_point(Point pt, GLfloat red, GLfloat green, GLfloat blue){
    glBegin(GL_POINTS);
        glColor3f(red, green, blue);  
        glVertex2f(pt.x,pt.y);
        glColor3f(DEFAULT_COLOR);
    glEnd();
}