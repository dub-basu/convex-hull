#include <algorithm> 
// #include <iostream>
#include "GrahamScan.h"

GrahamScan::GrahamScan(){}

GrahamScan::GrahamScan(std::vector<Point>& points){
    set_input_points(points);
}

void GrahamScan::set_input_points(std::vector<Point>& points){
    this -> input_points = points;
    if(input_points.size() < 3) return;
    pivot_point = find_pivot_point();
    prep_scan_points();
}

void GrahamScan::compute_convex_hull(){
    if(this->scan_points.size() < 3) return;

    std::stack<PolarPoint> point_stack;
    
    std::vector<PolarPoint>::iterator front, rear;
    front = scan_points.begin();
    rear = scan_points.end() - 1;

    for(int i=0;i<3;i++){
        // Initialize stack with 3 points
        point_stack.push(*front);
        front++; 
    }

    while(true){
        if(is_stack_top_valid(point_stack)){
            if(front > rear) break;
            else{
                point_stack.push(*front);
                front++;
            }
        } else {
            PolarPoint temp1 = point_stack.top(); point_stack.pop();

            // std:: cout << "\n";
            // std:: cout << "\neliminating: " ;
            // std::cout << "(" << point_stack.top().x << "," << point_stack.top().y << ")" << std::endl;
            // std::cout << "^^^^^^^^^^\n\n";

            point_stack.pop();
            point_stack.push(temp1);
            if(point_stack.size() >= 3) continue;
            else{
                PolarPoint temp2 = point_stack.top(); point_stack.pop();
                PolarPoint temp3 = point_stack.top(); point_stack.pop();
                point_stack.push(*rear);
                rear--;
                point_stack.push(temp3);
                point_stack.push(temp2);
                continue;
            }
        }
    }

    stack_to_ch_points(point_stack);
    sort(ch_points.begin(), ch_points.end());
}

std::vector<PolarPoint> GrahamScan::get_ch_points(){
    return(this -> ch_points);
}

bool GrahamScan::are_collinear(Point pt1, Point pt2, Point pt3){
    len det_val =   pt1.x * (pt2.y - pt3.y) +  
                    pt2.x * (pt3.y - pt1.y) +  
                    pt3.x * (pt1.y - pt2.y);
    if(det_val == 0) return true;
    else return false;
}

std::vector<PolarPoint> GrahamScan::filter_points(std::vector<PolarPoint>& scan_points){
    std::vector<PolarPoint> filtered_points;
    angle previous_checked = -1;
    for(auto i: scan_points){
        if(i.get_p_angle() == previous_checked) continue;
        else{
            previous_checked = i.get_p_angle();
            filtered_points.push_back(i);
        }
    }
    return(filtered_points);
}


Point GrahamScan::find_pivot_point(){
    pivot_point = NAN_POINT;
    for(int i=0; i<input_points.size()-2; i++){
        std::vector<Point> triplet(input_points.begin() + i, input_points.begin() + i + 3);
        // for(auto i: triplet){
        //     std::cout << "(" << i.x << "," << i.y << ")";
        // }
        // std::cout << std::endl;

        if(are_collinear(triplet[0], triplet[1], triplet[2])) continue;
        else{
            pivot_point.x = ( triplet[0].x + triplet[1].x + triplet[2].x ) / 3;
            pivot_point.y = ( triplet[0].y + triplet[1].y + triplet[2].y ) / 3;
            break;
        }
    }
    return pivot_point;
}

bool GrahamScan::is_stack_top_valid(std::stack<PolarPoint>& point_stack){
    std::vector<PolarPoint> top_p_points;
    for(int i=0;i<3;i++){
        top_p_points.push_back(point_stack.top());
        point_stack.pop();
    }

    for(int i=0;i<3;i++) point_stack.push(top_p_points[3-1-i]);

    // std::cout << "\nstack points------VVVVVVVV\n";
    // for(int i=0;i<top_p_points.size();i++) 
    //     std::cout << top_p_points[i] << std::endl;


    Point middle(top_p_points[1].x - pivot_point.x, top_p_points[1].y - pivot_point.y);

    Point vec1(top_p_points[1].x - top_p_points[0].x, top_p_points[1].y - top_p_points[0].y);
    Point vec2(top_p_points[1].x - top_p_points[2].x, top_p_points[1].y - top_p_points[2].y);
    
    // std::cout << "middle = " << middle << std::endl;
    // std::cout << "vec1 = " << vec1 << std::endl;
    // std::cout << "vec2 = " << vec2 << std::endl;


    angle angle1 = Point::angle_between_vectors(vec1, middle);
    angle angle2 = Point::angle_between_vectors(vec2, middle);

    // std::cout << "angle1 = " << angle1 * 180 / PI << std::endl;
    // std::cout << "angle2 = " << angle2 * 180 / PI << std::endl; 
    // std::cout << "^^^^^^^^^^\n";
    
    return(angle1 + angle2 < PI);

}

void GrahamScan::prep_scan_points(){
    if(pivot_point.is_nan()) return;

    for(auto i: this -> input_points){
        PolarPoint ppoint(i,this -> pivot_point);
        (this -> scan_points).push_back(ppoint);
    }
    sort(scan_points.begin(), scan_points.begin() + scan_points.size());
    scan_points = filter_points(scan_points);
    
    // for(auto i: scan_points){
    //     std::cout << i << i.get_p_angle_degrees() << i.get_p_distance() << std::endl;
    // }
    // std::cout << std::endl;
}


void GrahamScan::stack_to_ch_points(std::stack<PolarPoint> points_stack){
    while(points_stack.size() > 0){
        PolarPoint pt(points_stack.top(), pivot_point);
        (this -> ch_points).push_back(pt);
        points_stack.pop();
    }
}
