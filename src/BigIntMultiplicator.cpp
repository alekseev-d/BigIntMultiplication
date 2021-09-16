#include "BigIntMultiplicator.h"

namespace BigInt
{
	void BigIntMultiplicator::initial_extend()
	{
		int n = std::max(left.size(), right.size());

		if (!(n % 2 == 0))
		{
			++n;
		}

		extend(left, n);
		extend(right, n);
	}

	void BigIntMultiplicator::extend(ivector& vec, int n)
	{
		if (vec.size() == n)
		{
			return;
		}

		for (size_t i = 0; i < n - vec.size(); ++i)
		{
			vec.push_back(0);
		}
	}

	void BigIntMultiplicator::check_and_extend(ivector& first, ivector& second, int n)
	{
		if (first.size() > second.size())
		{
			extend(second, first.size() + n);
		}
		if (first.size() < second.size())
		{
			extend(first, second.size() + n);
		}
	}

	ivector BigIntMultiplicator::sum_2_vect(ivector& first, ivector& second)
	{
		check_and_extend(first, second, 2);

		int length = first.size();
		ivector result(length);

		for (int i = 0; i < length; ++i)
		{
			result[i] = first[i] + second[i];
		}

		return result;
	}

	ivector BigIntMultiplicator::reverse(ivector&& num)
	{
		ivector result(num);
		int length = num.size();

		for (int i = 0; i < length / 2; ++i)
		{
			std::swap(result[i], result[length - i - 1]);
		}

		return del_zeros(std::move(result));
	}

	int BigIntMultiplicator::count_numbers(int number)
	{
		int n = 1;

		while ((number /= 10) > 0)
		{
			n++;
		}

		return n;
	}

	ivector BigIntMultiplicator::expand(ivector&& num)
	{
		ivector result(num);

		int dec = 0, maxNumber = 9, n, length = result.size();
		for (int i = 0; i < length; ++i)
		{
			result[i] += dec;

			if (result[i] > maxNumber)
			{
				n = pow(10, count_numbers(result[i]) - 1);
				dec = (result[i] / 10) % n;
				result[i] = result[i] % 10;
			}
			else
			{
				dec = 0;
			}
		}

		if (dec > 0)
		{
			extend(result, length + 3);
			result[length] = dec % 10;
		}

		return result;
	}

	void BigIntMultiplicator::finalize(ivector& num, const ivector& P, int step)
	{
		for (int i = 0; i < P.size(); ++i)
		{
			num[i + step] += P[i];
		}
	}

	int BigIntMultiplicator::complong(const ivector& first, const ivector& second)
	{
		int f_length = first.size(), s_length = second.size();

		if (f_length < s_length)
		{
			return -1;
		}

		if (f_length > s_length)
		{
			return 1;
		}

		for (int i = f_length - 1; i >= 1; i--)
		{
			if (first[i] < second[i])
			{
				return -1;
			}

			if (first[i] > second[i])
			{
				return 1;
			}
		}

		return 0;
	}


	ivector BigIntMultiplicator::diff_2_vect(ivector& first, ivector& second)
	{
		check_and_extend(first, second, 2);

		if (complong(first, second) < 0)
		{
			std::swap(first, second);
		}

		int c = 0;
		for (int i = 0; i < std::max(first.size(), second.size()); ++i)
		{
			c = c + first[i] - second[i] + 10;
			first[i] = c % 10;

			if (c <= 9)
			{
				c = -1;
			}
			else
			{
				c = 0;
			}
		}

		return first;
	}

	ivector BigIntMultiplicator::del_zeros(ivector&& num)
	{
		ivector result(num);

		while (result[0] == 0)
		{
			result.erase(result.begin());
		}

		return result;
	}

	ivector BigIntMultiplicator::karatsuba(const ivector& p_left, const ivector& p_right)
	{
		int length = p_left.size();

		if (length < 64)
		{
			return iterative(p_left, p_right);
		}

		int k = length / 2;
		auto f_beg = p_left.begin();
		auto s_beg = p_right.begin();

		ivector result(2 * length),
			first_1 = { f_beg, f_beg + k },
			first_2 = { f_beg + k, p_left.end() },
			second_1 = { s_beg, s_beg + k },
			second_2 = { s_beg + k, p_right.end() };

		check_and_extend(first_1, first_2, 1);
		check_and_extend(second_1, second_2, 1);

		ivector P1 = karatsuba(first_1, second_1);
		ivector P2 = karatsuba(first_2, second_2);

		ivector Xlr = sum_2_vect(first_1, first_2);
		ivector Ylr = sum_2_vect(second_1, second_2);
		ivector P3 = expand(karatsuba(Xlr, Ylr));

		ivector tmp = expand(sum_2_vect(P2, P1));

		P3 = expand(diff_2_vect(P3, tmp));

		finalize(result, P1, 0);
		finalize(result, P2, 2 * k);
		finalize(result, P3, k);

		return expand(std::move(result));		
	}

	ivector BigIntMultiplicator::iterative(const ivector& p_left, const ivector& p_right)
	{
		int len = p_left.size(), tmp;
		ivector result(2 * len);

		for (int i = 0; i < len; ++i)
		{
			for (int j = 0; j < len; ++j)
			{
				tmp = p_left[i] * p_right[j] + result[i + j];
				result[i + j + 1] += tmp / 10;
				result[i + j] = tmp % 10;
			}
		}

		return result;
	}

	BigIntMultiplicator::BigIntMultiplicator(const ivector& p_left, const ivector& p_right) : left(p_left), right(p_right) 
	{
		initial_extend();
	}

	BigIntMultiplicator::BigIntMultiplicator(const std::string& p_left, const std::string& p_right)
	{
		for (const auto& iter : p_left)
		{
			left.insert(left.begin(), iter - '0');
		}

		for (const auto& iter : p_right)
		{
			right.insert(right.begin(), iter - '0');
		}

		initial_extend();
	}

	BigIntMultiplicator::~BigIntMultiplicator() {}

	ivector BigIntMultiplicator::iterative_mult()
	{
		return reverse(std::move(iterative(left, right)));
	}

	ivector BigIntMultiplicator::karatsuba_mult()
	{
		return reverse(std::move(karatsuba(left, right)));
	}

}