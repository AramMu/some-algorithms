#ifndef BASIC_STRUCTS
#define BASIC_STRUCTS
#include <vector>

template <class T>
using Vector = std::vector<T>;

template <class T>
using Matrix = Vector <Vector <T> >;

#endif // BASIC_STRUCTS
