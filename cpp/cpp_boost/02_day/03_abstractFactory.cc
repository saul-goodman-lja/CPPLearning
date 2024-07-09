#include <iostream>
#include <memory>

using std::cin, std::cout, std::endl;
using std::unique_ptr;
using std::make_unique;

class AbstractProductA{
public:
    virtual void show() = 0;
    virtual ~AbstractProductA() = default;
};

class ProductA1 : public AbstractProductA{
public:
    void show() override{
        cout << "ProductA1" << endl;
    }
};

class ProductA2 : public AbstractProductA{
public:
    void show() override{
        cout << "ProductA2" << endl;
    }
};

class AbstractProductB{
public:
    virtual void show() = 0;
    virtual ~AbstractProductB() = default;
};

class ProductB1 : public AbstractProductB{
public:
    void show() override{
        cout << "ProductB1" << endl;
    }
};

class ProductB2 : public AbstractProductB{
public:
    void show() override{
        cout << "ProductB2" << endl;
    }
};

class AbstractFactory{
public:
    virtual AbstractProductA* createProductA() = 0;
    virtual AbstractProductB* createProductB() = 0;
    virtual ~AbstractFactory() = default;
};

class ConcreteFactory1 : public AbstractFactory{
public:
    AbstractProductA* createProductA() override{
        return new ProductA1();
    }
    AbstractProductB* createProductB() override{
        return new ProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory{
public:
    AbstractProductA* createProductA() override{
        return new ProductA2();
    }
    AbstractProductB* createProductB() override{
        return new ProductB2();
    }
};
void test0(){
    auto factory1 = make_unique<ConcreteFactory1>();
    unique_ptr<AbstractProductA> productA(factory1->createProductA());
    unique_ptr<AbstractProductB> productB(factory1->createProductB());
    productA->show();
    productB->show();
    cout << "---" << endl;
    auto factory2 = make_unique<ConcreteFactory2>();
    unique_ptr<AbstractProductA> productA2(factory2->createProductA());
    unique_ptr<AbstractProductB> productB2(factory2->createProductB());
    productA2->show();
    productB2->show();
    cout << "---" << endl;
}

int main(void){

    test0();

    return 0;
}