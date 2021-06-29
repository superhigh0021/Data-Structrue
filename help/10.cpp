/* �ڵ� 5 ������д�� Complex ��������һ������ת��������ʹ�� Complex
���͵Ķ����ܹ��� Point ���͵Ķ�����кϷ����� */

#include <iostream>
using namespace std;

class Point {
public:
    float x, y; //Բ������
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
    //�Ȱ�Complex����cǿ��ת��ΪPoint�Ķ�����������һ�����ţ�Ȼ���ٵ�x����Ȼ�����Complex���µĳ�Ա
    cout<<p.x+((Point)c).x;

    system("pause");
    return 0;
}
