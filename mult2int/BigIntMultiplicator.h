#pragma once
#include <string>
#include <vector>

namespace BigInt																				// namespace for operation with big integers
{
	typedef std::vector<int> ivector;															// std::vector of integers

	class BigIntMultiplicator																	// class for big integer multiplication
	{
		ivector left, right;																	// result = left * right

		void initial_extend();																	// initial extend of vectors
		void extend(ivector& vec, int n);														// extend vector method
		void check_and_extend(ivector& first, ivector& second, int n);							// comparing vector sizes and expanding them
		ivector sum_2_vect(ivector& first, ivector& second);									// sum method
		ivector reverse(ivector&& num);															// reverse vector
		int count_numbers(int number);															// count of digits in number
		ivector expand(ivector&& num);															// expanding in normal number form
		void finalize(ivector& num, const ivector& P, int step);								// forming a final number
		int complong(const ivector& first, const ivector& second);								// compare two vectors
		ivector diff_2_vect(ivector& first, ivector& second);									// difference between 2 vectors
		ivector del_zeros(ivector&& num);														// delete extra zeros

		ivector karatsuba(const ivector& p_left, const ivector& p_right);						// inner karatsuba method
		ivector iterative(const ivector& p_left, const ivector& p_right);						// inner iterative method
	public:
		BigIntMultiplicator() = delete;															// default constructor
		BigIntMultiplicator(const ivector& p_left, const ivector& p_right);						// constructor with vectors
		BigIntMultiplicator(const std::string& p_left, const std::string & p_right);			// constructor with strings

		BigIntMultiplicator(const BigIntMultiplicator& other) = delete;							// copy constructor
		BigIntMultiplicator(BigIntMultiplicator&& other) = delete;								// move constructor

		BigIntMultiplicator& operator=(const BigIntMultiplicator& other) = delete;				// copy operator
		BigIntMultiplicator& operator=(BigIntMultiplicator&& other) = delete;					// move operator

		~BigIntMultiplicator();																	// destructor

		ivector iterative_mult();																// iterative method
		ivector karatsuba_mult();																// karatsuba method
	};
}