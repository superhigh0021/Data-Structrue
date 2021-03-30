#include <iostream>
using namespace std;
#define maxlength 20

template <typename T>
class List
{
public:
    List();
    List(T a[], int n);
    int size()
    {
        return count;
    }
    T get_element(const int &i) const;
    int locate(const T &x);
    void insert(const int &i, const T &x);
    void Delete(const int &i);
    void PrintTest();
    void SortInsert(const T &target);
    void DeleteSame();
    void MinusSet(List<T> &l);

private:
    int count = 0;
    T data[maxlength];
};

template <typename T>
List<T>::List(T a[], int n)
{
    if (n > maxlength)
    {
        cout << "overflow!" << endl;
        return;
    }
    for (int i = 0; i < n; ++i)
    {
        data[i] = a[i];
        count++;
    }
}

template <typename T>
T List<T>::get_element(const int &i) const
{
    if (i < 0 || i >= count)
        return;
    return data[i];
}

template <typename T>
int List<T>::locate(const T &x)
{
    for (int i = 0; i < size(); ++i)
        if (data[i] == x)
            return (i);
    return -1;
}

template <typename T>
void List<T>::insert(const int &i, const T &x)
{
    if (count == maxlength)
        return;
    if (i < 0 || i >= size())
        return;
    if (i == count - 1)
    {
        count++;
        data[count - 1] = x;
        return;
    }
    count++;
    for (int j = count - 1; j > i; --j)
        data[j] = data[j - 1];
    data[i] = x;
}

template <typename T>
void List<T>::Delete(const int &i)
{
    if (size() == 0)
        return;
    if (i < 1 || i > size())
        return;
    for (int j = i + 2; j < count + 1; ++j)
        data[j - 2] = data[j - 1];
    count--;
}

template <typename T>
void List<T>::PrintTest()
{
    for (int i = 0; i < count; ++i)
        cout << data[i] << ' ';
}

template <typename T>
void List<T>::SortInsert(const T &target)
{
    int boder = count - 1;
    int lo = 0, hi = boder;
    while (lo < hi)
    {
        if (hi - lo == 1)
        {
            this->insert(hi, target);
            return;
        }
        int mi = (lo + hi) >> 1;
        if (data[mi] < target)
            lo = mi;
        else if (data[mi] > target)
            hi = mi;
        else
        {
            cout << "already existed!";
            return;
        }
    }
}

template <typename T>
void List<T>::DeleteSame()
{
    T cnt = data[0];
    for (int i = 1; i < count; ++i)
    {
        while (data[i] == cnt)
            this->Delete(i);
        cnt = data[i];
    }
}

template <typename T>
void List<T>::MinusSet(List<T> &l)
{
    for(int i=0;i<this->count;++i){
        if(l.locate(data[i])!=-1)
        this->Delete(i);
    }
}