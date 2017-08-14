#ifndef CLASS_ENIGMA
#define CLASS_ENIGMA

#include <cstdlib>
#include <string>
#include <iostream>

#include "rotor.hpp"
#include "plugboard.hpp"

#define DEBUG 0

class Enigma
{
private:

    // string of valid characters
    const std::string m_Chars;

    // Rotors, first is static rotor (pass through), last is reflector
    // static and reflector do not rotate
    // all rotors in between are encoding rotors that turnover
    std::vector<Rotor*> m_Rotors;

    // plugboard
    PlugBoard *m_PlugBoard;

    // steps rotors when key is pressed
    void stepRotors(int rnum = 1);

    // checks that rotor setup is valid
    bool isValid();


public:
    Enigma();
    ~Enigma();

    std::string getValidChars() { return m_Chars;}
    bool isCharValid(char tc);

    std::vector<int> getRotorPositions();

    bool configurePlugBoard(std::string pb);

    char enterInput(char tc);
    std::string enterString(std::string ts);

    void clear();
    void reset();

    void show();

};
#endif // CLASS_ENIGMA
