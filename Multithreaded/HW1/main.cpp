#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;
std::once_flag flag;
std::once_flag flag2;


void queue_func(int& clients) {
    for (int i = 0; i < clients; i++)
    {
        std::this_thread::sleep_for(1000ms);
        clients++;
        std::cout << " Clients " << i << ' ' << std::endl;
    }
}

void teller_func(int& clients) {
    while (clients != 0) {
        std::this_thread::sleep_for(2000ms);
        --clients;
        std::cout << " Tellers " << clients << ' ' << std::endl;
    }
}

int main() {
    int k = 10;
    std::cout << "Your proccessor have " << std::thread::hardware_concurrency() << " cores" << std::endl;

    std::thread queue(queue_func, std::ref(k));
    std::thread teller(teller_func, std::ref(k));

    queue.join();
    teller.join();

    return 0;
}