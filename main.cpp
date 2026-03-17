#include <thread>
#include <iostream>
#include <condition_variable>
#include "ThreadPool.h"

int main() {
    ThreadPool pool(4);
    for (int i = 0; i < 100000; i++) {
        pool.enqueue([i] {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            static std::mutex print_mtx;
            std::lock_guard<std::mutex> lock(print_mtx);
            std::cout << "Task " << i << " completed." << std::endl;
        });
    }
    return 0;
}
