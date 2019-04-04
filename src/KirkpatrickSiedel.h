#ifndef CONVEX_HULL_KIRKPATRICKSIEDEL_H
#define CONVEX_HULL_KIRKPATRICKSIEDEL_H

#include <vector>
#include "primitives.h"

using namespace std;
class KirkpatrickSiedel {
public:

    class KpsPoint : public Point{
    public:
        KpsPoint(Point p);
        bool operator< (KpsPoint& );
        bool operator<=(KpsPoint& );
        static KpsPoint MAX;
        Point getPoint();
    };

    KirkpatrickSiedel(vector<Point> v);

    vector<Point> compute();
private:

    vector<KpsPoint> points;

    vector<KpsPoint> upperHull(vector<KpsPoint> points,bool upper);
    vector<KpsPoint> upperBridge(vector<KpsPoint> points, coordinate x);

    vector<KpsPoint> lowerHull(vector<KpsPoint> points);

};



#endif //CONVEX_HULL_KIRKPATRICKSIEDEL_H
