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

### Arithmetic
* **Negation:** $-x = \{ -R_x \mid -L_x \}$
* **Addition:** $x + y = \{ L_x + y \cup x + L_y \mid R_x + y \cup x + R_y \}$
* **Multiplication:** $x \cdot y = \{ X_{LL} \cup X_{RR} \mid X_{LR} \cup X_{RL} \}$
  * where $X_{LL} = \{ l_x y + x l_y - l_x l_y \}$ and $X_{RR} = \{ r_x y + x r_y - r_x r_y \}$
  * where $X_{LR} = \{ l_x y + x r_y - l_x r_y \}$ and $X_{RL} = \{ r_x y + x l_y - r_x l_y \}$

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

    // Arithmetic
    Surreal sum = pos_half + pos_half;   // 1/2 + 1/2 = 1
    Surreal prod = pos_half * pos_one;   // 1/2 * 1 = 1/2

    std::cout << "sum == 1: " << (sum == pos_one ? "true" : "false") << std::endl;
    std::cout << "1/2 string form: " << pos_half.to_string() << std::endl;

    return 0;
}
```

##  Building & Running Tests

Requires a C++20 compatible compiler (e.g., `g++` or `clang++`).

```bash
# Compile
g++ -std=c++20 -Wall -Wextra main.cpp surreal.cpp -o surreal.o

# Run tests
./surreal.o
```
