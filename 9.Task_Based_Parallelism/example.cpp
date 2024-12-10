#include <iostream>
#include <numeric>
#include <future>
#include <vector>

int sumRange(const std::vector<int>& data, size_t start, size_t end){
    return std::accumulate(data.begin() + start, data.begin() + end, 0);
}


int main() 
{
    std::vector<int> input (10000000,1);
    auto mid = input.size() / 2;
    auto result1 = std::async(sumRange,input, 0, mid);
    auto result2 = std::async(sumRange,input, mid, input.size());
    
    std::cout << "result: " << result1.get() + result2.get() << std::endl;
    return 0;
}