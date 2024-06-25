#include <iostream>
#include <string>

class Entity
{
private:
    std::string m_Name;
    int m_Age;
public:
    explicit Entity(const std::string& name)
        : m_Name(name), m_Age(-1) {}
    
    explicit Entity(int age)
        : m_Name("Unknown"), m_Age(age) {}
};

void PrintEntity(const Entity& entity)
{
    
}

int main()
{   

    PrintEntity(22);
    PrintEntity((std::string)"cherno");

    Entity a("cherno");
    Entity a1 = Entity("cherno");
    Entity a2 = (std::string)"Cherno";
    
    Entity b = Entity(22);
    Entity b1 = 22;
    Entity b2(22);

    std::cin.get();
}