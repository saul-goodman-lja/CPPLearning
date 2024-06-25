#include <iostream>
#include <vector>

struct Vertex
{
    float x, y, z;
};

std::ostream& operator<<(std::ostream& stream, const Vertex& vertex)
{
    stream << vertex.x << ", " << vertex.y << ", " << vertex.z;
    return stream;
}

void Function(const std::vector<Vertex>& vertices)
{

}

int main()
{   
    std::vector<Vertex> vertices;
    vertices.push_back({1, 2, 3});
    vertices.push_back({4, 5, 6});
    Function(vertices);
    
    for(int i = 0; i < vertices.size(); i++)
        std::cout << vertices[i] << std::endl;

    for(const Vertex& v : vertices)
        std::cout << v << std::endl;

    for(const auto& v : vertices)
        std::cout << v << std::endl;

    vertices.erase(vertices.begin() + 1);

    vertices.clear();

    std::cin.get();
}