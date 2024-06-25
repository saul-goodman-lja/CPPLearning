#include <iostream>
#include <memory>
#include <string>

class Entity
{
public:
    Entity()
    {
        std::cout << "Create Entity!" << std::endl;
    }

    ~Entity()
    {
        std::cout << "Destroyed Entity!" << std::endl;
    }

    void Print() const { std::cout << "Hello!" << std::endl; }

};

class ScopePtr
{
private:
    Entity *m_Obj;
public:
    ScopePtr(Entity *entity)
        : m_Obj(entity)
    {

    }

    ~ScopePtr()
    {
        delete m_Obj;
    }

    Entity *GetObject() { return m_Obj; }

    const Entity *operator->() const
    {
        return m_Obj;
    }
};

struct Vector3
{
    float x, y, z;
};

int main()
{   
    long offset = (long)&((Vector3 *)nullptr)->z;

    ScopePtr entity = new Entity();
    // entity.GetObject()->Print(); 
    entity->Print();
    const Entity *e = (entity->Print());
    // Entity *ex = entity->Print();

    // Entity e;
    // e.Print();

    // Entity *ptr = &e;

    // (*ptr).Print();
    // ptr->Print();

    
    std::cin.get();
}