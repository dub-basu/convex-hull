#include<iostream>
#include<mutex>
#include<thread>
#include "primitives.h"
#include "GrahamScan.h"
#include "JarvisMarch.h"
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
    // Point p1(1,1);
    // Point p2(2,2);
    // Point p3(3,3);
    // Point p4(4,4);
    // Point p5(5,5);
    // Point p6(6,6);

    Point p1(1,1);
    Point p2(0,2);
    Point p3(-1,1);
    Point p4(-1,-1);
    Point p5(0,3);
    Point p6(1,-1);

    // TODO: Case fails for Graham's Scan. Fix.
    // Point p1(-1,1);
    // Point p2(-0.5,0.5);
    // Point p3(0,0);
    // Point p4(-1,-1);
    // Point p5(1,-1);
    // Point p6(1,1);
    // Point p7(2,0);
    // Point p8(0,-1);
    
    vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
    // points.push_back(p7);
    // points.push_back(p8);

    
    /* Graham's Scan */
    // GrahamScan gh_scan(points);
    // gh_scan.compute_convex_hull();
    // vector<PolarPoint> result;
    // result = gh_scan.get_ch_points();

    /* Jarvis March */
    JarvisMarch jar_march(points, gfx_ptr);
    jar_march.compute_convex_hull();
    vector<Point> result;
    result = jar_march.get_ch_points();

    for(auto pt: result)
        cout << pt << endl;

    if(VISUALISE) gfx_thread -> join();

    return 0;
}
