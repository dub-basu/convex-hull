#include "KirkpatrickSiedel.h"
#include <set>
#include <list>
#include <vector>
#include "median_finding.h"

#define ERROR 0.000001

vector<KirkpatrickSiedel::KpsPoint> KirkpatrickSiedel::upperHull(vector<KpsPoint> points, bool upper) {

    if (points.size() == 1){
        return vector<KpsPoint>{points[0]};
    }
    if (points.size() == 2) {
        // DRAW HERE
        // If Upper == true Draw points as is.
        // Else make 2 dummy points, with same x coordinate and -1*y coordinate of old point
        // Draw them. Do not change the originals
        KpsPoint left = points[0], right = points[1];

        if(left.x == right.x){
            if(left.y > right.y) {return vector<KpsPoint>{left} ;}
            else {return vector<KpsPoint> {left} ;}
        }

        if(left.x > right.x){ swap(left,right); }
        return vector<KpsPoint>{left,right};
    }
//    cout << "Upper Hulling : ";
//    for (auto p : points){
//        cout << p << "\t";
//    }
//    cout << "\n";

    coordinate x_split = find_median(points).x + ERROR;

    vector<KpsPoint> leftPoints, rightPoints;

    vector<KpsPoint> upper_bridge = upperBridge(points, x_split);

    for(auto p : points) {
        if(p.x <= upper_bridge[0].x){
            leftPoints.push_back(p);
        }
        else if(p.x >= upper_bridge[1].x){
            rightPoints.push_back(p);
        }
    }

    vector<KpsPoint> leftHull = upperHull(leftPoints,upper);
    vector<KpsPoint> rightHull = upperHull(rightPoints,upper);

    //leftHull.push_back(upper_bridge[0]);
    //leftHull.push_back(upper_bridge[1]);

    for(auto r : rightHull){
        leftHull.push_back(r);
    }

    return leftHull;

}

vector<KirkpatrickSiedel::KpsPoint> KirkpatrickSiedel::upperBridge(vector<KpsPoint> points, coordinate l_x) {
    vector<KpsPoint> candidates;
//    cout << "Splitting by" << l_x << ":\t";
//
//    for(auto p : points){
//        cout << p;
//    }
//
//    cout << "\n";

    list<pair<KpsPoint,KpsPoint>> pairs,new_pairs;

    vector<coordinate> slopes;

    if (points.size() == 2){
        if(points[0].x > points[1].x){ swap(points[0], points[1]); }
//        cout << "Bridge = " << points[0] << points[1] << "\n";
        return vector<KpsPoint> {points[0],points[1]};
    }


    for (int i = 0; i < points.size() - 1; i += 2){
        KpsPoint p0 = points[i];
        KpsPoint p1 = points[i+1];

        if(p1.x < p0.x)
            swap(p0,p1);
        //cout << "PAIR:" << p0 << p1 << "\n";
        pairs.push_front(make_pair(p0,p1));

    }

    if (points.size() % 2 == 1){
        candidates.push_back(points[points.size()-1]);
    }

    for (auto pair : pairs){
        KpsPoint p0 = pair.first;
        KpsPoint p1 = pair.second;

        if(abs(p0.x - p1.x) < ERROR){
            KpsPoint toInsert = p0.y > p1.y ? p0 : p1;
            candidates.push_back(toInsert);
        }
        else{
            new_pairs.push_back(pair);
            slopes.push_back((p0.y-p1.y)/(p0.x-p1.x));
        }
    }
    //pairs = new_pairs;
    coordinate k = find_median(slopes);

    list<pair<KpsPoint,KpsPoint>> small ;
    list<pair<KpsPoint,KpsPoint>> equal_list;
    list<pair<KpsPoint,KpsPoint>> large;

    for(auto pair : new_pairs){
        KpsPoint p0 = pair.first;
        KpsPoint p1 = pair.second;

        coordinate slope = (p0.y - p1.y) / (p0.x - p1.x);

        if (abs(slope - k) < ERROR){
            equal_list.push_front(pair);
        }
        else if (slope > k){
            large.push_front(pair);
        }
        else{
            small.push_front(pair);
        }
    }

    vector<KpsPoint> max_points;
    max_points.push_back(points[0]);
    for ( auto i : points ){
        if(i.y - k*i.x > max_points[0].y - k*max_points[0].x){
            max_points.clear();
            max_points.push_back(i);
        }
        if(abs(i.y - k*i.x - max_points[0].y + k*max_points[0].x) < ERROR){
            //max_points.clear();
            max_points.push_back(i);
        }
    }

    KpsPoint pk = max_points[0], pm = max_points[0];
    for( auto i : max_points){
        if (i.x < pk.x){ pk = i; }
        if (i.x > pm.x){ pm = i; }
    }

    if (pk.x <= l_x && pm.x > l_x){
        cout << "Bridge = " << pk << pm << "\n";
        return vector<KpsPoint>{pk,pm};
    }

    if( pm.x <= l_x ){
        for(auto paired : large){
            candidates.push_back(paired.second);
        }

        for(auto paired : equal_list){
            candidates.push_back(paired.second);
        }
        for(auto paired : small){
            candidates.push_back(paired.first);
            candidates.push_back(paired.second);
        }
    }

    if( pk.x > l_x ){
        for(auto paired : large){
            candidates.push_back(paired.first);
            candidates.push_back(paired.second);
        }

        for(auto paired : equal_list){
            candidates.push_back(paired.first);
        }

        for(auto paired : small){
            candidates.push_back(paired.first);
        }
    }

    return upperBridge(candidates, l_x);
}

