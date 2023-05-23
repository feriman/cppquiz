/*
 * The program is undefined.
 * Modifying string literals is undefined behavior. In practice, the
 * implementation can for instance store the string literal in read-only
 * memory, such as the code segment. Two string literals might even be
 * stored in overlapping memory. So allowing them to be modified is clearly
 * not a good idea.
 *
 * Let's look at [lex.literal] [1] in the C++ standard:
 *
 * According to [lex.string]#1 [2] "Hello" is a string literal:
 *
 * "A string literal is a sequence of characters (as defined in #5.13.3)
 * surrounded by double quotes, optionally prefixed by R, u8, u8R, u, uR,
 * U, UR, L, or LR, as in "...", R"(...)", u8"...", u8R"(...)", u"...",
 * uR"~(...)~", U"...", UR"zzz(...)zzz", L"...", or LR"(...)",
 * respectively."
 *
 * The particularity of storing of string literals is unspecified. Thus the
 * result of modification of a string literal is indefined [3]:
 *
 * [lex.string]#16 [4]:
 *
 * "Whether all string literals are distinct (that is, are stored in
 * nonoverlapping objects) and (...) is unspecified. [Note: The effect of
 * attempting to modify a string literal is undefined. - end note]"
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/lex.literal
 * [2] https://timsong-cpp.github.io/cppwp/n4659/lex.string#1
 * [3] Also consider that the type of the string literal is array of const
 * char, and thus not modifiable.
 * [4] https://timsong-cpp.github.io/cppwp/n4659/lex.string#16
 */

#include <iostream>

int main()
{
	char *a = const_cast<char*>("Hello");
	a[4] = ' ';
	std::cout << a;
}

