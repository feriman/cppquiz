/*
 * What does the std::variant default constructor do? Which of the types
 * does it pick, or is the variant empty? And if it picks one, how is the
 * value initialized?
 *
 * std::variant's default constructor constructs a variant holding the
 * value-initialized value of the first alternative. So it picks C as the
 * type and calls the C::C() default constructor initializing it with i==1,
 * which gets printed.
 *
 * [variant.ctor] [1]:
 *
 * In the descriptions that follow, let i be in the range
 * [0, sizeof...(Types)), and Ti be the i'th type in Types....
 *
 * constexpr variant() noexcept(see below);
 *
 * Effects: Constructs a variant holding a value-initialized value of type
 * T0.
 *
 * Now what does value-initialized mean?
 *
 * [dcl.init]#8 [2]:
 *
 * To value-initialize an object of type T means:
 * -- if T is a (possibly cv-qualified) class type (Clause 12) with either
 * no default constructor (15.1) or a default constructor that is
 * user-provided or deleted, then the object is default-initialized;
 *
 * C has a user-provided constructor, so it's default-initialized. Now what
 * does default-initialized mean?
 *
 * [dcl.init]#7 [3]:
 *
 * To default-initialize an object of type T means:
 * -- If T is a (possibly cv-qualified) class type (Clause 12),
 * constructors are considered. The applicable constructors are enumerated
 * (16.3.1.3), and the best one for the initializer () is chosen through
 * overload resolution (16.3). The constructor thus selected is called,
 * with an empty argument list, to initialize the object.
 *
 * There's only one default constructor, it gets called and initializes the
 * C object with i == 1.
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/variant.ctor
 * [2] https://timsong-cpp.github.io/cppwp/n4659/dcl.init#8
 * [3] https://timsong-cpp.github.io/cppwp/n4659/dcl.init#7
 */

#include <iostream>
#include <variant>

struct C
{
	C() : i(1) {}
	int i;
};

struct D
{
	D() : i(2) {}
	int i;
};

int main()
{
	const std::variant<C,D> v;
	std::visit([](const auto& val){ std::cout << val.i; }, v);
}

