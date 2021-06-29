/* 在第 5 题所编写的 Complex 类中增加一个类型转换函数，使得 Complex
类型的对象能够与 Point 类型的对象进行合法操作 */

#include <iostream>
using namespace std;

class Point {
public:
    float x, y; //圆心坐标
    Point(float a,float b):x(a),y(b){}
};

class Complex {
public: //a+bi
    float a, b;
    Complex(float m, float n): a(m), b(n){}
    void multiply(Complex q)
    {
        a = a * q.a - b * q.b;
        b = b * q.a + a * q.b;
    }
    void print()
    {
        cout << a << '+' << b << 'i' << endl;
    }
    operator Point(){
        return Point(a,b);
    }
};

int main(void){
    Point p(1,3);
    Complex c(2,4);
    //先把Complex对象c强制转换为Point的对象，外面必须加一个括号，然后再点x，不然会调用Complex底下的成员
    cout<<p.x+((Point)c).x;

    system("pause");
    return 0;
}
