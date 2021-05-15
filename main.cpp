#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<chrono>
#include<fstream>
using namespace std;

int* createArray(int n) {
	int* arr = new int[n * n];

	for (int i = 0; i < (n * n); i++) {
		arr[i] = rand() % 10;

	}
	return arr;
}


int* calcArrayNaiive(int* A, int* B, int size) {
	int* result = createArray(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int counter = 0;
			for (int z = 0; z < size; z++) {
				counter += A[i * size + z] * B[z * size + j];
			}
			result[i * size + j] = counter;
		}
	}
	return result;
}

int* calcArrayThread(int* A, int* B, int size) {
	int* result = createArray(size);
	#pragma omp parallel for
	for (int i = 0; i < size; i++) {
		
		for (int j = 0; j < size; j++) {
			int counter = 0;
			for (int z = 0; z < size; z++) {
				counter += A[i * size + z] * B[z * size + j];
			}
			result[i * size + j] = counter;
		}
	}
	return result;
}

int* calcArrayThreadNested(int* A, int* B, int size) {
	int* result = createArray(size);
#pragma omp parallel for collapse(2)
	for (int i = 0; i < size; i++) {

		for (int j = 0; j < size; j++) {
			int counter = 0;
			for (int z = 0; z < size; z++) {
				counter += A[i * size + z] * B[z * size + j];
			}
			result[i * size + j] = counter;
		}
	}
	return result;
}

void printArr(int* A, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << A[i * size + j] << " | ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

	void time(int size) {
	int* A = createArray(size);

	int* B = createArray(size);
	auto timestart = std::chrono::high_resolution_clock::now();
	int* result = calcArrayNaiive(A, B, size);
	auto timeend = std::chrono::high_resolution_clock::now();


	int* resultThread = calcArrayThread(A, B, size);
	auto timeendThread = std::chrono::high_resolution_clock::now();

	int* resultThreadNested = calcArrayThreadNested(A, B, size);
	auto timeendNested = std::chrono::high_resolution_clock::now();

	auto durationNaiive = std::chrono::duration_cast<std::chrono::nanoseconds>(timeend - timestart);
	auto durationThread = std::chrono::duration_cast<std::chrono::nanoseconds>(timeendThread - timeend);
	auto durationThreadNested = std::chrono::duration_cast<std::chrono::nanoseconds>(timeendNested - timeendThread);

	std::cout << durationNaiive.count() << "," << durationThread.count() <<"," << durationThreadNested.count()<< ","<< size << std::endl;
	
	


	delete[] A;
	delete[] B;
	delete[] result;
	delete[] resultThread;
	delete[] resultThreadNested;
	
}

void main() {
	int A[] = { 10, 67, 125, 183, 241, 299, 356, 414, 472, 530, 588, 646, 703, 761, 819, 877, 935, 993, 1050, 1108, 1166, 1224, 1282, 1340, 1397, 1455, 1513, 1571, 1629, 1686, 1744, 1802, 1860, 1918, 1976, 2033, 2091, 2149, 2207, 2265, 2323, 2380, 2438, 2496, 2554, 2612, 2670, 2727, 2785, 2843, 2901, 2959, 3016, 3074, 3132, 3190, 3248, 3306, 3363, 3421, 3479, 3537, 3595, 3653, 3710, 3768, 3826, 3884, 3942, 4000 };
	int size = sizeof(A)/4;
	for (int j = 0; j < size; j++) {
		time(A[j]);
	}	
}

