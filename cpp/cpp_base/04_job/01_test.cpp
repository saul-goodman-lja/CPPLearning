#include <iostream>
using std::cout, std::endl;
int i = 1;

class Test
{
public:
	Test()
	:_fourth(_third)
	,_second(i++)
	,_first(i++)
	,_third(i++)
	{
		_third = i;
	}
	void print()
	{  
		cout << "result : " << _first + _second + _third + _fourth << endl;
	}
private:
	int _first;
	int _second;
	int _third;
	int &_fourth;
};

int main()
{
	Test test;
	test.print();
	
	return 0;
}