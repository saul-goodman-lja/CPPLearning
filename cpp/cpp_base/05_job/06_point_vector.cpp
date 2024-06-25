#include <iostream>
#include <vector>
using std::cin, std::cout, std::endl;
using std::vector;

class Point{

public:
    Point(int x = 0, int y = 0) : _x(x), _y(y) {}
    
    void print(){
        cout << "x = " << _x << ", y = " << _y << endl;
    }

private:
    int _x;
    int _y;
};

int main(void){
    vector<Point> pointSet;
    pointSet.reserve(10);
    for(int i = 0; i < 5; i++){
        pointSet.emplace_back(i, i+1);
        pointSet.emplace_back(Point(i, i + 2));
    }

    for(auto & point : pointSet){
        point.print();
    }

    // for(auto it = pointSet.begin(); it != pointSet.end(); it++){
    //     it->print();
    // }
}