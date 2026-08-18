# Surreal Numbers in C++

An experimental C++ implementation of **Surreal Numbers**, a system introduced by John Conway containing real numbers as well as infinite and infinitesimal numbers.

In this system, a surreal number $x$ is defined recursively as an ordered pair of sets of previously constructed surreal numbers:

$$x = \{ L_x \mid R_x \}$$

where no element in $L_x$ (the Left set) is greater than or equal to any element in $R_x$ (the Right set).

---

## Mathematical Reference

### Comparisons

Comparison between two surreal numbers $x$ and $y$ is defined as:

$$x \le y \iff (\forall l \in L_x, y \not\le l) \land (\forall r \in R_y, r \not\le x)$$

Derived equality and inequality:
* $x == y \iff (x \le y) \land (y \le x)$
* $x < y \iff (x \le y) \land \neg(y \le x)$

##  Example Usage

```cpp
#include <iostream>
#include "surreal.h"

int main() {
    // Day 0
    Surreal zero{};                      // 0 = { | }

    // Day 1
    Surreal pos_one({zero}, {});         // 1 = { 0 | }
    Surreal neg_one({}, {zero});         // -1 = { | 0 }

    // Day 2
    Surreal pos_half({zero}, {pos_one}); // 1/2 = { 0 | 1 }

    if (neg_one < pos_half && pos_half < pos_one) {
        std::cout << "-1 < 1/2 < 1" << std::endl;
    }

    return 0;
}
```

##  Building & Running Tests

Requires a C++17 compatible compiler (e.g., `g++` or `clang++`).

```bash
# Compile
g++ -std=c++17 -Wall -Wextra main.cpp surreal.cpp -o surreal.o

# Run tests
./surreal.o
```
