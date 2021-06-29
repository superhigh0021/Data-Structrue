/*����һ�������� Elevator������˽�����ݳ�Ա���ͺ� id ���ۼ� price����
���� pElevator �����ͺź��ۼ��⣬�������������ԣ�����ؿ���
passenger_load�������� cElevator �����ͺź��ۼ��⣬�������������ԣ�
����ػ����� cargo_load���ͻ������� dElevator ���������������ԡ���
дһ��������ȷ��������֮��ļ̳й�ϵ�����ܹ���ȡ��λ���أ���
�ͻ��ػ����۸��������⣩��
ע�⣺ʹ������������������⣻Ϊ�������д���캯����*/

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