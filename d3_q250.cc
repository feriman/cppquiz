/*
 * The first foo (let's call it foo_1) is a template for an old-school (pre
 * variadic templates) variadic function. It takes a first argument of type
 * T, followed by a varying number of arguments.
 *
 * The second foo (let's call it foo_2) is a variadic function template
 * (notice the ellipsis in typename...). It takes a parameter pack.
 *
 * Which overload is selected for each of the calls too foo?
 *
 * When a function is overloaded, we first need to find which of the
 * functions are viable for a given function call. Then, we need to find
 * out which of those viable functions is the best one. For function
 * templates, we first perform template argument deduction to generate
 * candidate specializations.
 *
 * foo(1):
 *
 * First let's look at the call foo(1). The explanation is lengthy, but
 * rest assured we re-use most of it in the much shorter explanation of
 * foo(1, 2)!
 *
 * We start by deducing the template arguments for both overloads. For
 * foo_1, the argument 1 is used to deduce T to be int. It's signature is
 * then foo_1(int, ...). However, for overload resolution we ignore the ...
 * since it doesn't have a mathing argument:
 * [over.match.viable]#2.3 [1]:
 *
 * For the purposes of overload resolution, the parameter list is truncated
 * on the right, so that there are exactly m parameters.
 *
 * So we end up with the viable function foo_1(int).
 *
 * For foo_2, T... is a function parameter pack. The argument 1 is used to
 * deduce this as one int, and it's signature is foo_2(int).
 *
 * So, both foos are viable. Which one is best? [over.match.best]#1 [2]:
 *
 * Given these definitions, a viable function F1 is defined to be a better
 * function than another viable function F2 if for all arguments i,
 * ICSi(F1) is not a worse conversion sequence than ICSi(F2), and then
 *
 * for some argument j, ICSj(F1) is a better conversion sequence than
 * ICSj(F2)
 *
 * ICSi(F1) just means "the Implicit Conversion Sequence for argument i.
 * Our sole argument 1 is of type int, so no conversion sequence is needed
 * for neither foo_1 nor foo_2, as they both take an int as their first
 * argument. (i.e. neither is a better conversion sequence than the other.)
 *
 * [over.match.best]#1 [2] continues:
 *
 * [or, if not that] F1 and F2 are function template specializations, and
 * the function template for F1 is more specialized than the template for
 * F2 according to the partial ordering rules
 *
 * I won't go into all the details for partial ordering here, but skip to
 * the interesting parts. In short, we transform each specialization by
 * substituting each template parameter with a unique, made up type and get
 * foo_1(X, ...) and foo_2(Y). Then we do deduction from each transformed
 * function to the other, original template.
 *
 * Again, the ellipsis is ignored since it doesn't have an argument at the
 * all site:
 * [temp.deduct.partial]#3 [3]:
 *
 * The types used to determine the ordering depend on the context in which
 * the partial ordering is done:
 * In the context of a function call, the types used are those function
 * parameter types for which the function call has arguments.
 *
 * We now do deduction of foo_2(T...) from foo_1(X), which deduces T=X. We
 * then do deduction of foo_1(T) from foo_2(Y). It looks like we would get
 * T=Y, but [temp.deduct.type]#10 [4] says:
 *
 * During partial ordering, if Ai was originally a function parameter pack
 * [and] Pi is not a function parameter pack, template argument deduction
 * fails.
 *
 * Ai in this case is Y, which was originally a function parameter pack. Pi
 * is T, which is not a function parameter pack, so deduction fails.
 *
 * Since we can deduce foo_2 from foo_1, but not foo_1, from foo_2, foo_1
 * is more specialized and a better function. Overload resolution picks it
 * and prints A.
 *
 * foo(1, 2):
 *
 * Now let's look at the call foo(1, 2).
 *
 * Again we start by deducing the template arguments. For foo_1, the first
 * argument 1 is used to deduce T to be int. It's signature is then
 * foo_1(int, ...).
 *
 * For foo_2, T... is a function parameter pack. The arguments 1 and 2 are
 * used to deduce this as two ints, and it's signature is foo_2(int, int).
 *
 * Which of these is the best match? We turn again to [ver.match.best]#1
 * [2] which checks whether
 *
 * for some argument j, ICSj(F1) is a better conversion sequence than
 * ICSj(F2)
 *
 * For both templates, the first argument is an exact match. For foo_1, the
 * second argument 2 requires an ellipsis conversion sequence to match the
 * second parameter ...:
 * [over.ics.ellipsis]#1 [5]:
 *
 * An ellipses conversion sequence occurs when an argument in a function
 * call is matched with the ellipsis parameter specification of the
 * function called
 *
 * For foo_2, no conversion is required, so it's a better match. The second
 * foo is called, and B is printed.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/over.match.viable#2.3
 * [2] https://timsong-cpp.github.io/cppwp/n4659/over.match.best#1
 * [3] https://timsong-cpp.github.io/cppwp/n4659/temp.deduct.partial#3
 * [4] https://timsong-cpp.github.io/cppwp/n4659/temp.deduct.type#10
 * [5] https://timsong-cpp.github.io/cppwp/n4659/over.ics.ellipsis#1
 */

#include <iostream>

template <typename T>
void foo(T...) { std::cout << 'A'; }

template <typename... T>
void foo(T...) { std::cout << 'B'; }

int main()
{
	foo(1);
	foo(1, 2);
}

