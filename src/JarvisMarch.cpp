#include<algorithm>
#include "JarvisMarch.h"

JarvisMarch::JarvisMarch(){}

JarvisMarch::JarvisMarch(std::vector<Point>& points, ConvexHullGraphix* gfx){
    if(gfx != NULL){
        this -> visualise = true;
        chGfx = gfx;
    } else {
        this -> visualise = false;
    }
    set_input_points(points);
}

void JarvisMarch::set_input_points(std::vector<Point>& points){
    this -> input_points = points;

    if(this -> visualise){
        chGfx -> init_points(points);
        chGfx -> render();
    }

    if(input_points.size() < 3) return;
    threshold_angle = -1;
}

void JarvisMarch::compute_convex_hull(){
    if(input_points.size() < 3) return;

    this -> starting_point = *min_element(input_points.begin(), input_points.end());
    Point next_point(starting_point);
    // std::cout << "Starting Point = " << next_point << std::endl;

    do{

        if(this -> visualise){
            chGfx -> update_pivot_point(next_point);
            chGfx -> render();
        }

        ch_points.push_back(next_point);
        Point pt = find_next_point(next_point);

        if(this -> visualise){
            chGfx -> add_edge(next_point, pt);
            chGfx -> render();
        }

        next_point = pt;

    }while(next_point != this -> starting_point);

    Point p = NAN_POINT;
    if(this -> visualise){
        chGfx -> update_pivot_point(p);
        chGfx -> render();
    }

    if(ch_points.size() < 3) ch_points.clear();
}

Point JarvisMarch::find_next_point(Point& pivot_point){
    std::vector<PolarPoint> data_points;
    for(auto pt: this -> input_points){
        PolarPoint new_p_pt(pt, pivot_point);
        data_points.push_back(new_p_pt);
    }

    PolarPoint next_p_pt;
    for(auto p_pt: data_points){
        if(p_pt.get_p_angle() >= threshold_angle){
            if(Point::are_collinear(next_p_pt, pivot_point, p_pt)){
                next_p_pt = next_p_pt.get_p_distance() > p_pt.get_p_distance() ? next_p_pt : p_pt;
            }
            else if(p_pt < next_p_pt){
                next_p_pt = p_pt;
            }
        }
    }
    this -> threshold_angle = next_p_pt.get_p_angle();

    // std::cout << "Closest point = " << next_p_pt << std::endl;
    Point next_point(next_p_pt.x, next_p_pt.y);
    return(next_point);
}

std::vector<Point> JarvisMarch::get_ch_points(){
    return(this -> ch_points);
}
