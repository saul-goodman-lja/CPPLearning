#include <iostream>
#include <string>

// pure virtual
class Printable
{
public:
    virtual std::string GetClassName() = 0;
};

class Entity : public Printable
{
public:
    virtual std::string GetName() { return "Entity"; }
    std::string         GetClassName() override { return "Entity"; }
};

class Player : public Entity
{
private:
    std::string m_Name;

public:
    Player(const std::string& name)
        : m_Name(name)
    {}

    std::string GetName() override { return m_Name; }
};

class A : public Printable
{
public:
    std::string GetClassName() override { return "A"; }
};

void Print(Printable* obj)
{
    std::cout << obj->GetClassName() << std::endl;
}

int main()
{

    Print(new A());

    std::cout << "hello world!" << std::endl;
}