//
// Created by 赵桐桐 on 26-3-12.
//

#include "ThreadPool.h"
ThreadPool::ThreadPool(int Threadnum) :stop(false){
    for (int i=0;i<Threadnum;i++) {
        threads.emplace_back([this]{
            while (true) {
                std::function<void()> task;
                    {
                    std::unique_lock<std::mutex> lock(mtx);
                    cv.wait(lock, [this] { return stop || !tasks.empty(); });

                        if (stop && tasks.empty())
                            return; // 安全退出

                    task = std::move(tasks.front());
                    tasks.pop();
                    }
                task(); // 解锁后执行任务
            }
        });
    }

}
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();
    for (auto &t:threads) {
        t.join();
    }
}


