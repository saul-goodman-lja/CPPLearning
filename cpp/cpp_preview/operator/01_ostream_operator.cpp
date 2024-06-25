#include <iostream>

using std::cout;

class Entity{

public:
    Entity(int x = 0, int y = 0) : a(x), b(y) {}

    void print() const{
        cout << a << " " << b << std::endl;
    }

    friend std::ostream & operator<<(std::ostream &os, const Entity & rhs);

private:
    int a;
    int b;
};

class Data{
public:
    Data(Entity *entity) : e(entity) {
        cout << "constructor" << std::endl;
    }
    ~Data() { 
        if(e){
            delete e;
            e = nullptr;
        }
    }

    Data & operator=(const Data &rhs){
        cout << "operator" << std::endl;
        this->e = rhs.e;
        return *this;
    }

    const Entity *operator->() const{
        return e;
    }

    const Entity & operator*() const{
        return *e;
    }
 
private:
    Entity *e;
};
std::ostream & operator<<(std::ostream &os, const Entity & rhs){
        os << rhs.a << " " << rhs.b << std::endl;
        return os;
}

class ThirdLayer{
public:
    ThirdLayer(Data *p) : data(p) {}
    ~ThirdLayer(){
        if(data){
            delete data;
            data = nullptr;
        }
    }

    const Data &operator->() const{
        return *data;
    }    
    
    const Entity &operator*() const{
        return *(*data);
    }



private:
    Data *data;
};

int main(){

    Data data = new Entity();
    data->print();
    (*data).print();
    (data.operator->())->print();

    ThirdLayer t = new Data(new Entity);
    t->print();
    (*t).print();
}