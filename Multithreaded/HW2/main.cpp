#include <iostream>
#include <iomanip>
#include <vector>
#include <thread>
#include <chrono>

void calculate_sum(std::vector<int>& vec1, std::vector<int>& vec2, std::vector<int>& result, int start, int end) {
    for (int i = start; i < end; ++i) {
        result[i] = vec1[i] + vec2[i];
    }
}

int main() {
    std::cout << "Available hardware cores: " << std::thread::hardware_concurrency() << std::endl;

    std::vector<int> sizes = { 1000, 10000, 100000, 1000000 };
    std::vector<int> num_threads = {1, 2, 4, 8, 16 };
    for (auto size : sizes)
    {
        std::vector<int> vec1(size, 10000);
        std::vector<int> vec2(size, 10000);
        std::vector<int> result(size);

        std::cout << size << std::endl;

        

        for (auto threads : num_threads) {
            std::vector<std::thread> thread_pool;

            auto start_time = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < threads; ++i) {
                int start = i * (size / threads);
                int end = (i == threads - 1) ? size : (i + 1) * (size / threads);
                thread_pool.emplace_back(calculate_sum, std::ref(vec1), std::ref(vec2), std::ref(result), start, end);
            }

            for (auto& thread : thread_pool) {
                thread.join();
            }

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

            std::cout << "Threads: " << threads << ", Time: " << duration.count() / 1000.0 << " ms" << std::endl;
        }
        std::cout << std::endl;
        }
   

    return 0;
}
