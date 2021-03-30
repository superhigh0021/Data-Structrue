#include <iostream>
using namespace std;
#define maxlength 10

template <typename T>
class List
{
public:
    List();
    int size()
    {
        return count;
    }
    T get_element(const int &i) const;
    int locate(const T &x);
    void insert(const int &i, const T &x);
    void Delete(const int &i);

private:
    int count;
    T data[maxlength];
};

template <typename T>
List<T>::List()
{
    count = 0;
}

template <typename T>
T List<T>::get_element(const int &i) const
{
    if (i <= 0 || i > count)
        exit(0);
    return data[i - 1];
}

template <typename T>
int List<T>::locate(const T &x)
{
    for (int i = 0; i < size(); ++i)
        if (data[i] == x)
            return (i + 1);
    return 0;
}

template <typename T>
void List<T>::insert(const int &i, const T &x)
{
    if (count == maxlength)
        exit(0);
    if (i < 1 || i > size() + 1)
        exit(0);
    for (int j = count; j >= i; --j)
        data[j] = data[j - 1];
    data[i - 1] = x;
    count++;
}

template<typename T>
void List<T>::Delete(const int& i){
    if(size()==0) return;
}