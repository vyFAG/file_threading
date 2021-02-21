#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
using namespace std;

vector<int> primes;
int primes_index = 0;
bool overed = 0;

mutex mtx;

int is_prost(int num) {
	for (int i = 2; i < num / 2 + 1; i++) {
		if (num % i == 0) {
			return 0;
		}
	}

	return 1;
}

void FileWriting() {
	ofstream file;
	file.open("primes.txt", ios::out);

	while (1) {
		if (primes_index == primes.size() - 1) {
			if (overed != 1) {
				continue;
			}

			else {
				break;
			}
		}

		file << primes[primes_index] << endl;
		cout << primes[primes_index] << endl;
		primes_index++;
	}
}

void PrimeCycle(int threads, int pos) {
	for (int i = 3 + pos; i < 100000; i += threads) {
		if (is_prost(i) == 1) {
			mtx.lock();
			primes.push_back(i);
			mtx.unlock();
		}
	}

	overed = 1;
}

int main() {
	int threads_count = 12;
	thread* prime_nums = new thread[threads_count];

	for (int i = 0; i < threads_count; i++) {
		prime_nums[i] = thread(PrimeCycle, threads_count, i);
	}

	thread file_write(FileWriting);

	for (int i = 0; i < threads_count; i++) {
		prime_nums[i].join();
	}
	
	file_write.join();
}