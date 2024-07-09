#include "TaskQueue.hh"
#include "ThreadPool.hh"
#include <stdlib.h>
#include "time.h"
#include <memory>
using std::cin, std::cout, std::endl;

class MyTask{
public:
    void process(){
        ::srand(::clock());
        int number = ::rand() % 100;
        cout << "number = " << number << endl;
    }
};

void test(){
    auto task = std::make_unique<MyTask>();
    ThreadPool pool(4, 10);
    pool.start();
    int cnt = 20;
    while(cnt--){
        pool.addTask(std::bind(&MyTask::process, task.get()));
        cout << "---cnt = " << cnt << endl;
    }
    pool.stop();
}

int main(){
    test();
    return 0;
}