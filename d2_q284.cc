/*
 * Perhaps surprisingly, this program has no undefined behaviour.
 * std::string's operator[](size_type pos) must return a reference to the
 * null character when pos equals the length of the string:
 *
 * [string.access]#1 [1]
 *
 * operator[](size_type pos)
 * Returns: *(begin() + pos) if pos < size(). Otherwise, returns a
 * reference to an object of type charT with value charT(), where modifying
 * the object to any value other than charT() leads to undefined behaviour.
 *
 * charT() is char() in this case. The char() expression value-initializes
 * a char, which initializes it to 0.
 *
 * So out[out.size()] == '\0' compares 0 to \0. Are they the same? Yes:
 *
 * [lex.charset]#3 [2]
 *
 * The basec execution character set and the basec execution wide-character
 * set shall each contain all the members of the basic source character
 * set, plus control characters representing alert, backspace, and carriage
 * return, plus a null character (respectively, null wide character), whose
 * value is 0.
 *
 * So the value of \0 is indeed 0. The comparison is true, and 1 is
 * printed.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/lex.string#6
 * [2] https://timsong-cpp.github.io/cppwp/n4659/lex.charset#3
 */

#include <string>
#include <iostream>

auto main() -> int {
	std::string out{"Hello world"};
	std::cout << (out[out.size()] == '\0');
}

