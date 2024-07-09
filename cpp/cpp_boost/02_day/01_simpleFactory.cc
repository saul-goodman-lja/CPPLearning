#include <iostream>
#include <memory>

using std::cin, std::cout, std::endl;
using std::unique_ptr, std::make_unique;

enum ProductType{
    A,
    B,
    C
};

class Product{
public:
    virtual void show() = 0;
    virtual ~Product() = default;
};
class ProductA : public Product{
public:
    void show() override {
        cout << "ProductA" << endl;
    }
};
class ProductB : public Product{
public:
    void show() override {
        cout << "ProductB" << endl;
    }
};
class ProductC : public Product{
public:
    void show() override {
        cout << "ProductC" << endl;
    }
};
class ProductFactory{
public:
    static unique_ptr<Product> createProduct(ProductType type){
        switch(type){
            case A:
                return make_unique<ProductA>();
            case B:
                return make_unique<ProductB>();
            case C:
                return make_unique<ProductC>();
            default:
                return nullptr;
        }
    }
};
void test0(){
    auto pa = ProductFactory::createProduct(A);
    pa->show();
    auto pb = ProductFactory::createProduct(B);
    pb->show();
    auto pc = ProductFactory::createProduct(C);
    pc->show();
}

int main(void){

    test0();

    return 0;
}