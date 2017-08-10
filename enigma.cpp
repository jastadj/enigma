#include "enigma.hpp"

Enigma::Enigma()
{
    // init rotors
    //m_Rotors.push_back(new Rotor("Rotor1", "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q') );
    //m_Rotors.push_back(new Rotor("Rotor2", "AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E') );
    //m_Rotors.push_back(new Rotor("Rotor3", "BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V') );

    //m_Reflector = new Reflector("Reflector", "EJMZALYXVBWFCRQUONTSPIKHGD");
    //m_Static = new Reflector("Static");

    // init rotos
    m_Rotors.push_back( new StaticRotor("Static Rotor"));

    m_Rotors[0]->show();
}

Enigma::~Enigma()
{

}

char Enigma::enterInput(char tc)
{


}
