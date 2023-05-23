/*
 * According to [lex.string]#8 [1] in the standard: "A narrow string
 * literal has type "array of n const char""
 *
 * An array of n const char converts to a pointer to const char. A note in
 * [conv.qual]#4 [2] extrapolates from the preceeding normative passages
 * that "a prvalue of type "pointer to cv1 T" can be converted to a prvalue
 * of type "pointer to cv2 T" if "cv2 T" is more cv-qualified than
 * "cv1 T"." In this case however, char* is less cv-qualified than const
 * char*, and the conversion is not allowed.
 *
 * Note: While most compilers still allow char const[] to char* conversion
 * with just a warning, this is not a legal conversion since C++11.
 *
 * See also [3].
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/lex.string#8
 * [2] https://timsong-cpp.github.io/cppwp/n4659/conv.qual#4
 * [3] http://dev.krzaq.cc/stop-assigning-string-literals-to-char-star-
 * already/
 */

#include <iostream>

int main() {
	char* str = "X";
	std::cout << str;
}

