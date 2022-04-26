#include <iostream>
#include <numeric>
#include <string>
#include <iomanip>
#include <sstream>
using namespace std;

/* This class doesn't take care for 
 * division zero error or invalid operand, 
 * it's caller's due to check the situation.
 * Just make operate wouldn't throw any
 * exception.
 */
class Fraction {
    public:
        Fraction();     // default ctor
        Fraction(int numerator, int denominator);   // ctor takes two integers as parameters
        Fraction(const Fraction& old_frac);          // copy ctor
        Fraction(string &str);                      // str to fraction
        // arithmetical operators
        Fraction operator+(const Fraction& frac) const;
        Fraction operator-(const Fraction& frac) const;
        Fraction operator*(const Fraction& frac) const;
        Fraction operator/(const Fraction& frac) const;
        // relational operators
        bool operator<(const Fraction& frac) const;
        bool operator>(const Fraction& frac) const;
        bool operator>=(const Fraction& frac) const;
        bool operator<=(const Fraction& frac) const;
        bool operator!=(const Fraction& frac) const;
        bool operator==(const Fraction& frac) const;
        // cast type to double
        operator double() const;
        // convert to string, take in one optional 
        // argument to specify presision
        string frac_to_string(int presicion = 6) const;

        int m_numerator, m_denominator;
};

// insertor and extractor
ostream& operator<<(ostream &out, const Fraction & frac);
istream& operator>>(istream &in, Fraction &frac);