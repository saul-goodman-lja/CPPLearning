#include<iostream>

using std::cout;
using std::endl;

class Point
{   
public:
    Point(int a=0, int b=0) 
	{
		x = a; 
		y = b;
	}
    void move(int xoffset,int yoffset) 
	{
		x += xoffset; 
		y += yoffset;
	}
	

    int getx() 
    {	
    	return x;	
    }
    
    int gety() 
    {	
    	return y;	
    }

private:
	int x,y;
};

class Rectangle
:public Point
{    
public:
	Rectangle(int x, int y, int l, int w)
	: Point(x,y)
	{   
		length = l;
		width  = w;
	}
	

	int getLength()
	{	
		return length;	
	}
	
	int getWidth()	
	{	
		return width;	
	}

private:
	int length;
	int width;
};
int main()
{ 
	Rectangle r(0, 0, 8,4);
 	r.move(23,56);
	cout << r.getx() 
	     << "," << r.gety() 
		 << "," << r.getLength() 
		 << "," << r.getWidth() << endl;
		 

	return 0;

}