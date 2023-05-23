/*
 * Though this piece of code might look strange at first sight, it is still
 * valid C++ code and is known as Duff's device [1].
 *
 * According to the standard [stmt.select]#1 [2], a switch statement can be
 * followed (likewise, e.g., an if statement) by any valid statement
 * including a compound (block) statement. The only difference from a
 * general compound statement is that case and default labels can appear
 * inside it. Jumping into the nested do-while block is legal ([stmt.dcl]#3
 * [3]), and its execution is not altered by the case labels
 * ([stmt.switch]#6 [4]).
 *
 * [1] https://en.wikipedia.org/wiki/Duff%27s_device
 * [2] https://timsong-cpp.github.io/cppwp/n4659/stmt.select#1
 * [3] https://timsong-cpp.github.io/cppwp/n4659/stmt.dcl#3
 * [4] https://timsong-cpp.github.io/cppwp/n4659/stmt.switch#6
 */

#include <iostream>

int main() {
	int n = 3;
	int i = 0;

	switch (n % 2) {
	case 0:
		do {
			++i;
			case 1: ++i;
		} while (--n > 0);
	}

	std::cout << i;
}

