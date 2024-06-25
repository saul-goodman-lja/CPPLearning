#include <iostream>
#include <ostream>

class Entity;

void PrintEntity(const Entity& e);

class Entity
{
public:
    int x, y;

    Entity(int x, int y)
    {
        // const Entity *e = this;
        // e = nullptr;

        // this (* const )
        Entity* const & f = this;

        // this = nullptr;

        f->x = x;
        f->y = y;

        Entity &e = *this;

        PrintEntity(*this);
    }

    int GetX() const
    {   
        // this.x = 1;
        // this (const Entity* const)

        const Entity &a = *this;

        const Entity * const & e =this;
        return e->x;
    }

};

void PrintEntity(const Entity& e)
{
    // print
    std::cout << e.x << ", " << e.y << std::endl;
}


int main()
{
    std::cin.get();
}