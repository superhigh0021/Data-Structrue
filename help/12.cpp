/*设有一个电梯类 Elevator，包括私有数据成员：型号 id 和售价 price。客
梯类 pElevator 除了型号和售价外，还包括新增属性：最大载客数
passenger_load。货梯类 cElevator 除了型号和售价外，还包括新增属性：
最大载货重量 cargo_load。客货两用类 dElevator 包含上述所有属性。编
写一个程序，明确上述各类之间的继承关系，并能够求取单位承载（载
客或载货）价格（数据自拟）。
注意：使用虚基类解决二义性问题；为派生类编写构造函数。*/

#include <iostream>
using namespace std;

class Elevator {
public:
    Elevator(string id, int price): id(id), price(price){}

private:
    string id;
    int price;
};

class pElevator : virtual public Elevator {
public:
    pElevator(string id, int price, int passenger_load): Elevator(id, price), passenger_load(passenger_load){}

private:
    int passenger_load;
};

class cElevator : virtual public Elevator {
public:
    cElevator(string id, int price, int cargo_load): Elevator(id, price), cargo_load(cargo_load){}

private:
    int cargo_load;
};

class dElevator : public pElevator, public cElevator {
public:
    dElevator(string id,int price,int passenger_load,int cargo_load):Elevator(id,price),pElevator(id,price,passenger_load),cElevator(id,price,cargo_load){}

};

int main(void)
{

    system("pause");
    return 0;
}