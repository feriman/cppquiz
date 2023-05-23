/*
 * This overload is ambiguous. Why?
 *
 * There are two viable functions for the call f(-2.5). For the compiler to
 * select one, one of them needs to be better than the other, or the
 * program is ill-formed. In our case, they are equally good, making the
 * program ill-formed.
 *
 * According to [over.match.best] [1] in the standard, a viable
 * one-argument function is better than another if the conversion sequence
 * for the argument is better. So why isn't the int conversion sequence,
 * given that the double is signed?
 *
 * All conversion are given a rank, and both "double => int" and "double =>
 * unsigned int" are of type "floating-integral conversion", which has rank
 * "conversion". See Table 13 in the standard and [conv.fpint] [2]. Since
 * they have the same rank, no conversion is better than the other, and the
 * program is ill-formed.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/over.match.best
 * [2] https://timsong-cpp.github.io/cppwp/n4659/conv.fpint
 */

#include <iostream>

void f(int) { std::cout << 1; }
void f(unsigned) { std::cout << 2; }

int main() {
	f(-2.5);
}

