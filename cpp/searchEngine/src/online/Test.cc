#include "../../include/online/SearchEngineServer.hh"
#include "../../include/online/Configuration.hh"
#include "../../include/online/TimerManager.hh"
#include "../../include/online/CacheUpdateTask.hh"
#include <iostream>
#include <thread>

auto main(void) -> int{
    TimerManager timerManager;
    CacheUpdateTask cacheUpdateTask;
    SearchEngineServer server(
        std::stoi(Configuration::getInstance().getparameter("threadNum")), // 线程池的线程数量
        std::stoi(Configuration::getInstance().getparameter("queSize")), // 任务队列的数量
        Configuration::getInstance().getparameter("ip"), 
        std::stoi(Configuration::getInstance().getparameter("port")));
    timerManager.attach(&cacheUpdateTask);
    std::thread timerManagerThread(&TimerManager::start, &timerManager);
    server.start();
    timerManager.stop();
    timerManagerThread.join();
    return 0;
}