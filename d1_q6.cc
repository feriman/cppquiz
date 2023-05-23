/*
 * Whether you post-increment or pre-increment i, its value does not change
 * until after the loop body has executed.
 */

#include <iostream>

int main() {
	for (int i = 0; i < 3; i++)
		std::cout << i;
	for (int i = 0; i < 3; ++i)
		std::cout << i;
}