vector<KirkpatrickSiedel::KpsPoint> KirkpatrickSiedel::lowerHull(vector<KpsPoint> points) {
    for(int i = 0; i < points.size(); i++){
        points[i].y *= -1;
    }

    vector<KpsPoint> inverted_hull = upperHull(points,true);

    for(int i = 0; i < inverted_hull.size(); i++){
        inverted_hull[i].y *= -1;
    }

    return inverted_hull;
    //return vector<Point>();
}

KirkpatrickSiedel::KirkpatrickSiedel(vector<Point> v) {
    KpsPoint::MAX = KpsPoint(Point(numeric_limits<float>::max(),
                                   numeric_limits<float>::max()) );

    points.reserve(v.size());
    for (auto p : v){
        points.push_back(KpsPoint(p));
    }
}

vector<Point> KirkpatrickSiedel::compute() {
//    return vector<Point>();
    KpsPoint p_umin = points[0];
    KpsPoint p_umax = points[0];
    KpsPoint p_lmin = points[0];
    KpsPoint p_lmax = points[0];

    for (auto p : points){
        if((p.x < p_umin.x) || (p.x == p_umin.x && p.y > p_umin.y)){
            p_umin = p;
        }

        if((p.x > p_umax.x) || (p.x == p_umax.x && p.y > p_umax.y)){
            p_umax = p;
        }

        if((p.x < p_lmin.x) || (p.x == p_lmin.x && p.y < p_lmin.y)){
            p_lmin = p;
        }

        if((p.x > p_lmax.x) || (p.x == p_lmax.x && p.y < p_lmax.y)){
            p_lmax = p;
        }
    }

    LineSegment upper_segment(p_umin,p_umax), lower_segment(p_lmin,p_lmax);

    vector<KpsPoint> upper_points, lower_points;

    upper_points.push_back(p_umax);
    upper_points.push_back(p_umin);

    lower_points.push_back(p_lmax);
    lower_points.push_back(p_lmin);

    for (auto p : points){
        Point upper_proj = upper_segment.vertical_projection(p);
        if(!upper_proj.is_nan() && p.y > upper_proj.y){
            upper_points.push_back(p);
        }

        Point lower_proj = lower_segment.vertical_projection(p);
        if(!lower_proj.is_nan() && p.y < lower_proj.y){
            lower_points.push_back(p);
        }
    }

    // Call upper Hull
    vector<KpsPoint> upper_ch = upperHull(upper_points,true);

    // Call lower Hull
    vector<KpsPoint> lower_ch = lowerHull(lower_points);

    // return Points
    vector<Point> hull;
    for(int i = 0; i <  upper_ch.size();i++){hull.push_back(upper_points[i].getPoint());}
    for(int i = lower_ch.size() -1 ; i >= 0;i--){hull.push_back(lower_points[i].getPoint());}

    return hull;
}

KirkpatrickSiedel::KpsPoint::KpsPoint(Point p) {
    this->x = p.x;
    this->y = p.y;
}

bool KirkpatrickSiedel::KpsPoint::operator<(KirkpatrickSiedel::KpsPoint &p) {
    return this->x < p.x;
}

bool KirkpatrickSiedel::KpsPoint::operator<=(KirkpatrickSiedel::KpsPoint &p) {
    return !(p.x < this->x);
}


Point KirkpatrickSiedel::KpsPoint::getPoint() {
    return Point(x,y);
}

KirkpatrickSiedel::KpsPoint KirkpatrickSiedel::KpsPoint::MAX(Point(numeric_limits<float>::max(),
                               numeric_limits<float>::max()));