#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <iterator>

template <typename Iterator, typename Function>
void parallel_for_each(Iterator begin, Iterator end, Function&& func) {
	const size_t num_threads = std::thread::hardware_concurrency();
	const size_t chunk_size = std::distance(begin, end) / num_threads;

	std::vector<std::thread> threads;
	threads.reserve(num_threads);

	Iterator chunk_start = begin;
	for (size_t i = 0; i < num_threads; ++i)
	{
		Iterator chunk_end = std::next(chunk_start, chunk_size);
		if (i == num_threads - 1) {
			chunk_end = end;
			threads.emplace_back([chunk_start, chunk_end, &func] {
				std::for_each(chunk_start, chunk_end, func);
				});
			chunk_start = chunk_end;
		}
		for (auto& thread : threads)
		{
			if (thread.joinable()) {
				thread.join();
			}
		}

	}
 }


int main () {
	std::vector<int> nums = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	
	parallel_for_each(nums.begin(), nums.end(), [] (int& num) {
		num *= 2;
	});

	std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;

	return 0;
}