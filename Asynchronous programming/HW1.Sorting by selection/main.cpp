#include <iostream>
#include <vector>
#include <future>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

void selectionSort(int arr[], int arr_size, std::promise<int> &prom) {
    for (int i = 0; i < arr_size - 1; i++ ) {
        int Indexmin = i;
        for (int j = i + 1; j < arr_size; j++) {
            if (arr[j] < arr[Indexmin]) {
                Indexmin = j;
            }
        }
        std::swap(arr[Indexmin], arr[i]);
    }

    for (int i = 0; i <= arr_size - 1; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << arr[i] << ' ' << std::flush;
    }
    prom.set_value(arr_size);
}


int main() {
    int arr[] = { 10, 8, 5, 6, 9, 15, 2 };
    int arr_size = 7;
	std::promise<int> prom;
	std::future<int> futur = prom.get_future();
    auto ft = std::async(std::launch::async, selectionSort,arr, arr_size, ref(prom));
	futur.wait();
	std::cout << "\nSize of sorted array: " << futur.get() << " elements." << std::flush;
	return 0;
}