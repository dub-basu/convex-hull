#include <algorithm>
#include "ChansAlgorithm.h"
#include "GrahamScan.h"

Chans::Chans(std::vector<Point>& points, ConvexHullGraphix* gfx){
    if(gfx != NULL){
        this -> visualise = true;
        chGfx = gfx;
    } else {
        this -> visualise = false;
    }
    set_input_points(points);
}

void Chans::set_input_points(std::vector<Point>& points){
    this -> input_points = points;
    if(input_points.size() < 3) return;

    if(this -> visualise){
        chGfx -> init_points(this -> input_points);
        chGfx -> render();
    }
    this -> threshold_angle = -1;
}

std::vector<std::vector<Point> > Chans::divide_into_subhulls(std::vector<Point> points, int m){
    int number_of_subhulls = points.size() / m;
    if(points.size() % m != 0)
        number_of_subhulls++;

    std::vector<std::vector<Point> > subhulls(number_of_subhulls);
    int count = 0;
    int index = 0;

    for(auto pt: points){
        if(count < m){
            subhulls[index].push_back(pt);
            count++;
        } else {
            count = 1;
            index++;
            subhulls[index].push_back(pt);
        }
    }

    for(int i=0;i<subhulls.size();i++){

        GrahamScan gh_scan(subhulls[i]);
        gh_scan.compute_convex_hull();
        
        std::vector<PolarPoint> result_graham;
        result_graham = gh_scan.get_ch_points();

        if(this -> visualise){
            for(auto pt: subhulls[i]){
                chGfx -> remove_point(pt);
            }
            for(auto pt: result_graham){
                chGfx -> add_point(pt);
            }
        }

        subhulls[i].resize(result_graham.size());

        for(int j=0;j<result_graham.size();j++){
            Point pt(result_graham[j].x, result_graham[j].y);
            subhulls[i][j] = pt;
        }

        if(this -> visualise){
            draw_subhull(subhulls[i]);
            chGfx -> render();
        }

    }

    return(subhulls);

}

void Chans::compute_convex_hull(){
    this -> starting_point = find_starting_point();
    int t = 1;

    while(true){
        this -> m_value = pow(2, pow(2,t));
        find_hull_points(this -> m_value);

        if(!(this -> incomplete)){
            break;
        } else {
            std::cout << "!! INCOMPLETE !!\nNumber of points found = " << (this -> ch_points).size() << std::endl;
            std::cout << "Points found: " << std::endl;
            for(auto pt: this -> ch_points){
                std::cout << pt << std::endl;
            }
            std::cout << std::endl;
            t++;
        }
    }
}

Point Chans::find_starting_point(){
    std::vector<Point> min_points;
    Point minimum_point = *min_element((this -> input_points).begin(), (this -> input_points).end());
    return(minimum_point);
}

Point Chans::find_next_point(Point pt){

    std::vector<PolarPoint> points_of_tangency;
    
    for(auto subhull: this -> sub_hulls){
        PolarPoint tan_point(find_point_of_Rtangency(pt, subhull), pt);
        points_of_tangency.push_back(tan_point);
    }

    sort(points_of_tangency.begin(), points_of_tangency.end());

    PolarPoint next_p_pt;
    for(auto p_pt: points_of_tangency){
        if(p_pt.get_p_angle() >= this -> threshold_angle){
            if(Point::are_collinear(next_p_pt, pt, p_pt)){
                next_p_pt = next_p_pt.get_p_distance() > p_pt.get_p_distance() ? next_p_pt : p_pt;
            }
            else if(p_pt < next_p_pt){
                next_p_pt = p_pt;
            }
        }
    }
    this -> threshold_angle = next_p_pt.get_p_angle();
    
    Point min_point(next_p_pt.x, next_p_pt.y);
    return(min_point);
}

Point Chans::find_point_of_Rtangency(Point pt, std::vector<Point> subhull){

    int debug_flag = 0;
    Point debug_temp(252.8, -996.68);
    Point debug_temp2(222.96, 484.7);

    if(pt == debug_temp && subhull[0] == debug_temp2 && this -> m_value == 16)
        debug_flag = 1;
    
    int subhull_size = subhull.size();

    int start;
    int end;
    int mid;

    bool start_up, mid_down;
    
    if (below(pt, subhull[1], subhull[0]) && !above(pt, subhull[subhull_size-1], subhull[0]))
        return subhull[0];

    for(start=0, end=subhull_size;;){
       
        mid = (start + end) / 2;
        int a = start, b = mid, c = end;
        
        if(subhull[start] == pt){
            return(subhull[(start+1)%subhull_size]);
        } else if (subhull[end] == pt && !subhull[end].is_nan()) {
            return(subhull[(end+1)%subhull_size]);
        } else if (subhull[mid] == pt) {
            return(subhull[(mid+1)%subhull_size]); 
        }

        mid_down = below(pt, subhull[(mid+1)%subhull_size], subhull[mid]);
        if(mid_down && !above(pt, subhull[(mid-1)%subhull_size], subhull[mid]))
            return(subhull[mid]);

        start_up = above(pt, subhull[(start+1)%subhull_size], subhull[start]);
        
        if(start_up){
            if(mid_down){
                end = mid;
            } else {
                if(above(pt, subhull[start], subhull[mid])){
                    end = mid;
                } else {
                    start = mid;
                }
            }
        } else {
            if(!mid_down){
                start = mid;
            } else {
                if(below(pt, subhull[start], subhull[mid])){
                    end = mid;
                } else {
                    start = mid;
                }
            }
        }
    }
}

float Chans::is_left(Point pt1, Point pt2, Point pt3){
    float result = (pt2.x - pt1.x)*(pt3.y - pt1.y) - (pt3.x - pt1.x)*(pt2.y - pt1.y);
    return(result);
}

bool Chans::above(Point pt, Point pt1, Point pt2){
    return(is_left(pt, pt1, pt2) > 0);
}

bool Chans::below(Point pt, Point pt1, Point pt2){
    return(is_left(pt, pt1, pt2) < 0);
}

std::vector<Point> Chans::get_ch_points(){
    return(this -> ch_points);
}

void Chans::debug_print_subhulls(){
    for(int i=0;i<(this -> sub_hulls).size(); i++){
        std::cout << "Subhull #" << i << std::endl;
        for(auto pt: (this->sub_hulls)[i]){
            std::cout << pt << std::endl;
        }
        std::cout << std::endl;
    }
}

void Chans::draw_subhull(std::vector<Point> subhull){
    for(int i=0;i<subhull.size()-1;i++){
        chGfx -> add_edge(subhull[i], subhull[i+1]);
    }
    chGfx -> add_edge(subhull[subhull.size()-1], subhull[0]);
}

void Chans::find_hull_points(int maximum_number_of_points){

    this -> threshold_angle = -1;
    (this -> ch_points).clear();
    std::cout << "\nM value: " << this -> m_value << std::endl;
    this -> sub_hulls = divide_into_subhulls(this -> input_points, this -> m_value);

    Point next_point(this -> starting_point);

    for(int count=0; count < maximum_number_of_points; count++){

        ch_points.push_back(next_point);
        Point pt = find_next_point(next_point);

        if(this -> visualise){
            chGfx -> add_edge(next_point, pt);
            chGfx -> render();
        }

        next_point = pt;

        if(next_point == this -> starting_point){
            this -> incomplete = false;
            return;
        } else {
            continue;
        }
    }
    this -> incomplete = true;
    if(this -> visualise){
        chGfx -> clear_lines();
    }
    return;
}