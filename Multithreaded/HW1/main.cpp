#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;
std::once_flag flag;
std::once_flag flag2;


void queue_func(int clients, int tellers){
    for(int i = 0; i < clients; ++i){
        std::this_thread::sleep_for(1000ms);
        std::call_once(flag, []() {
            std::cout << "Clients ";
            });
        std::cout << i << ' ';
    }
    std::cout << std::endl;

    for (int i = tellers; i << tellers >= 0; --i) {
        std::this_thread::sleep_for(2000ms);
        std::call_once(flag2, []() {
            std::cout << "Tellers ";
            });
        std::cout << i << ' ';
    }
}

int main(){
    std::cout << "Your proccessor have " << std::thread::hardware_concurrency() << " cores" << std::endl;

    std::vector<std::thread> ths;
    for (int i = 0; i < 1; ++i) {
        std::thread queue(queue_func, 10, 9);
        queue.join();
    }
    return 0;
}