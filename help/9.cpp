/*实现一个名为 Circle 的圆类，并规定其数据成员 float *radius 为指向半径
值的指针。以 Point 类的对象指针作为另一个数据成员，表示圆心位置。
定义一个判别两圆位置关系（相交/外离/内含/内切/外切）的函数。
注意：使用函数指针调用函数，熟悉各类指针的用法*/

#include <iostream>
#include <cmath>
using namespace std;

class Point {
public:
    float x, y; //圆心坐标
};

class Circle {
public:
    float Radius;
    float* radius = &Radius;
    Point point;
    Circle(float x, float y, float r):Radius(r)
    {
        point.x = x;
        point.y = y;
    }
};

float _distance(const Point& p, const Point& q)
{
    //求圆心之间的距离平方的函数
    return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
}

void Judge(const Circle& a, const Circle& b)
{
    float distance = _distance(a.point, b.point);
    if (distance < fabs(*(a.radius) - *(b.radius))) {
        cout << "两圆内含"<<endl;
        return;
    }
    if (distance > *(a.radius) + *(b.radius)) {
        cout << "两圆外离"<<endl;
        return;
    }
    if (distance < *(a.radius) + *(b.radius)) {
        cout << "两圆相交"<<endl;
        return;
    }
    if (distance == fabs(*(a.radius) - *(b.radius))) {
        cout << "两圆内切"<<endl;
        return;
    }
    cout << "两圆外切"<<endl;
}

int main(void)
{

    Circle a(0, 0, 1);
    Circle b(0, 1, 100);

    void (*Func)(const Circle& a, const Circle& b);
    Func=Judge;
    (*Func)(a, b);
    //此处用函数指针调用Judge函数

    system("pause");
    return 0;
}