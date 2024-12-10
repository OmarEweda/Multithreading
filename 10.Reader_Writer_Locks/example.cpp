#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>
#include <vector>

std::shared_mutex mtx;
std::mutex cout_mtx;
std::vector<int> data {1,2,3,4,5,6,7};

void writeData(int id){
    {
        std::unique_lock<std::shared_mutex> lock(mtx); //exclusive lock for writing
        data.push_back(id);
    }
    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << "writer id " << std::this_thread::get_id() << " added value " << id << std::endl;
    }
}

void readData(int id){
    std::shared_lock<std::shared_mutex> lock(mtx); //shared lock for reading
    {
        std::lock_guard<std::mutex> lock(cout_mtx);
        std::cout << "Reader " << id << " reading: ";
        for (int val : data) {
            std::cout << val << " ";
        }    
        std::cout << std::endl;
    }
}


int main() 
{
    std::thread reader1(readData, 1);
    std::thread writer1(writeData, 10);
    std::thread reader2(readData, 2);
    std::thread reader3(readData, 3);
    std::thread writer2(writeData, 20);

    reader1.join();    
    writer1.join();
    reader2.join();
    reader3.join();
    writer2.join();
    
    return 0;
}