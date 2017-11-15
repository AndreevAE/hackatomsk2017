#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <ctime>
#include <future>
#include <vector>

int calc(int x) {
	srand(x * time(0));
	int msec = rand() % 1001;
	usleep(msec * 1000);
	return x * 2;
}

int main(int argc, char *argv[]) {
	
	std::vector<std::future<int>> futures;
	for (int i = 0; i < 10; i++) {
		std::future<int> fut = std::async(std::launch::async, calc, i);
		futures.push_back(std::move(fut));
	}

	for (auto &fut : futures) {
		auto result = fut.get();
		std::cout << result << std::endl;
	}

	return 0;
}
