#include <iostream>
#include <thread>

void printMessage(){
    std::cout << "inside thread" << std::endl;
}


int main(int argc, const char** argv) {
    // Create a thread that runs the `printMessage` function
    std::thread t1(printMessage);
    // Wait for the thread to finish
    t1.join();
    std::cout << "Thread finished execution" << std::endl;

    return 0;
}


