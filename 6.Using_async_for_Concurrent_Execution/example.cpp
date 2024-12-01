#include <chrono>
#include <iostream>
#include <thread>
#include <future>

int sumRange(int start, int end){
    int sum = 0;
    for (int i = start; i < end; ++i) {
        sum+=i;
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return sum;
}


int main() 
{
    std::future<int> result = std::async(sumRange, 5, 500);

    std::cout << "calculating in the background" << std::endl;
    
    std::cout << "result: " << result.get() << std::endl;
    return 0;
}