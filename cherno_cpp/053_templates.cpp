#include <iostream>
#include <string>
#include <memory>

using String = std::string; // 类型
auto& cout = std::cout; // 对象
auto endl = static_cast<std::ostream&(*)(std::ostream&)>(&std::endl); // endl是函数指针
const auto& Endl = static_cast<std::ostream&(*)(std::ostream&)>(&std::endl); // endl是函数指针

using EndlType = std::ostream& (*)(std::ostream&);
EndlType myEndl = std::endl;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

// avoid code duplication
// evaluated at compile time
template <typename T>
void Print(T value)
{
    UniquePtr<int> a(new int(11115));
    cout << *a << Endl;
    cout << value << Endl;
}

template <class T>
void Print1(T value)
{
    cout << value << Endl;
}

template<typename T, int N>
class Array
{
private:
    int m_Array[N];
public:
    int GetSize() const { return N; }
};

int main()
{
    Print<String>("hello");
    Print(5.5f);
    Print(0);
    Print(88);

    Array<std::string, 50> array;
    std::cout << array.GetSize() << std::endl;
}