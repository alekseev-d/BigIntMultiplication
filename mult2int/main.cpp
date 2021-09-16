#include <iostream>
#include "BigIntMultiplicator.h"
#include <fstream>
#include <chrono>

void output_to_file(const std::vector<int>& num, const std::string& path)
{
	std::ofstream out(path);
	for (const auto& iter : num)
	{
		out << iter;
	}
	out.close();
}

void output_to_console(const std::vector<int>& num)
{
	for (const auto& iter : num)
	{
		std::cout << iter;
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	std::string first, second;

	std::ifstream file("./test/test4.txt");
	if (!file.is_open())
	{
		std::cout << "Error: File wasn't opened";
		return -1;
	}

	file >> first >> second;
	file.close();

	BigInt::BigIntMultiplicator mult(first, second);

	auto start = std::chrono::high_resolution_clock::now();
	std::vector<int> karatsuba_method = mult.karatsuba_mult();
	auto stop = std::chrono::high_resolution_clock::now();

	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Karatsuba: " << duration.count() << std::endl;

	output_to_file(karatsuba_method, "./result/karatsuba.txt");
	output_to_console(karatsuba_method);

	start = std::chrono::high_resolution_clock::now();
	auto iterative_method = mult.iterative_mult();
	stop = std::chrono::high_resolution_clock::now();

	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "\nIterative: " << duration.count() << std::endl;

	output_to_file(iterative_method, "./result/iterative.txt");
	output_to_console(iterative_method);

	return 0;
}