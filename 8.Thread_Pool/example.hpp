#include <chrono>
#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

#define TH_NUM      4
#define TSK_NUM     10

class ThreadPool
{
public:
    ThreadPool() = default;
    ThreadPool(std::size_t threads);
    ~ThreadPool();
    void enqueue(std::function<void()> task);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;
    void workerThread();
};