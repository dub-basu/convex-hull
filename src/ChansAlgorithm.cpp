#include<algorithm>
#include<unistd.h>
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
    this -> m_value = 10;
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
        subhulls[i].resize(result_graham.size());
        
        for(int j=0;j<result_graham.size();j++){
            Point pt(result_graham[j].x, result_graham[j].y);
            subhulls[i][j] = pt;
        }
    }

    return(subhulls);

}

void Chans::compute_convex_hull(){
    this -> sub_hulls = divide_into_subhulls(this -> input_points, this -> m_value);
    debug_print_subhulls();


    this -> starting_point = find_starting_point();
    Point next_point(this -> starting_point);

    do{
        
        if(this -> visualise){
            chGfx -> update_pivot_point(next_point);
            chGfx -> render();
        }

        ch_points.push_back(next_point);
        // std::cout << "FOUND CH POINT: " << next_point << std::endl;
        Point pt = find_next_point(next_point);

        if(this -> visualise){
            chGfx -> add_edge(next_point, pt);
            chGfx -> render();
        }

        // std::cout << "Found next point" << pt << std::endl;
        
        next_point = pt;

    }while(next_point != this -> starting_point);    

}

Point Chans::find_starting_point(){
    std::vector<Point> min_points;

    for(auto subhull: this -> sub_hulls){
        min_points.push_back(*min_element(subhull.begin(), subhull.end()));
    }

    // std::cout << "Min Points: " << std::endl;
    // for(auto point: min_points){
    //     std::cout << point << std::endl;
    // }

    Point minimum_point = *min_element(min_points.begin(), min_points.end());
    // std::cout << "\nMinimum Point: " << minimum_point << std::endl;
    return(minimum_point);
}

Point Chans::find_next_point(Point pt){

    std::vector<PolarPoint> points_of_tangency;
    
    for(auto subhull: this -> sub_hulls){
        PolarPoint tan_point(find_point_of_Rtangency(pt, subhull), pt);
        // std::cout << "Point of contact: " << tan_point << std::endl << std::endl;
        points_of_tangency.push_back(tan_point);
    }

    sort(points_of_tangency.begin(), points_of_tangency.end());
    // std::cout << "Current pivot point: " << pt << std::endl;
    // std::cout << "Points of tangency: " << std::endl;
    // for(auto pt: points_of_tangency){
    //     std::cout << pt << std::endl;
    // }
    // std::cout << std::endl;


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

    // std::cout << "found min point of tangency: " << next_p_pt << std::endl;
    Point min_point(next_p_pt.x, next_p_pt.y);

    return(min_point);
}

Point Chans::find_point_of_Rtangency(Point pt, std::vector<Point> subhull){

    // std::cout << "Pivot point for search: " << pt << std::endl;
    // std::cout << "\nBinary search on hull: " << std::endl;
    // if(this -> visualise){
    //     debug_draw_subhull(subhull);
    //     chGfx -> render();
    // }
    // for(auto pt: subhull){
    //     std::cout << pt << std::endl; 
    // }
    // std::cout << std::endl;

    int subhull_size = subhull.size();

    int start = 0;
    int end = subhull_size - 1;
    int mid;

    bool start_up, mid_down;

    if (below(pt, subhull[1], subhull[0]) && !above(pt, subhull[subhull_size-1], subhull[0]))
        return subhull[0];

    // std::cout << "Now entering binary search...\n" << std::endl;

    for(start=0, end=subhull_size;;){
       
        mid = (start + end) / 2;

        // std::cout << "start = " << start << " " << subhull[start] << std::endl;
        // std::cout << "mid = " << mid << " " << subhull[mid] << std::endl;
        // std::cout << "end = " << end << " " << subhull[end] << std::endl;
        int a = start, b = mid, c = end;
        
        if(this -> visualise){
            chGfx -> add_edge(pt, subhull[mid]);
            chGfx -> add_edge(pt, subhull[start]);
            chGfx -> add_edge(pt, subhull[end]);
            chGfx -> render();
        }
        // usleep(1000000);

        if(subhull[start] == pt){
            return(subhull[(start+1)%subhull_size]);
        } else if (subhull[end] == pt) {
            return(subhull[(end+1)%subhull_size]);
        } else if (subhull[mid] == pt) {
            return(subhull[(mid+1)%subhull_size]); 
        }
        

        mid_down = below(pt, subhull[(mid+1)%subhull_size], subhull[mid]);
        if(mid_down && !above(pt, subhull[(mid-1)%subhull_size], subhull[mid]))
            return(subhull[mid]);

        // std::cout << "Mid down: " << mid_down << std::endl;

        start_up = above(pt, subhull[(start+1)%subhull_size], subhull[start]);
        // std::cout << "Start up: " << start_up << std::endl;
        if(start_up){
            // std::cout << "if condition reached" << std::endl;
            if(mid_down){
                // std::cout << "if if " << std::endl;
                end = mid;
            } else {
                if(above(pt, subhull[start], subhull[mid])){
                    // std::cout << "if else if" << std::endl;
                    end = mid;
                } else {
                    // std::cout << "if else else" << std::endl;
                    start = mid;
                }
            }
        } else {
            // std::cout << "else condition reached" << std::endl;
            if(!mid_down){
                // std::cout << "else first" << std::endl; 
                start = mid;
            } else {
                if(below(pt, subhull[start], subhull[mid])){
                    // std::cout << "else second first" << std::endl;
                    end = mid;
                } else {
                    // std::cout << "else second second" << std::endl;
                    start = mid;
                }
            }
        }

        if(this -> visualise){
            chGfx -> remove_edge(pt, subhull[b]);
            chGfx -> remove_edge(pt, subhull[a]);
            chGfx -> remove_edge(pt, subhull[c]);
            chGfx -> render();
        }

    // usleep(50000);
    // std::cout << "\n" ;
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

void Chans::debug_draw_subhull(std::vector<Point> subhull){
    for(int i=0;i<subhull.size()-1;i++){
        if(this -> visualise){
            LineSegment ls(subhull[i], subhull[i+1]);
            chGfx -> add_edge(ls);
        }
    }
    LineSegment ls(subhull[subhull.size()-1], subhull[0]);
    chGfx -> add_edge(ls);
}
