#include <iostream>
#include <ostream>


class Entity
{
private:
    int *m_X, m_Y;
    mutable int var; // 即使被const 也是可以修改的
public:
    const int* const & GetX() const
    {
        return m_X;
    }

    void SetX(int x)
    {
        m_X = &x;
    }
};

void PrintEntity(const Entity& e)
{
    std::cout << e.GetX() << std::endl;
}

int main()
{

    int a = 10;
    const int *b = &a;
    *b = 10;

    int * const c = &a;
    c = nullptr;

    const int * const d = &a;
    *d = 1;
    d = nullptr;

}