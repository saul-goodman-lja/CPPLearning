#include <iostream>
#include <string>

class Example
{
public:
    Example()
    {
        std::cout << "Created Entity" << std::endl;
    }

    Example(int x)
    {
        std::cout << "Created Entity with " << x << std::endl;
    }
};

class Entity
{
private:
    std::string m_Name;
    Example m_Example;
public:
    // default constructor
    Entity()
        : m_Name("unknown"), m_Example(Example(8))
    {
    }

    Entity(const std::string& name)
        : m_Name(name)
    {
    }
};

int main()
{   
    Entity e;

    std::cin.get();
}