#include <iostream>
#include <thread>

int main(int argc, const char** argv) {
    std::thread t1([](){
        std::cout<< "inside lambda function in thread"<< std::endl; 
    });
    // Wait for the thread to finish
    t1.join();
    std::cout << "Thread finished execution" << std::endl;
    return 0;
}


