#include <iostream>
#include <string>

using String = std::string;

class Entity
{
private:
    String m_Name;
public:
    Entity() : m_Name("unknown") {}
    Entity(const String& name) : m_Name(name) {}

    const String& GetName() const
    {
        return m_Name;
    }
};

int main()
{
    int a = 2;
    int *b = new int[50];

    Entity *e = new Entity(); // 会调用构造函数
    Entity *eb = new(b) Entity(); // 并未重新分配内存，占用b，会调用构造函数

    Entity *e1 = (Entity *)malloc(sizeof(Entity)); // 不会调用构造函数

    delete e;
    free(e1);
    delete [] b;

    std::cin.get();
}