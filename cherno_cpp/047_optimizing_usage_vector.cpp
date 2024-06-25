#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
    float x, y, z;

    Vertex(float x, float y, float z)
        : x(x), y(y), z(z)
    {

    }

    Vertex(const Vertex& vertex)
        : x(vertex.x), y(vertex.y), z(vertex.z)
    {
        std::cout << "Copied!" << std::endl;
    }
};

int main()
{   
    // exponentially  

    // push_back  
        // 当使用 push_back() 将对象添加到容器时，通常会涉及元素的移动构造或者拷贝构造。
        // push_back() 接受一个对象，然后将这个对象拷贝或者移动到容器中。
    // emplace_back  
        // emplace_back() 直接在容器的尾部构造一个新对象，而不需要拷贝或者移动。
        // 这是通过将参数传递给对象的构造函数来实现的，这个构造函数在容器内部被调用，因此不需要进行额外的拷贝或者移动操作。

    std::vector<Vertex> vertices;
    vertices.reserve(3);
    vertices.push_back({ 1, 2, 3});
    vertices.push_back({ 4, 5, 6});
    vertices.push_back(Vertex(7, 8, 9));

    int capacity = vertices.capacity();

    vertices.emplace_back(1, 2, 3);
    vertices.emplace_back(4, 5, 6);
    vertices.emplace_back(Vertex(7, 8, 9));

    capacity = vertices.capacity();

    std::cin.get();

}