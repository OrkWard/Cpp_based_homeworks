#include "fraction.h"

Fraction::Fraction(): m_numerator(0), m_denominator(0) {}
Fraction::Fraction(int numerator, int denominator): m_numerator(numerator), m_denominator(denominator) {}
Fraction::Fraction(const Fraction& old_frac): m_numerator(old_frac.m_numerator), m_denominator(old_frac.m_denominator) {}
Fraction::Fraction(string &str) {
    stringstream ss;
    if(str.find('.') >= 0 && str.find('.') < str.length()) {
        ss << str.substr(0, str.find('.'));
        int integer = 0, decimal = 0;
        ss >> integer;
        ss << str.substr(str.find('.') + 1);
        ss >> decimal;
        int numerator = integer, denominator = 1, tmp = decimal;
        while(tmp > 0) {
            tmp /= 10;
            denominator *= 10;
            numerator *= 10;
        }
        numerator += decimal;
        int divisor = gcd(numerator, denominator);
        m_numerator = numerator / divisor;
        m_denominator = denominator / divisor;
    }
    else {
        ss << str;
        int numerator;
        ss >> numerator;
        m_numerator = numerator;
        m_denominator = 1;
    }
    
}
Fraction Fraction::operator+(const Fraction &frac) const {
    Fraction new_frac(m_numerator*frac.m_denominator + m_denominator*frac.m_numerator, 
                        m_denominator*frac.m_denominator);
    int divisor = gcd(new_frac.m_numerator, new_frac.m_denominator);
    new_frac.m_denominator /= divisor;
    new_frac.m_numerator /= divisor;
    return new_frac;
}
Fraction Fraction::operator-(const Fraction &frac) const {
    Fraction new_frac(m_numerator*frac.m_denominator - m_denominator*frac.m_numerator, 
                        m_denominator*frac.m_denominator);
    int divisor = gcd(new_frac.m_numerator, new_frac.m_denominator);
    new_frac.m_denominator /= divisor;
    new_frac.m_numerator /= divisor;
    return new_frac;
}
Fraction Fraction::operator*(const Fraction &frac) const {
    Fraction new_frac(m_numerator*frac.m_numerator, 
                        m_denominator*frac.m_denominator);
    int divisor = gcd(new_frac.m_numerator, new_frac.m_denominator);
    new_frac.m_denominator /= divisor;
    new_frac.m_numerator /= divisor;
    return new_frac;
}
Fraction Fraction::operator/(const Fraction &frac) const {
    Fraction new_frac(m_numerator*frac.m_denominator,
                        m_denominator*frac.m_numerator);
    int divisor = gcd(new_frac.m_numerator, new_frac.m_denominator);
    new_frac.m_denominator /= divisor;
    new_frac.m_numerator /= divisor;
    return new_frac;
}
bool Fraction::operator<(const Fraction &frac) const {
    Fraction differ = *this - frac;
    return differ.m_denominator*differ.m_numerator < 0;
}
bool Fraction::operator>(const Fraction &frac) const {
    Fraction differ = *this - frac;
    return differ.m_denominator*differ.m_numerator > 0;
}
bool Fraction::operator>=(const Fraction &frac) const {
    Fraction differ = *this - frac;
    return differ.m_denominator*differ.m_numerator >= 0;
}
bool Fraction::operator<=(const Fraction &frac) const {
    Fraction differ = *this - frac;
    return differ.m_denominator*differ.m_numerator <= 0;
}
bool Fraction::operator!=(const Fraction &frac) const {
    Fraction differ = *this - frac;
    return differ.m_numerator != 0;
}
bool Fraction::operator==(const Fraction &frac) const {
    Fraction differ = *this - frac;
    return differ.m_numerator == 0;
}
Fraction::operator double() const {
    return m_numerator * 1.0 / m_denominator;
}
string Fraction::frac_to_string(int presicion) const {
    stringstream ss;
    ss << setprecision(presicion) << (double)*this;
    return ss.str();
}

ostream& operator<<(ostream &out, const Fraction & frac) {
    if(frac.m_numerator == 0)
        out << 0;
    else {
        out << frac.m_numerator << '/' << frac.m_denominator;
    }
    return out;
}

istream &operator>>(istream &in, Fraction &frac) {
    in >> frac.m_numerator >> frac.m_denominator;
    return in;
}