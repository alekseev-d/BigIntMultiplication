# BigIntMultiplication

# Task
Given two integers in length that exceed the limit of the standard numeric types. It is necessary to write a code to multiply these numbers.

There are 2 methods:
* 1) iterative algorithm with O(n^2),
* 2) karatsuba algorithm with O(n^log2(3)).

Karatsuba algorithm reduces the multiplication of two n-digit numbers to at most n^(log2(3)) single-digit multiplications in general. It is therefore asymptotically faster than the traditional algorithm, which requires n^2 single-digit products.
