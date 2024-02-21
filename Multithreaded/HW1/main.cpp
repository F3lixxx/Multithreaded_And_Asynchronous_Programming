#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

using namespace std::chrono_literals;
std::once_flag flag;
std::once_flag flag2;


void queue_func(int &clients) {
    for (int i = 0; i <= clients; ++i) {
        std::this_thread::sleep_for(1000ms);
        std::call_once(flag, []() {
            std::cout << "Clients ";
            });
        std::cout << i << '\t';
    }
    std::cout << std::endl;
}
void teller_func(int &clients) {

    for (int i = clients; i >= 0; --i) {
        std::this_thread::sleep_for(2000ms);
        std::call_once(flag2, []() {
            std::cout << "Tellers ";
            });
        std::cout << i << '\t';
    }
}

int main() {
    int k = 10;
    std::cout << "Your proccessor have " << std::thread::hardware_concurrency() << " cores" << std::endl;

    for (int i = 0; i < 1; ++i) {
        std::thread queue(queue_func, std::ref(k));
        queue.join();

    }
    for (int i = 0; i < 1; ++i) {
        std::thread teller(teller_func, std::ref(k));
        teller.join();
    }

    return 0;
}