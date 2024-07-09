#include "Consumer.hh"
#include "Producer.hh"
#include "TaskQueue.hh"
#include <iostream>
#include <thread>

using std::cin, std::cout, std::endl;

void test0(){
    TaskQueue que(10);
    Consumer consumer1;
    Consumer consumer2;
    Consumer consumer3;
    Producter producer1;
    Producter producer2;
    std::thread c1(&Consumer::consume, &consumer1, std::ref(que));
    std::thread c2(&Consumer::consume, &consumer2, std::ref(que));
    std::thread c3(&Consumer::consume, &consumer3, std::ref(que));
    std::thread p1(&Producter::produce, &producer1, std::ref(que));
    std::thread p2(&Producter::produce, &producer2, std::ref(que));

    c1.join();
    c2.join();
    c3.join();
    p1.join();
    p2.join();

}

int main(void){

    test0();

    return 0;
}