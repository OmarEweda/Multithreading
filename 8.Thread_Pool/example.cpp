#include "example.hpp"


ThreadPool::ThreadPool(std::size_t threads){
    for (std::size_t i = 0 ; i < threads; ++i) {
        this->workers.emplace_back(&ThreadPool::workerThread, this);        
        std::cout << "Creating thread " << i << " ID " << this->workers.back().get_id() << std::endl;
    }
}

ThreadPool::~ThreadPool(){
    {
        std::unique_lock<std::mutex> lock(this->mtx);
        this->stop = true;
    }
    this->cv.notify_all();

    for (auto &worker : this->workers) {
        worker.join();
    }
}

void ThreadPool::enqueue(std::function<void()> task){
    {
        std::unique_lock<std::mutex> lock(this->mtx);
        this->tasks.emplace(std::move(task));
    }

    this->cv.notify_one();
}

void ThreadPool::workerThread()
{
    while (!stop)
    {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock (this->mtx);
            cv.wait(lock, [this]{return !this->tasks.empty() || this->stop;});

            if(this->stop && this->tasks.empty()){
                return;
            }

            task = this->tasks.front();
            this->tasks.pop();
        }
        task();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}



int main() {
    ThreadPool pool(TH_NUM);
    for (size_t i = 0; i < TSK_NUM; i++)
    {
        pool.enqueue([i]{
            std::cout << "enqueue task: "<< i << " using thread: "<< std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        });
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}
