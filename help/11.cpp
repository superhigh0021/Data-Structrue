#include <iostream>
using namespace std;
#include <cmath>

class Point {
public:
    float x, y;
    Point(float a, float b)
        : x(a)
        , y(b)
    {
    }
};

class Rectangle {
public:
    Point p1, p2;
    Rectangle();
    Rectangle(Point pa, Point pb)
        : p1(pa)
        , p2(pb)
    {
    }
    bool isRect()
    {
        if (p1.x == p2.x || p1.y == p2.y) {
            return false;
        } else {
            return true;
        }
    }
    virtual float gets()
    {
        if (isRect()) {
            float s = abs((p1.x - p2.x) * (p1.y - p2.y));
            return s;
        } else {
            return -1;
        }
    }
};

class Cuboid : public Rectangle {
public:
    Point p3;
    Cuboid(Point pa, Point pb, Point pc)
        : Rectangle(pa, pb),p3(pc){}
    float get(const Point& p1, const Point& p2)
    {
        return abs((p1.x - p2.x) * (p1.y - p2.y));
    }
    float area()
    {
        return 2 * (get(p1, p2) + get(p1, p3) + get(p2, p3));
    }
    float volume(){
        return get(p1,p2)*(p3.y-p2.y);
    }
};

int main(void)
{
    system("pause");
    return 0;
}