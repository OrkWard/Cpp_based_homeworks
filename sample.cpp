#include "fraction.h"

int main() {
    cout << "Fraction(): " << Fraction() << endl;
    cout << "Fraction(4, 10): " << Fraction(4, 10) << endl;
    Fraction new_frac = Fraction(4, 10);
    cout << "Fraction new_frac = old_frac: " << new_frac << endl;

    cout << Fraction(3, 5) << " + " << Fraction(4, 9) << " = " << Fraction(3, 5) + Fraction(4, 9) << endl;
    cout << Fraction(3, 6) << " - " << Fraction(2, 4) << " = " << Fraction(3, 6) - Fraction(2, 4) << endl;
    cout << Fraction(3, 7) << " x " << Fraction(7, 9) << " = " << Fraction(3, 7) * Fraction(7, 9) << endl;
    cout << Fraction(9, 8) << " / " << Fraction(5, 4) << " = " << Fraction(9, 8) / Fraction(5, 4) << endl << endl;

    cout << Fraction(3, 8) << " < " << Fraction(21, 29) << " : " << (Fraction(3, 8) < Fraction(21, 29)) << endl;
    cout << Fraction(3, 8) << " > " << Fraction(21, 29) << " : " << (Fraction(3, 8) > Fraction(21, 29)) << endl;
    cout << Fraction(3, 8) << " >= " << Fraction(21, 29) << " : " << (Fraction(3, 8) >= Fraction(21, 29)) << endl;
    cout << Fraction(3, 8) << " <= " << Fraction(21, 29) << " : " << (Fraction(3, 8) <= Fraction(21, 29)) << endl;
    cout << Fraction(3, 8) << " != " << Fraction(21, 29) << " : " << (Fraction(3, 8) != Fraction(21, 29)) << endl;
    cout << Fraction(3, 8) << " == " << Fraction(21, 56) << " : " << (Fraction(3, 8) == Fraction(21, 56)) << endl << endl;

    cout << "(double)" << Fraction(61, 29) << " = " << (double)Fraction(61, 29) << endl;
    cout << "To string(default presicion): " << Fraction(61, 29).frac_to_string() << endl;
    cout << "To string(presicion = 3): " << Fraction(61, 29).frac_to_string(4) << endl;

    return 0;
}