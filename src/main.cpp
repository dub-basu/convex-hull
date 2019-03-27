#include<iostream>
#include "primitives.h"

using namespace std;

int main(){
    
    Point p1(0,2);
    Point p2(1,1);

    PolarPoint pp1(p2, p1);
    cout << "x = " << pp1.x << ", " << "y = " << pp1.y << endl;
    cout << "P distance = " << pp1.get_p_distance() << ", " << "P_angle = " << pp1.get_p_angle_degrees() << endl;

    return 0;
}