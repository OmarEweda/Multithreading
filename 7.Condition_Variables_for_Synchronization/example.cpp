#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
std::queue<int> dataQueue;
bool finished = false;

void producer(){
    for (int i = 0; i < 10; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate work
        std::unique_lock<std::mutex> lock(mtx);
        dataQueue.push(i);
        std::cout << "Produced: " << i << std::endl;
        cv.notify_one();
    }
    std::unique_lock<std::mutex> lock(mtx);
    finished = true;
}

void consumer(){

    while (1) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock);
        while (!dataQueue.empty()) {
            int item = dataQueue.front();
            dataQueue.pop();
            std::cout << "Consumed: " << item << "\n";
        }
        if (finished && dataQueue.empty()) {
            break;
        }
    }

}

int main() 
{
    std::thread producerThread(producer);
    std::thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}