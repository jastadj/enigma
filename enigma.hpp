#ifndef CLASS_ENIGMA
#define CLASS_ENIGMA

#include <cstdlib>
#include <string>
#include <iostream>

#include "rotor.hpp"

#define DEBUG 0

class Enigma
{
private:

    // Rotors, first is static rotor (pass through), last is reflector
    // static and reflector do not rotate
    // all rotors in between are encoding rotors that turnover
    std::vector<Rotor*> m_Rotors;

    void stepRotors(int rnum = 1);
    bool isValid();

public:
    Enigma();
    ~Enigma();

    char enterInput(char tc);

    std::string enterString(std::string ts);
};
#endif // CLASS_ENIGMA
