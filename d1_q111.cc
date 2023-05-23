/*
 * [stmt.cont]#1 [1] in the standard: "The continue statement (...) causes
 * control to pass to the loop-continuation portion of the smallest
 * enclosing iteration-statement, that is, to the end of the loop." (Not to
 * the beginning.)
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/stmt.cont#1
 */

#include <iostream>

int main() {
	int i=1;
	do {
		std::cout << i;
		i++;
		if(i < 3) continue;
	} while(false);
	return 0;
}

