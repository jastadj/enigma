#ifndef CLASS_ENIGMA
#define CLASS_ENIGMA

#include <cstdlib>
#include <string>
#include <iostream>

#include "rotor.hpp"

class Enigma
{
private:

    // Rotors, first is static rotor (pass through), last is reflector
    // static and reflector do not rotate
    // all rotors in between are encoding rotors that turnover
    std::vector<Rotor*> m_Rotors;

public:
    Enigma();
    ~Enigma();

    char enterInput(char tc);
};
#endif // CLASS_ENIGMA
