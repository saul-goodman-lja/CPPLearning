#include<iostream>

using std::cout;
using std::endl;

class Base
{     
public:
	Base(int n)
	{
		cout <<"Constucting base class" << endl;
		_ix=n;
	}
	

    ~Base()
    {
    	cout <<"Destructing base class" << endl;
    }
    
    void showX()
    {
    	cout << _ix << ",";
    }
    
    int getX()
    {
    	return _ix;
    }

private:
	int _ix;
};

class Derived
:public Base
{     
public:
	Derived(int n, int m, int p)
	: Base(m)
	, _base(p)
	{
		cout << "Constructing derived class" <<endl;
        j = n;
    }

    ~Derived()
    {
    	cout <<"Destructing derived class"<<endl;
    }
    
    void show()
    {
    	Base::showX();
        cout << j << "," << _base.getX() << endl;
    }

private:
	int j;
    Base _base;
};
int main()
{ 
	Derived obj(8,13,24);
 	obj.show();

	return 0;

}