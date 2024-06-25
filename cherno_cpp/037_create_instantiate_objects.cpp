#include <iostream>
#include <memory>
#include <ostream>
#include <string>

using String = std::string;

class Entity
{
private:
    String m_Name;
public:
    Entity() : m_Name("Unknown") {}
    Entity(const String& name) : m_Name(name) {}

    const String& GetName() const { return m_Name; }

};



int main()
{   
    //Entity entity = Entity("cherno"); 拷贝初始化，调用拷贝构造函数，不存在则直接创建
    // Entity entity("cherno"); 直接初始化

    Entity *e;
    {
        Entity *entity = new Entity("cherno");
        // std::unique_ptr<Entity> key = std::make_unique<Entity>("cherno");
        e = entity;
        std::cout << e->GetName() << std::endl;
    }

    delete e;
    std::cin.get();
}