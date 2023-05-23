/*
 * As the else part of the branch is obvious, we concentrate on the if part
 * and make the assumptions present in the condition.
 *
 * [lex.icon] [1] in the standard: "The type of an integer literal is the
 * first of the corresponding list in Table 7 in which its value can be
 * represented." [Table 7: int, unsigned int, long int, unsigned long int
 * ... for hexadecimal literals --end Table]
 *
 * Since the literal 0xffffffff needs 32 digits, it can be represented as
 * an unsigned int but not as a signed int, and is of type unsigned int.
 * But what happens with the negative of an unsigned integer?
 *
 * [expr.unary.op]#8 in the standard: "The negative of an unsigned quantity
 * is computed by subtracting its value from 2^n, where n is the number of
 * bits in the promoted operand." Here n is 32, and we get:
 *
 * 2^32 - 0xffffffff = 4294967296 - 4294967295 = 1
 *
 * So i is initialized to 1, and N[1] is the only element accessed in the
 * loop. (The second time around the loop, i is 0, which evaluates to
 * false, and the loop terminates.)
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/lex.icon
 * [2] https://timsong-cpp.github.io/cppwp/n4659/expr.unary.op#8
 */

#include <iostream>
#include <limits>

int main()
{
	int N[] = {0,0,0};

	if ( std::numeric_limits<long int>::digits==63 &&
		 std::numeric_limits<int>::digits==31 &&
		 std::numeric_limits<unsigned int>::digits==32 )
	{
		for (long int i = -0xffffffff; i ; --i)
		{
			N[i] = 1;
		}
	}
	else
	{
		N[1]=1;
	}

	std::cout << N[0] << N[1] << N[2];
}

