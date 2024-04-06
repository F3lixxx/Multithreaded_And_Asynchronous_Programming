#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <mutex>
#include <vector>
#include <windows.h>

using namespace std::chrono_literals;

void calculation(bool& exeption)
{
	std::this_thread::sleep_for(200ms);
	const unsigned int chance = 10;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distance(1, 100);
	exeption = (distance(gen) <= chance);
}

class calculationControl
{
public:
	calculationControl(int countthreads, int calcs)
	{
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
		_countThreads = countthreads;
		for (int  i = 0; i < _countThreads; i++)
		{
			threadsnum.push_back(std::thread(&calculationControl::calcThread, this, calcs, i));
		}
	}

	~calculationControl()
	{
		for (int i = 0; i < _countThreads; i++)
		{
			if (threadsnum[i].joinable())
			{
				threadsnum[i].join();
			}
			COORD coord = { 0, _countThreads + 1 };
			SetConsoleCursorPosition(handle, coord);
		}
	}
private:
	int _countThreads;
	std::vector<std::thread> threadsnum;
	std::mutex mt;
	std::once_flag onceFlag;
	HANDLE handle;

	void calcThread(int countCalcs, int numThread)
	{
		std::unique_lock<std::mutex> lk(mt);
		COORD coord = { 0, 0 };
		CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

		std::call_once(onceFlag, [&]()
			{
				std::cout << "#\t" << "id\t"; \
				GetConsoleScreenBufferInfo(handle, &bufferInfo);
				coord = bufferInfo.dwCursorPosition;
				int shift = 0;
				if (countCalcs > 12) 
				
					shift = countCalcs - 12;
					coord.X += shift / 2;
					SetConsoleCursorPosition(handle, coord);
					std::cout << "Progress Bar: ";
					coord.X += (13 + (shift - shift / 2));
					SetConsoleCursorPosition(handle, coord);
					std::cout << "Time";
			});
		coord.X = 0;
		coord.Y = numThread + 1;
		SetConsoleCursorPosition(handle, coord);
		std::cout << numThread << "\t" << std::this_thread::get_id() << "\t";

		GetConsoleScreenBufferInfo(handle, &bufferInfo);
		coord = bufferInfo.dwCursorPosition;
		lk.unlock();

		auto start = std::chrono::steady_clock::now();
		for (int i = 0; i < countCalcs; i++)
		{
			bool exeption;
			calculation(exeption);
			lk.lock();
			SetConsoleCursorPosition(handle, coord);
			if (!exeption)
			{
				SetConsoleTextAttribute(handle, ((15 << 4) | 15));
				std::cout << " ";
				SetConsoleTextAttribute(handle, ((0 << 4) | 15));
			}
			else
			{
				SetConsoleTextAttribute(handle, ((4 << 4) | 4));
				std::cout << " ";
				SetConsoleTextAttribute(handle, ((0 << 4) | 15));
			}
			coord.X++;
			lk.unlock();
		}
		auto end = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsedSeconds = end - start;
		lk.lock();
		coord.X++;
		if (countCalcs < 12)
			coord.X += 12 - countCalcs;
		SetConsoleCursorPosition(handle, coord);
		std::cout << elapsedSeconds.count();
	}
};

int main()
{
	const unsigned int countThreads = 8;
	const unsigned int countCalcs = 12;

	calculationControl calccontrol(countThreads, countCalcs);
	return 0;
}