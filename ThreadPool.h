//
// Created by 赵桐桐 on 26-3-12.
//
#ifndef TREADPOOL_H
#define TREADPOOL_H
#include <thread>
#include <vector>
#include <functional>
#include <queue>
#include <mutex>
#include <condition_variable>

class ThreadPool {
public:
    ThreadPool(int Threadnum);

    ~ThreadPool();
    //函数模版必须在头文件中定义
    template<class F, class... Args>
    void enqueue(F &&f, Args &&... args) {
        std::function<void()> task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        {
            std::unique_lock<std::mutex> lock(mtx);
            tasks.emplace(std::move(task));
        }
        //cv.notify_one();
    }


private:
    std::vector<std::thread> threads;       //线程池数组
    std::queue<std::function<void()>> tasks;    //任务队列
    std::mutex mtx;
    std::condition_variable cv;
    bool stop;                              //停止标志

};
#endif //TREADPOOL_H
