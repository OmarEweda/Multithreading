#include <iostream>
#include <sys/types.h>
#include <thread>
#include <mutex>
#include <vector>

std::mutex mtx;

void printNumber(int id){
    std::lock_guard<std::mutex> lock(mtx);
    for(int x = 0; x < 5; ++x){
        std::cout<<"In thread: " << id <<" printing: "<< x << std::endl;
    }
}


int main() 
{
    std::vector<std::thread> threads;
    
    for (int x = 0; x < 10; ++x) {
        threads.emplace_back(printNumber, x);    
    }

    for (auto &a : threads) {
        a.join();
    }

    return 0;
}