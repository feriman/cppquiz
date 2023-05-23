/*
 * std::get<T>(tuple) can only be used on a tuple which has exactly one T
 * in it.
 *
 * [tuple.elem]#5 [1]:
 *
 * template <class T, class... Types>
 * constexpr const T& get(const tuple<Types...>& t) noexcept;
 *
 * Requires: The type T occurs exactly once in Types.... Otherwise, the
 * program is ill-formed.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/tuple.elem#5
 */

#include <iostream>
#include <tuple>

int main()
{
	const auto t = std::make_tuple(42, 3.14, 1337);
	std::cout << std::get<int>(t);
}

