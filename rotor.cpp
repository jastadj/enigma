#include "rotor.hpp"

#include <iostream>

const std::string Rotor::m_Chars = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

Rotor::Rotor(std::string rname, std::string wiredchars, char turnoverc)
{
    m_Name = rname;
    m_WiredChars = wiredchars;
    m_TurnoverChar = turnoverc;
    m_Position = 0;

    // check if rotor is valid
    if(!isValid())
    {
        std::cout << "Rotor is not valid! (Wired chars or turnover character)\n";
        m_WiredChars = m_Chars;
    }
}

Rotor::~Rotor()
{

}

void Rotor::turn()
{
    m_Position++;

    if(m_Position >= getCharCount()) m_Position = 0;
}

bool Rotor::isValid()
{
    std::vector<bool> found;

    for(int i = 0; i < int(m_Chars.length()); i++) found.push_back(false);

    // check that wired char length is the same as expected chars length
    if( m_Chars.length() != m_WiredChars.length()) return false;

    // mark found characters
    for(int i = 0; i < int(m_WiredChars.length()); i++)
    {
        size_t fpos = 0;

        // find target character in expected char list
        fpos = m_Chars.find_first_of(m_WiredChars[i]);

        // target character in wiredchars was not found in expected char list
        if(fpos == std::string::npos) return false;

        // string position out of expected range
        if( int(fpos) < 0 || int(fpos) >= int(found.size()) ) return false;

        // character already found?
        if(found[fpos]) return false;

        // checks passed, mark as found
        found[fpos] = true;
    }

    // check turnover char
    if(m_Chars.find_first_of(m_TurnoverChar) == std::string::npos) return false;

    return true;
}

int Rotor::getOutputPosition(ROTOR_SIDE rside, int tpos)
{
    // target character
    char tc;
    int opos = 0;
    size_t tpos = 0;

    // get local position (without rotation)
    int lpos = tpos + m_Position;
    if(lpos >= getCharCount()) lpos -= getCharCount();


    switch(rside)
    {
    case ROTOR_RIGHT:
        tc = m_WiredChars[lpos];
        tpos = m_Chars.find_first_of(tc);
        opos = int(tpos);

        break;
    case ROTOR_LEFT:
        break;
    default:
        break;
    }


}

void Rotor::show()
{
    StaticRotor *sr = dynamic_cast<StaticRotor*>(this);

    if(sr != NULL) std::cout << "Static Rotor Name:";
    else std::cout << "Rotor Name:";
    std::cout << m_Name << std::endl;

    for(int i = 0; i < int(m_Chars.length()); i++)
    {
        std::cout << i << " : " << m_Chars[i] << "->" << m_WiredChars[i] << std::endl;
    }
    std::cout << "Turnover:" << m_TurnoverChar << std::endl;
    std::cout << "Position:" << m_Position << " - " << m_Chars[m_Position] << std::endl;
}
//////////////////////////////////////////////////////
//
StaticRotor::~StaticRotor()
{

}
