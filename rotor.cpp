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

bool Rotor::setZeroPositionToChar(char tc)
{
    size_t tpos = m_Chars.find_first_of(tc);
    if(tpos == std::string::npos)
    {
        std::cout << tc << " is not a valid char for " << m_Name << " in setZeroPositionToChar!\n";
        return false;
    }

    m_Position = int(tpos);
    return true;
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
    size_t foundpos = 0;

    // check that target position is valid
    if(tpos < 0 || tpos >= getCharCount())
    {
        std::cout << "Error in getOutputPosition, tpos is out of range!\n";
        return 0;
    }

    // get local position (without rotation)
    int lpos = tpos + m_Position;
    if(lpos >= getCharCount()) lpos -= getCharCount();

    // get wired position output (with rotation applied)
    switch(rside)
    {
    // input on left side of rotor (in)
    case ROTOR_RIGHT:
        // get the character wired to the right side
        tc = m_WiredChars[lpos];
        // get the out position of tc on the opposite side
        foundpos = m_Chars.find_first_of(tc);
        opos = int(foundpos);
        // apply rotation
        opos -= m_Position;
        if(opos < 0) opos += getCharCount();
        break;
    case ROTOR_LEFT:
        // get the character wired to the left side
        tc = m_Chars[lpos];
        // get the out position of tc on the opposite side
        foundpos = m_WiredChars.find_first_of(tc);
        opos = int(foundpos);
        // apply rotation
        opos -= m_Position;
        if(opos < 0) opos += getCharCount();
        break;
    default:
        std::cout << "Error in getOutputPosition, rotor enum undefined!\n";
        opos = 0;
        break;
    }

    return opos;
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
    std::cout << "Position:" << m_Position << std::endl;
    std::cout << "Char at pos 0 = " << m_Chars[m_Position] << std::endl;
    std::cout << "Left output at pos 0 = " << getOutputPosition(ROTOR_RIGHT, 0) << std::endl;
    std::cout << "Right output at pos 0 = " << getOutputPosition(ROTOR_LEFT, 0) << std::endl;
}
//////////////////////////////////////////////////////
//
StaticRotor::~StaticRotor()
{

}

//////////////////////////////////////////////////////
//
ReflectorRotor::~ReflectorRotor()
{

}
