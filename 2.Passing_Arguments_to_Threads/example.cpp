#include <iostream>
#include <thread>

void printNumber(int number){
    std::cout << "inside thread, passed number is "<< number << std::endl;
}


int main(int argc, const char** argv) {
    // Create a thread that runs the `printNumber` function
    // pass the argumet of the function 
    std::thread t1(printNumber,50);
    // Wait for the thread to finish
    t1.join();
    std::cout << "Thread finished execution" << std::endl;
    return 0;
}


