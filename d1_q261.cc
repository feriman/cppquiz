/*
 * Summary
 *
 * stringstream is backed by a character buffer. Initializing it with a
 * string initializes the buffer with that string, in this case a. Calling
 * str() returns the contents of the buffer, and we print a.
 *
 * operator<< writes to the next position in the buffer, in this case the
 * beginning of the buffer, overwriting whatever is already there. A b is
 * written, overwriting the a which was previously in the buffer.
 *
 * Finally str() is called again, this time printing b.
 *
 * We can change this bahaviour by initializing stringstream like this:
 *
 * std::stringstream ss("a", std::ios_base::out|std::ios_base::ate);
 *
 * Then the a doesn't get overwritten, and the program instead outputs aab,
 * where a comes from the first call to str(), and ab comes from the second
 * call to str().
 *
 * Detail
 *
 * A stringstream is an alias for basic_stringstream<char>.
 * basic_stringstream<char> uses a basic_stringbuf<char> as storage for the
 * characters in the stream:
 *
 * using stringstream = basic_stringstream<char>
 *
 *  ------------------         ---------------
 * |basic_stringstream|<>-----|basic_stringbuf|
 *  ------------------         ---------------
 *
 * Let's have a look at the basic_stringstream constructor:
 * [stringstream.cons]#2 [1]:
 *
 * explicit basic_stringstream(const basic_string<charT, traits,
 * 	   Allocator>& str, ios_base::openmode which = ios_base::out |
 * 	   ios_base::in);
 *
 * Effects: Constructs an object of class basic_stringstream<charT,
 * traits>, initializing the base class with basic_iostream(&sb) and
 * initializing sb with basic_stringbuf<charT, traits, Allocator>(str,
 * which).
 *
 * sb here refers to the basic_stringbuf which backs the
 * basic_stringstream.
 * So this constructor initializes the buffer with "a", and sets its mode
 * to ios_base::out | ios_base::in.
 *
 * Then we call str() on the basic_strintstream, which again calls str() on
 * the basic_stringbuf, which according to [stringbuf.members]#1 [2]:
 *
 * Returns: A basic_string object whose is equal to the basic_stringbuf
 * underlying character sequence.
 *
 * So we get out a copy of that, and a is printed. (Note that str() does
 * not modify the buffer.)
 *
 * Then we stream "b" into the basic_stringstream. This operation is
 * defined in terms of some of the basic_stringstream base classes, so
 * here's (parts of) its inheritance diagram, for reference:
 *
 *                               ---------
 *                              |basic_ios|
 *                               ---------
 *                              /
 *                     -------------   -------------
 *                    |basic_istream| |basic_ostream|
 *                     -------------   -------------
 *                                       /
 *                             --------------
 *                            |basic_iostream|
 *                             --------------
 *                                   |
 *                            ------------------
 *                           |basic_stringstream|
 *                            ------------------
 *
 * basic_stringstream inherits operator<< from ostream, which according to
 * [ostream]#2 [3]:
 *
 * generate[s] (or insert[s]) output characters by actions equivalent to
 * calling rdbuf()->sputc(int_type).
 *
 * rdbuf() here refers to our basic_stringbuf. basic_stringbuf inherits
 * sputc from basic_stringbuf. [streambuf.pub.put]#1 [4]:
 *
 * int_type sputc(char_type c);
 * (...) stores c at the next pointer for the output sequence, increments
 * the pointer
 *
 * So when we stream into our stringstream, the characters get stored at
 * the next pointer in the buffer, and the next pointer is incremented.
 *
 * Since the basic_stringbuf was constructed with ios_base::out |
 * ios_base::in, the next pointer points to the beginning of the stream,
 * and the a already in the stream gets overwritten. If we add the flag
 * io_base::ate, we get a different result, [ios::openmode] [5]:
 *
 * ate open and seek to end immediately after opening
 *
 * This will seek to the end of the stream, i.e. after the a which is
 * already in the buffer, and the b will be appended rather than
 * overwriting the a. So if we construct the stringstream like this:
 *
 * std::stringstream ss("a", std::ios_base::out|std::ios_base::ate);
 *
 * The output changes to aab, where a comes from the first call to str(),
 * and ab comes from the second call to str().
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/stringstream.cons#2
 * [2] https://timsong-cpp.github.io/cppwp/n4659/stringbuf.members#1
 * [3] https://timsong-cpp.github.io/cppwp/n4659/ostream#2
 * [4] https://timsong-cpp.github.io/cppwp/n4659/streambuf.pub.put#1
 * [5] https://timsong-cpp.github.io/cppwp/n4659/ios::openmode
 */

#include <iostream>
#include <sstream>

int main() {
	std::stringstream ss("a");
	std::cout << ss.str();
	ss << "b";
	std::cout << ss.str();
}

