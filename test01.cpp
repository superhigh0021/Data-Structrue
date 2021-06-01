#include <iostream>
using namespace std;
#include <stack>

stack<int> *ht(int s)
{
	stack<int> *S;
	S->empty();
	return S;
}

int main(void)
{
	int s = 0;
	ht(s);

	system("pause");
	return 0;
}