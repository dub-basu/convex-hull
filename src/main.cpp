#include<iostream>
#include<mutex>
#include<thread>
#include "primitives.h"
#include "GrahamScan.h"
#include "JarvisMarch.h"
#include "KirkpatrickSiedel.h"
#include "median_finding.cpp"
#include "ConvexHullGraphix.h"

#define VISUALISE true

using namespace std;

void init_graphix_class(ConvexHullGraphix* x){
    x->loopie();
}

int main(){
    
    std::mutex mtx;
    ConvexHullGraphix* gfx_ptr;
    thread* gfx_thread;
    if(VISUALISE){
        gfx_ptr = new ConvexHullGraphix(mtx);
        gfx_thread = new thread(init_graphix_class, gfx_ptr);
    } else {
        gfx_ptr = NULL;
    }

    // TODO: Case fails for Jarvis March. Fix.
//     Point p1(1,1);
//     Point p2(2,2);
//     Point p3(3,3);
//     Point p4(4,4);
//     Point p5(5,5);
//     Point p6(6,6);
//
//    Point p1(1,1);
//    Point p2(0,2);
//    Point p3(-1,1);
//    Point p4(-1,-1);
//    Point p5(0,3);
//    Point p6(1,-1);
//
//    // TODO: Case fails for Graham's Scan. Fix.
//     Point p1(-6,0);
//     Point p2(-4,2);
//     Point p3(0,0);
//     Point p4(1,5);
//     Point p5(1.5,3);
//     Point p6(1.6,1);
//     Point p7(2,4);
//     Point p8(6,0);
//
//    vector<Point> points;
//    points.push_back(p1);
//    points.push_back(p2);
//    points.push_back(p3);
//    points.push_back(p4);
//    points.push_back(p5);
//    points.push_back(p6);
//    points.push_back(p7);
//    points.push_back(p8);

    Point p1(1,5);
    Point p2(3,8);
    Point p3(5,5);
    Point p4(5,1);
    Point p5(1,1);
    Point p6(3,4);
    Point p7(1.5,4);
    vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
    points.push_back(p7);


//
//    /* Graham's Scan */
//    // GrahamScan gh_scan(points);
//    // gh_scan.compute_convex_hull();
//    // vector<PolarPoint> result;
//    // result = gh_scan.get_ch_points();
//
//    /* Jarvis March */
//    JarvisMarch jar_march(points);
//    jar_march.compute_convex_hull();
//    vector<Point> result;
//    result = jar_march.get_ch_points();
//
//    for(auto pt: result)
//        cout << pt << endl;
//
//    return 0;
//
//    vector<int> a {1,2,3,4};
//    //for(int i = 0; i < 456262; i++){ a.push_back(i); }
//    //random_shuffle(a.begin(), a.end());

    KirkpatrickSiedel kps(points);
    vector<Point> hull = kps.compute();

    for(auto p : hull){
        cout << p;
    }
    cout << "\n";


}
