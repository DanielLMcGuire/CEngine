# CalcEngine

Extracted from [microsoft/calculator](https://github.com/microsoft/calculator) (MIT License).  
Arbitrary-precision rational arithmetic with no external dependencies.

## Building

Requires C++17 and CMake 3.14+.

```bash
cmake -S . -B build
cmake --build build
cd build
```

To compile the example binary:

```bash
cmake -S . -B build -DCALC_ENGINE_BUILD_EXAMPLE=ON
```

To integrate into your own CMake project:

```cmake
add_subdirectory(CEngine)
target_link_libraries(your_target PRIVATE CalcEngine)
```

## Initialization

Call this **once** at startup before doing any math:

```cpp
#include "Ratpack/ratpak.h"

ChangeConstants(10, 32);
```

| Parameter   | Meaning                                                               |
|-------------|-----------------------------------------------------------------------|
| `radix`     | Display base. `10` = decimal, `16` = hex, `2` = binary.               |
| `precision` | Significant digits to maintain. `32` is what Windows Calculator uses. |

This pre-computes all internal constants (π, e, ln 2, ln 10, angle conversion
factors, integer boundary values) at the requested precision. It is cheap to
call again if you need to switch radix (e.g. a programmer mode).

## Usage

```cpp
#include "Header Files/Rational.h"
#include "Header Files/RationalMath.h"
#include "Ratpack/ratpak.h"

using namespace CalcEngine;
```

### Constructing a Rational

```cpp
// From an integer
Rational a{ 42 };

// From a p/q fraction, the correct way to represent decimals
Rational tenth{
    Number(1, 0, {1}),   // numerator:   1
    Number(1, 0, {10})   // denominator: 10
};  // exact representation of 0.1

// From another Rational
Rational b = a;
```

### Arithmetic operators

All standard operators are supported and work exactly:

```cpp
Rational x = frac(1, 10) + frac(2, 10);  // 0.3, exactly
Rational y = frac(1, 3)  * frac(3, 1);   // 1, exactly

bool ok = (x == frac(3, 10));  // true
```

### Math functions (RationalMath)

```cpp
RationalMath::Pow(base, exp)
RationalMath::Root(base, n)       // nth root
RationalMath::Exp(x)              // e^x
RationalMath::Log(x)              // natural log
RationalMath::Log10(x)
RationalMath::Abs(x)
RationalMath::Fact(x)             // factorial
RationalMath::Integer(x)          // floor toward zero
RationalMath::Frac(x)             // fractional part

// Trig - AngleType::Radians / Degrees / Gradians
RationalMath::Sin(x, AngleType::Radians)
RationalMath::Cos(x, AngleType::Radians)
RationalMath::Tan(x, AngleType::Radians)
RationalMath::ASin(x, AngleType::Radians)
RationalMath::ACos(x, AngleType::Radians)
RationalMath::ATan(x, AngleType::Radians)

// Hyperbolic
RationalMath::Sinh(x)
RationalMath::Cosh(x)
RationalMath::Tanh(x)
RationalMath::ASinh(x)
RationalMath::ACosh(x)
RationalMath::ATanh(x)
```

### Converting to a string

```cpp
// ToString(radix, format, precision)
std::wstring s = x.ToString(10, NumberFormat::Float, 32);

// NumberFormat options:
//   NumberFormat::Float, decimal or exponential as needed
//   NumberFormat::Scientific, always exponential
//   NumberFormat::Engineering, exponent always a multiple of 3
```

### Comparison

```cpp
x == y
x != y
x <  y
x >  y
x <= y
x >= y
```

## Example

```cpp
#include <iostream>
#include "Header Files/Rational.h"
#include "Header Files/RationalMath.h"
#include "Ratpack/ratpak.h"

using namespace CalcEngine;

static Rational frac(int p, int q)
{
    return Rational{
        Number(1, 0, {(uint32_t)p}),
        Number(1, 0, {(uint32_t)q})
    };
}

int main()
{
    ChangeConstants(10, 32);

    Rational a = frac(1, 10);
    Rational b = frac(2, 10);
    Rational c = frac(3, 10);

    std::wcout << (a + b == c) << L"\n";

    Rational pi_approx = frac(355, 113);
    std::wcout << pi_approx.ToString(10, NumberFormat::Float, 32) << L"\n";

    Rational e = RationalMath::Exp(Rational{1});
    std::wcout << e.ToString(10, NumberFormat::Float, 32) << L"\n";
}
```

## Licence

MIT, © Microsoft Corporation. [See license](LICENSE).
