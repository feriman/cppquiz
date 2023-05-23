/*
 * [temp.res]#9 [1] states: "When looking for the declaration of a name
 * used in a template definition, the usual lookup rules (6.4.1, 6.4.2) are
 * used for non-dependent names. The lookup of names dependent on the
 * template parameters is postponed until the actual template argument is
 * known (17.6.2)."
 *
 * The first call to adl is a non-dependent call, so it is looked up at the
 * time of definition of the function template. The resolution of the
 * second call is deferred until the template is instantiated because it
 * depends on a template parameter.
 *
 * template<typename T> void call_adl_function(T t)
 * {
 *     adl(S()); // Independent, looks up adl now.
 *     adl(t); // Dependent, looks up adl later.
 * }
 *
 * When adl is being looked up at the time of definition of the function
 * template, the only version of adl that exists is the templated adl(T).
 * Specifically, adl(S) does not exist yet, and is not a candidate.
 *
 * Note: At the time of writing, this program does not confirm to the
 * standard in some recent versions of Visual Studio's C++ compiler.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/temp.res#9
 */

#include <iostream>

using namespace std;

template<typename T>
void adl(T)
{
	cout << "T";
}

struct S
{
};

template<typename T>
void call_adl(T t)
{
	adl(S());
	adl(t);
}

void adl(S)
{
	cout << "S";
}

int main()
{
	call_adl(S());
}

