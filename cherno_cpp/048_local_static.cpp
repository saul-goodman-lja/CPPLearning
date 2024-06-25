#include <iostream>

// 单例模式
class Singleton
{
private:
    static Singleton* s_Instance;
public:
    static Singleton& Get() { return *s_Instance;}
    // static Singleton& Get()
    // {
    //     static Singleton instance;
    //     return instance;
    // }

    void Hello() {}
};

Singleton *Singleton::s_Instance = nullptr;

class Singleton1
{
public:
    static Singleton1& Get()
    {
        static Singleton1 instance;
        return instance;
    }
    void Hello() {}
};

int main()
{
    Singleton::Get().Hello();
    Singleton1::Get().Hello();
}