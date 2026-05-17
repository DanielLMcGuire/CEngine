// Example: using CalcEngine's arbitrary-precision Rational type.
//
// IMPORTANT: call ChangeConstants(radix, precision) once before any math.
//   radix     — display base (10 for decimal)
//   precision — number of significant digits to maintain (32 is the
//               value Windows Calculator uses internally)

#include <iostream>
#include "Header Files/Rational.h"
#include "Header Files/RationalMath.h"
#include "Ratpack/ratpak.h"

using namespace CalcEngine;

static Rational frac(int p, int q)
{
    return Rational{
        Number(1, 0, { (uint32_t)p }),
        Number(1, 0, { (uint32_t)q })
    };
}

static void print(const wchar_t* label, Rational const& r)
{
    std::wcout << label << r.ToString(10, NumberFormat::Float, 32) << L"\n";
}

int main()
{
    ChangeConstants(10, 32);

    // IEEE-754 failure case
    Rational tenth      = frac(1, 10);
    Rational two_tenths = frac(2, 10);
    Rational three_tenths = frac(3, 10);

    Rational sum = tenth + two_tenths;

    print(L"0.1        = ", tenth);
    print(L"0.2        = ", two_tenths);
    print(L"0.1 + 0.2  = ", sum);
    print(L"0.3        = ", three_tenths);
    std::wcout << L"0.1 + 0.2 == 0.3 : "
               << ((sum == three_tenths) ? L"TRUE" : L"FALSE") << L"\n\n";

    // Basic arithmetic
    Rational a{ 355 }, b{ 113 };
    print(L"355 / 113  = ", a / b);   // close approximation of pi

    // Transcendental functions via RationalMath
    Rational pi_approx = a / b;
    Rational sin_pi    = RationalMath::Sin(pi_approx, AngleType::Radians);
    print(L"sin(355/113) = ", sin_pi);  // very close to 0

    Rational e_approx = RationalMath::Exp(Rational{ 1 });
    print(L"e (exp(1))   = ", e_approx);

    return 0;
}
