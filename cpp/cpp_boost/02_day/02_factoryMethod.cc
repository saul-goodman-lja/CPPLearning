#include <iostream>
#include <memory>

using std::cin, std::cout, std::endl;
using std::unique_ptr, std::make_unique;

class Product{
public:
    virtual void show() = 0;
    virtual ~Product() = default;
};
class ProductA : public Product{
public:
    void show() override{
        cout << "Product A" << endl;
    }
};

class ProductB : public Product{
public:
    void show() override{
        cout << "Product B" << endl;
    }
};

class Factory{
public:
    virtual Product *createProduct() = 0;
    virtual ~Factory() = default;
};

class FactoryA : public Factory{
public:
    Product *createProduct() override{
        return new ProductA;
    }
};

class FactoryB : public Factory{
public:
    Product *createProduct() override{
        return new ProductB;
    }
};

void test0(){
    auto factoryA = make_unique<FactoryA>();
    unique_ptr<Product> productA(factoryA->createProduct());
    productA->show();

    auto factoryB = make_unique<FactoryB>();
    unique_ptr<Product> productB(factoryB->createProduct());
    productB->show(); 

}

int main(void){

    test0();

    return 0;
}