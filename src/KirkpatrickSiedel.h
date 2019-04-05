#ifndef CONVEX_HULL_KIRKPATRICKSIEDEL_H
#define CONVEX_HULL_KIRKPATRICKSIEDEL_H

#include <vector>
#include "primitives.h"
#include "ConvexHullGraphix.h"

using namespace std;
class KirkpatrickSiedel {
public:
    ConvexHullGraphix* chGfx;
    class KpsPoint : public Point{
    public:
        /** constructor
        *@param p 
        */
        KpsPoint(Point p);

        bool operator< (KpsPoint& );
        bool operator<=(KpsPoint& );
        
        static KpsPoint MAX;
        Point getPoint();
    };

    KirkpatrickSiedel(vector<Point> v, ConvexHullGraphix* = NULL);

    vector<Point> compute();
private:
    bool visualise;

    vector<KpsPoint> points;

    vector<KpsPoint> upperHull(vector<KpsPoint> points,bool upper);
    vector<KpsPoint> upperBridge(vector<KpsPoint> points, coordinate x);

    vector<KpsPoint> lowerHull(vector<KpsPoint> points);

};

#endif //CONVEX_HULL_KIRKPATRICKSIEDEL_H
