/**@file main.cpp
 * @author Kaustubh Welankar
 * @author Basu Dubey
 * @author Syed Abid Abdullah
 * @brief Design and Analysis of Algorithms
 * \mainpage Description
 * This is an implementation of three convex hull algorithms
 * \section Instructions
 * Consult readme.md
 * \section Authors
 * \verbatim
  Basu Dubey			2016A7PS0136H
  Kaustubh Welankar		2016A7PS0095H
  Syed Abid Abdullah 	2016A7PS0562H
  \endverbatim
 */
#include<iostream>
#include<mutex>
#include<thread>
#include<fstream>
#include "primitives.h"
#include "GrahamScan.h"
#include "JarvisMarch.h"
#include "ConvexHullGraphix.h"
#include "KirkpatrickSiedel.h"
#include "median_finding.cpp"
#include <chrono> 

using namespace std::chrono; 

#define VISUALISE false
#define DEFAULT_FILENAME "../testcases/input3.txt"

using namespace std;

void init_graphix_class(ConvexHullGraphix* x){
    x->loopie();
}

void get_lines_from_file(string filename, vector<Point>& points){
    points.clear();
    ifstream fin;
    fin.open(filename, ios::in);
    string pt_str;
    string comma = ",";
    while(fin >> pt_str){
        pt_str = pt_str.substr(1, pt_str.size() - 2);
        string p1_x = pt_str.substr(0,pt_str.find(comma));
        string p1_y = pt_str.substr(pt_str.find(comma) + 1, pt_str.size());
        Point pt(stold(p1_x), stold(p1_y));
        points.push_back(pt);
    }
    fin.close();
}

int main(int argc, char** argv){
    
    std::mutex mtx;
    ConvexHullGraphix* gfx_ptr;
    thread* gfx_thread;
    if(VISUALISE){
        gfx_ptr = new ConvexHullGraphix(mtx);
        gfx_thread = new thread(init_graphix_class, gfx_ptr);
    } else {
        gfx_ptr = NULL;
    }

    string filename;
    if(argc > 1){
        filename = argv[1];
        cout << filename << endl;
    } else {
        filename = DEFAULT_FILENAME;
    }
    vector<Point> points;
    get_lines_from_file(filename, points);

    cout << "Input Points: " << endl;
    for(auto i: points){
        cout << i << ", " << endl;
    }
    cout << "------------" << endl;

    auto start = high_resolution_clock::now();
    /* Graham's Scan */
    GrahamScan gh_scan(points, gfx_ptr);
    gh_scan.compute_convex_hull();
    vector<PolarPoint> result_graham;
    result_graham = gh_scan.get_ch_points();
	cout << "Graham points: " << endl;
    for(auto pt: result_graham){
        cout << pt << endl;
    }
    cout <<"\n";
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "GrahamScan time: " << duration.count() << endl; 
    cout << "=====================================\n";

    start = high_resolution_clock::now();
    // // /* Jarvis March */
    cout << "Jarvis March\n";
    JarvisMarch jar_march(points, gfx_ptr);
    jar_march.compute_convex_hull();
    vector<Point> result_jarvis;
    result_jarvis = jar_march.get_ch_points();
    for(auto pt: result_jarvis){
        cout << pt << endl;
    }
    cout <<"\n";

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "JarvisMarch time: " << duration.count() << endl; 
    cout << "=====================================\n";

    start = high_resolution_clock::now();
    // /* KirkpatrickSiedel */
    cout << "KPS\n";
    KirkpatrickSiedel kps(points, gfx_ptr);
    vector<Point> result_kps = kps.compute();
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    


     // Print Result 
    cout << "Convex Hull points: " << endl;
    for(auto pt: result_kps){
        cout << pt << endl;
    }
    cout << "KPS time: " << duration.count() << endl;


    // KirkpatrickSiedel::KpsPoint p1(Point(-5,-2)), p2(Point(-1,-1)), p3(Point(-1,1));
    // vector<KirkpatrickSiedel::KpsPoint> arr{p1,p2,p3};
    // KirkpatrickSiedel k(vector<Point>(),NULL);
    // vector<KirkpatrickSiedel::KpsPoint> p = k.upperBridge(arr,-1);
    // cout << p[0] << p[1] << "\n";

    if(VISUALISE) gfx_thread -> join();

    return 0;
}
