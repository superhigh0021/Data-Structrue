#include <iostream>
using namespace std;
#define maxlength 20

template <typename T>
class List {
public:
    List();
    List(T a[], int n);
    int size()
    {
        return count;
    }
    T get_element(const int& i) const;
    int locate(const T& x);
    void insert(const int& i, const T& x);
    void Delete(const int& i);
    void PrintTest();

private:
    int count=0;
    T data[maxlength];
};

template <typename T>
List<T>::List(T a[], int n)
{
    if (n > maxlength) {
        cout << "overflow!" << endl;
        exit(0);
    }
    for (int i = 0; i < n; ++i) {
        data[i] = a[i];
        count++;
    }
}

template <typename T>
T List<T>::get_element(const int& i) const
{
    if (i < 0 || i >= count)
        exit(0);
    return data[i];
}

template <typename T>
int List<T>::locate(const T& x)
{
    for (int i = 0; i < size(); ++i)
        if (data[i] == x)
            return (i);
    return -1;
}

template <typename T>
void List<T>::insert(const int& i, const T& x)
{
    if (count == maxlength)
        exit(0);
    if (i < 0 || i >= size())
        exit(0);
    count++;
    for (int j = count-1; j > i; --j)
        data[j] = data[j - 1];
    data[i] = x;
}

template <typename T>
void List<T>::Delete(const int& i)
{
    if (size() == 0)
        exit(0);
    if (i < 1 || i > size())
        exit(0);
    for (int j = i + 2; j < count+1; ++j)
        data[j - 2] = data[j - 1];
    count--;
}

template <typename T>
void List<T>::PrintTest()
{
    for (int i = 0; i < count; ++i)
        cout << data[i] << ' ';
}