#include<iostream>
#include "primitives.h"
#include "GrahamScan.h"
#include "JarvisMarch.h"

using namespace std;

int main(){
    
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
    JarvisMarch jar_march(points);
    jar_march.compute_convex_hull();
    vector<Point> result;
    result = jar_march.get_ch_points();

    for(auto pt: result)
        cout << pt << endl;

    return 0;
}