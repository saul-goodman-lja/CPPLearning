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

    void Print() {}

};

int main()
{   
    Entity *e(new Entity());
    Entity *e1 = new Entity();



    {   
        // wear_ptr 会过期
        std::shared_ptr<Entity> e0;
        {
            // std::unique_ptr<Entity> entity1 = new Entity();
            std::unique_ptr<Entity> entity(new Entity());
            std::unique_ptr<Entity> entity2 = std::make_unique<Entity>();

            std::shared_ptr<Entity> shareEntiry = std::make_shared<Entity>();
            e0 = shareEntiry;

            entity->Print();
        }  
    }
    
    std::cin.get();
}