#include <iostream>
#include <ostream>
#include <string>

class Entity
{
private:
    int x;
public:
    Entity() 
    {
        std::cout << "Created Entity!" << std::endl;
    }
    ~Entity()
    {
        std::cout << "Destroy Entity!" << std::endl;
    }
};

class ScopePtr
{
private:
    Entity *m_Ptr;
public:
    explicit ScopePtr(Entity *ptr)
        : m_Ptr(ptr)
    {

    }

    ~ScopePtr()
    {
        delete m_Ptr;
    }

};

int *CreateArray()
{
    int *array = new int[50];
    return array;
}
// examples 
// timer time class , auto calculate time
// mutex locking  lock function
int main()
{       
    // empty scope
    {   
        ScopePtr e0 = new Entity();
        ScopePtr e_explicit(new Entity());
        Entity e;
        Entity *e1 = new Entity();
    }

    std::cin.get();
}