/*
 * Even though these constructor invocations look strikingly similar, the
 * one that takes a C-style string and the one that takes a basic_string
 * behave differently with respect to the second argument. For the former,
 * it means "until this position", but for the latter it means "from this
 * position".
 *
 * Details:
 *
 * In the constructor taking a C-style string (the s1 case) the second
 * argument is treated as how many character to take from the start of the
 * C-style string. [string.cons]#11 [1]:
 *
 * basic_string(const charT* s, size_type n, const Allocator& a =
 * Allocator());
 *
 * Effects: Constructs an object of class basic_string and determines its
 * initial string value from the array of charT of length n whose first
 * element is designated by s
 *
 * On the other hand, in the constructor that takes basic_string (the 2s
 * case) the second argument is treated as the position to start copying
 * the string from. [string.cons]#4 [2]:
 *
 * basic_string(const basic_string& str, size_type pos, const Allocator& a
 * = Allocator());
 * 
 * Effects: Constructs an object of class basic_string and determines the
 * effective length rlen of the initial string value as str.size() - pos,
 * as indicated in Table 57.
 *
 * Table 57 then goes on to explain that the data of the string starts at
 * pos:
 *
 * [the string data] points at the first element of an allocated copy of
 * rlen consecutive elements of the string controlled by str beginning at
 * position pos
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/string.cons#11
 * [2] https://timsong-cpp.github.io/cppwp/n4659/string.cons#4
 */

#include <string>
#include <iostream>

int main() {
	using namespace std::string_literals;
	std::string s1("hello world", 5);
	std::string s2("hello world"s, 5);

	std::cout << s1 << s2;
}

