/*ʵ��һ����Ϊ Circle ��Բ�࣬���涨�����ݳ�Ա float *radius Ϊָ��뾶
ֵ��ָ�롣�� Point ��Ķ���ָ����Ϊ��һ�����ݳ�Ա����ʾԲ��λ�á�
����һ���б���Բλ�ù�ϵ���ཻ/����/�ں�/����/���У��ĺ�����
ע�⣺ʹ�ú���ָ����ú�������Ϥ����ָ����÷�*/

#include <iostream>
#include <cmath>
using namespace std;

class Point {
public:
    float x, y; //Բ������
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
    //��Բ��֮��ľ���ƽ���ĺ���
    return sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2));
}

void Judge(const Circle& a, const Circle& b)
{
    float distance = _distance(a.point, b.point);
    if (distance < fabs(*(a.radius) - *(b.radius))) {
        cout << "��Բ�ں�"<<endl;
        return;
    }
    if (distance > *(a.radius) + *(b.radius)) {
        cout << "��Բ����"<<endl;
        return;
    }
    if (distance < *(a.radius) + *(b.radius)) {
        cout << "��Բ�ཻ"<<endl;
        return;
    }
    if (distance == fabs(*(a.radius) - *(b.radius))) {
        cout << "��Բ����"<<endl;
        return;
    }
    cout << "��Բ����"<<endl;
}

int main(void)
{

    Circle a(0, 0, 1);
    Circle b(0, 1, 100);

    void (*Func)(const Circle& a, const Circle& b);
    Func=Judge;
    (*Func)(a, b);
    //�˴��ú���ָ�����Judge����

    system("pause");
    return 0;
}