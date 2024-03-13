#include "header.h"
#include <thread>
#include <iomanip>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <functional>

std::mutex mtx;
std::mutex mtx2;

void loading_bar() {
	system("color 0A");
	char bar = 221;
	std::cout << std::fixed << std::setprecision(7) << std::setw(5);
	std::scoped_lock name_lk(mtx, mtx2);

	for (int i = 0; i < 20; i++)
	{
		std::cout << bar;
		Sleep(10);
	}
}

void id_thread() {
	std::scoped_lock name_lk(mtx, mtx2);
	std::cout << std::setw(8) << std::this_thread::get_id();

	loading_bar();
}


void threads() {
	std::cout << "#" << std::setw(7) << "id" << std::setw(20) << "Progress Bar" << std::setw(18) << "Time" << std::endl;
	std::vector<std::thread> threads;

	for (int i = 0; i < 4; ++i)
	{
		auto start_time = std::chrono::high_resolution_clock::now();
		std::cout << i;

		std::scoped_lock name_raii(mtx, mtx2);
		
		threads.emplace_back(id_thread);

		for (auto& th : threads) {
			if (th.joinable()) {
				th.join();
			}
		}

		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
		std::cout << std::setw(11) << std::fixed << std::setprecision(3) << duration.count() / 1000 << "ms";
		std::cout << std::endl;
		
	}
	
}