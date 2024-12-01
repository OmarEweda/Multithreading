#include <iostream>
#include <thread>
#include <chrono>

void printDelayMessage(){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"Message from background/Detached thread"<<std::endl;
}


int main(int argc, const char** argv) {
    // Create a thread that runs the `printDelayMessage` function
    std::thread t1(printDelayMessage);
    // Detach the thread to run independently    
    t1.detach();
    std::cout << "We are in main thread" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 0;
}