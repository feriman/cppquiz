/*
 * You might think we access an out-of-bounds array element and the program
 * behaviour is undefined, but [basic.start.main]#2 [1] explicitly stated:
 *
 * The value of argv[argc] shall be 0
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/basic.start.main#2
 */

#include <iostream>

int main(int argc, char* argv[]) {
	std::cout << (argv[argc] == nullptr);
}

