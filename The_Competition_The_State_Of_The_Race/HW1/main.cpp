#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <mutex>

using namespace std::chrono_literals;


static std::atomic<int> v2{ 1 };

void add(int& clients) {
        for (int i = 0; i < v2; i++)
        {
            std::this_thread::sleep_for(1000ms);
            v2.fetch_add(1, std::memory_order_relaxed);
            v2 = clients;
          
            std::cout << " Clients " << i << ' ' << std::endl;
        }
}

void sub(int& clients) {

       while (clients != 0) {
        // std::lock_guard lk(r);
         std::this_thread::sleep_for(2000ms);
         v2.fetch_sub(1, std::memory_order_relaxed);
         clients = v2;
         std::cout << " Tellers " << clients << ' ' << std::endl;
        }
}
   


int main() {
    int k = 7;
    std::cout << "Your proccessor have " << std::thread::hardware_concurrency() << " cores" << std::endl;

    std::thread queue(add, std::ref(k));
    std::thread teller(sub, std::ref(k)); 

    queue.join();
    teller.join();
    return 0;
}