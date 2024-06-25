#include <iostream>
#include <memory>

class Entity
{
public:
    Entity() { std::cout << "Created Entity!" << std::endl; }

    ~Entity() { std::cout << "Destroyed Entity!" << std::endl; }

    void Print() {}
};
int main()
{

    {
        std::shared_ptr<Entity> e0;
        {
            // std::unique_ptr<Entity> entity = std::make_unique<Entity>();

            std::shared_ptr<Entity> sharedEntiry = std::make_shared<Entity>();
            e0                                   = sharedEntiry;
            std::weak_ptr<Entity> weakEntity     = sharedEntiry;
            // entity->Print();
        }
    }

    std::cin.get();
}