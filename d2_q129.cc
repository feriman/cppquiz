/*
 * This program is undefined.
 * Here we are trying to initialize a vector<char> using two string
 * literals, not two chars.
 *
 * The initializer-list constructor for template<class T> vector is defined
 * as vector(initializer_list<T>) by [vector.overview] [1] in the standard.
 * In our case, vector(initializer_list<char>).
 *
 * The type of a string literal is "array of n const char" ([lex.string]#8
 * [2]), so clearly the initializer-list constructor is not a match.
 *
 * This problem does however not result in a compiler error, since the
 * compiler is able to find another constructor that matches!
 *
 * [over.match.list]#1 [3] explains the rules very clearly:
 * "When objects of non-aggregate class type T are list-initialized (...),
 * overload resolution selects the constructor in two phases:
 * -- Initially, the candidate functions are the initializer-list
 *  constructors of the class T and the argument list consists of the
 *  initializer list as a single argument [which we have seen didn't
 *  match].
 * -- If no viable initializer-list constructor is found, overload
 *  resolution is performed again, where the candidate functions are all
 *  the constructors of the class T and the argument list consists of the
 *  elements of the initializer list [in out case, the two string literals
 *  "," and ";"]".
 *
 * Going back to [vector.overview] [1], we find this candidate:
 *
 * template<class InputIterator> vector(InputIterator first, InputIterator
 * last)
 *
 * Note that the type of InpurIterator has no link to the type of T in the
 * vector<T>. So even if we are initializing a vector<char>, the two
 * arguments can be of arbitrary type. The only requirement is that they
 * confirm to the concept of InputIterator, which const char[] happens to
 * do.
 *
 * Now the constructor believes it has been passed two iterators to the
 * same sequence, but is has actually been passed iterators to two
 * completely different sequences, "," and ";". [forward.iterators]#2 [4]
 * says: "The domain of == for forward iterators is that of iterators over
 * the same underlying sequence.". So the result of this program is
 * undefined.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/vector.overview
 * [2] https://timsong-cpp.github.io/cppwp/n4659/lex.string#8
 * [3] https://timsong-cpp.github.io/cppwp/n4659/over.match.list#1
 * [4] https://timsong-cpp.github.io/cppwp/n4659/forward.iterators#2
 */

#include <vector>
#include <iostream>

using namespace std;

int main() {
	vector<char> delimiters = { ",", ";" };
	cout << delimiters[0];
}

