#include "plugboard.hpp"
#include <iostream>

PlugBoard::PlugBoard(std::string pname, std::string chars)
{
    m_Name = pname;
    m_Chars = chars;

    clear();
}

PlugBoard::~PlugBoard()
{

}

void PlugBoard::clear()
{
    m_WiredChars = "";
}

bool PlugBoard::configure(std::string wiredchars)
{

    //check that each character is valid
    for(int i = 0; i < int(wiredchars.length()); i++)
    {
        size_t vpos = m_Chars.find_first_of(wiredchars[i]);

        if(vpos == std::string::npos)
        {
            std::cout << "Unable to configure plugboard wired chars, invalid characters!\n";
            return false;
        }
    }

    // check that theres an even number of characters
    if( int(wiredchars.length())%2)
    {
        std::cout << "Unable to configure plugboard wire chars, uneven pairs.\n";
        return false;
    }

    // check for doubles
    for(int i = 0; i < int(wiredchars.length()); i++)
    {
        int ccount = 0;

        for(int n = 0; n < int(wiredchars.length()); n++)
        {
            if(wiredchars[i] == wiredchars[n]) ccount++;
        }

        if(ccount != 1)
        {
            std::cout << "Unable to configure plugboard wire chars, duplicate chars found!\n";
            return false;
        }
    }

    m_WiredChars = wiredchars;

    return true;
}

char PlugBoard::inputChar(char tc)
{
    for(int i = 0; i < int(m_WiredChars.length())/2; i++)
    {
        if(m_WiredChars[i] == tc) return m_WiredChars[i+1];
        else if(m_WiredChars[i+1] == tc) return m_WiredChars[i];
    }

    return tc;
}

void PlugBoard::show()
{
    std::cout << "PlugBoard Configuration:\n";

    for(int i = 0; i < int(m_WiredChars.length())/2; i++)
    {
        std::cout << m_WiredChars[i*2] << ":" << m_WiredChars[(i*2)+1] << std::endl;
    }
}
