/*
 * The name f is overloaded by the two function templates void f(T) and
 * void f(T*). Note that overload resolution only considers the function
 * templates, not the explicit specialisation void f<>(int*)! For overload
 * resolution, rist we deduce the template arguments for each function
 * template, and get T = int* for the first one, and T = int for the
 * second.
 *
 * Both function templates are viable, but which one is best? According to
 * [over.match.best]#1 [1], a function template is a better match than
 * another function template is it's more specialised:
 *
 *		a viable function F1 is defined to be a better function then
 *		another viable function F2 if (...) the function template for F1 is
 *		more specialized than the template for F2 according to the partial
 *		ordering rules described in 17.5.6.2
 *
 * The process of partial ordering is a bit long to quote here, and not key
 * to this question. But in summary, anything accepted by f(T*) would also
 * be accepted by f(T), but not the other way around. So f(T*) is more
 * specialised.
 *
 * Now we know that the function template void f(T*) is selected by
 * overload resolution, and we can start thinking about specialisations.
 * Which of the function templates is void f<>(int*) a specialisation of?
 * [temp.expl.spec]#3 [2]:
 *
 * 		A declaration of a function template (...) being explicitly
 * 		specialized shall precede the declaration of the explicit
 * 		specialization.
 *
 * So the explicit specialisation void f<>(int*) is a specialisation of
 * void f(T), since that's the only function template declaration that
 * precdes it. Overload resolution however selected the other function
 * template, void f(T*), and we instead call an implicitly instantiated a
 * specialisation of that, printing 3.
 *
 * Note: This example is taken from Why Not Specialize Function Templates?
 * [3] by Herb Sutter.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/over.match.best#1
 * [2] https://timsong-cpp.github.io/cppwp/n4659/temp.expl.spec#3
 * [3] http://www.gotw.ca/publications/mill17.htm
 */

#include <iostream>

template <class T>
void f(T) { std::cout << 1; }

template <>
void f<>(int*) { std::cout << 2; }

template <class T>
void f(T*) { std::cout << 3; }

int main()
{
	int *p = nullptr;
	f(p);
}

