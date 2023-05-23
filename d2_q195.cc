/*
 * nullptr is a prvalue of type std::nullptr_t, which is not actually a
 * pointer type. Instead, nullptr is a "null pointer constant" which can be
 * converted to a pointer.
 *
 * [lex.nullptr]#1 [1] in the C++ standard:
 *
 * The pointer literal is the keyword nullptr. It is a prvalue of type
 * std::nullptr_t. [Note: std::nullptr_t is a distinct type that is neither
 * a pointer type nor a pointer to member type; rather, a prvalue of this
 * type is a null pointer constant and can be converted to a null pointer
 * value or null member pointer value. See [conv.ptr] [2] and [conv.mem]
 * [3]. -- end note]
 *
 * [1] https://timsong-cpp.github.io/cppwp/n4659/lex.nullptr#1
 * [2] https://timsong-cpp.github.io/cppwp/n4659/conv.ptr
 * [3] https://timsong-cpp.github.io/cppwp/n4659/conv.mem
 */

#include <iostream>
#include <cstddef>
#include <type_traits>

int main() {
	std::cout << std::is_pointer_v<decltype(nullptr)>;
}

