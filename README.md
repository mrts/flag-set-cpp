# flag-set-cpp

`flag_set` is a type-safe class for using enums as flags in C++14 with an underlying `std::bitset`.

The original idea is by [Arnaud Kapp (Xaqq)](https://codereview.stackexchange.com/questions/96146/c-flagset-typesafe-usage-of-enumeration-as-bitset-bitmask)
with additions from 
[Barry Revzin](https://codereview.stackexchange.com/users/31292/barry).

## Usage

`flag_set` is a header-only library, simply copy `include/flag_set.hpp` to your
project to use it.

The `enum` type of the `flag_set` **must have** a last value sentinel Unicode
symbol `‿` (undertie, U+203F), as `flag_set` needs to know the `enum` size.
I chose `‿` as sentinel as it stands out clearly and is unlikely to collide with
an enum value. However, although this works well with Clang, it does currently
[not work with GCC](https://gcc.gnu.org/wiki/FAQ#utf8_identifiers). Please open
an issue if this is a problem for you (and feel free to propose a solution).

Usage example:

```c++
#include "flag_set.hpp"

enum class Options : uint8_t {
    FULLSCREEN,
    INVERT_MOUSE,
    FLASH,
    RED_BACKGROUND,
    RED_FOREGROUND,
    ‿
};

int main()
{
    flag_set<Options> red(Options::RED_FOREGROUND | Options::RED_BACKGROUND);

    if (red[Options::RED_BACKGROUND]) // or red & Options::RED_BACKGROUND
        cout << "Red background activated";
}
```

See more examples in [tests](tests/src/flag-set-tests.cpp).
