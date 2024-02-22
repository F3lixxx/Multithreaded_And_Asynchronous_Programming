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
    std::cout << std::setw(20) << "1000" << std::setw(20) << "10000" << std::setw(20) << "100000" << std::setw(17) << "1000000" << std::endl;

    std::vector<int> num_threads = { 1, 2, 4, 8, 16 };

    for (auto thread : num_threads) {
        std::cout << thread << " cores ";

        std::vector<int> sizes = { 1000, 10000, 100000, 1000000 };

        for (auto size : sizes) {
            std::vector<int> vec1(size, 10000);
            std::vector<int> vec2(size, 10000);
            std::vector<int> result(size);

            std::vector<std::thread> thread_pool;

            auto start_time = std::chrono::high_resolution_clock::now();

            for (int i = 0; i < thread; ++i) {
                int start = i * (size / thread);
                int end = (i == thread - 1) ? size : (i + 1) * (size / thread);
                thread_pool.emplace_back(calculate_sum, std::ref(vec1), std::ref(vec2), std::ref(result), start, end);
            }

            for (auto& thread : thread_pool) {
                thread.join();
            }

            auto end_time = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

            std::cout << std::setw(15) << std::fixed << std::setprecision(7) << duration.count() / 1000.0 << " ms";
        }

        std::cout << std::endl;
    }

    return 0;
}
