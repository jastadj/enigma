#include "enigma.hpp"

Enigma::Enigma():
m_Chars("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
{
    m_PlugBoard = NULL;

    // init rotors
    reset();
}

Enigma::~Enigma()
{
    clear();
}

void Enigma::clear()
{
    for(int i = 0; i < int(m_Rotors.size()); i++)
    {
        delete m_Rotors[i];
    }

    m_Rotors.clear();

    if(m_PlugBoard != NULL)
    {
        delete m_PlugBoard;
        m_PlugBoard = NULL;
    }
}

void Enigma::reset()
{
    clear();

    m_Rotors.push_back( new StaticRotor("Static Rotor", m_Chars) );
    m_Rotors.push_back( new Rotor("Rotor1", m_Chars, "EKMFLGDQVZNTOWYHXUSPAIBRCJ", 'Q') );
    m_Rotors.push_back( new Rotor("Rotor2", m_Chars, "AJDKSIRUXBLHWTMCQGZNPYFVOE", 'E') );
    m_Rotors.push_back( new Rotor("Rotor3", m_Chars, "BDFHJLCPRTXVZNYEIWGAKMUSQO", 'V') );
    m_Rotors.push_back( new ReflectorRotor("Reflector", m_Chars, "EJMZALYXVBWFCRQUONTSPIKHGD") );

    m_PlugBoard = new PlugBoard("Plugboard", m_Chars);
    m_PlugBoard->configure("");
}

std::vector<int> Enigma::getRotorPositions()
{
    std::vector<int> pos;

    for(int i = 0; i < int(m_Rotors.size()); i++)
    {
        StaticRotor *scheck = dynamic_cast<StaticRotor*>(m_Rotors[i]);
        ReflectorRotor *rcheck = dynamic_cast<ReflectorRotor*>(m_Rotors[i]);

        // if rotor is NOT static or reflector, add position to list
        if(scheck == NULL && rcheck == NULL)
        {
             pos.push_back(m_Rotors[i]->getPosition());
        }
    }

    return pos;

}

bool Enigma::configurePlugBoard(std::string pb)
{
    if(!m_PlugBoard)
    {
        std::cout << "PlugBoard is NULL!\n";
        return false;
    }

    if(!m_PlugBoard->configure(pb))
    {
        std::cout << "Unable to configure plugboard!\n";
        return false;
    }

    return true;
}

void Enigma::stepRotors(int rnum)
{
    if(rnum < 0 || rnum >= int(m_Rotors.size()) )
    {
        std::cout << "Error stepRotors, rotor number out of range!\n";
        return;
    }

    StaticRotor *scheck = dynamic_cast<StaticRotor*>(m_Rotors[rnum]);
    ReflectorRotor *rcheck = dynamic_cast<ReflectorRotor*>(m_Rotors[rnum]);

    // if rotor is static or reflector, skip
    if(scheck != NULL || rcheck != NULL) stepRotors(rnum+1);


    // turn rotor
    m_Rotors[rnum]->turn();
    if(DEBUG) std::cout << "Rotor " << m_Rotors[rnum]->getName() << " turned over.\n";

    // if turnover character is hit, rotate next rotor
    char tc = m_Rotors[rnum]->getTurnoverChar();
    size_t tcpos = m_Chars.find_first_of(tc);
    if(tcpos == std::string::npos)
    {
        std::cout << "Error stepRotors, turnover character not found in m_Chars for " << m_Rotors[rnum]->getName() << std::endl;
        return;
    }

    // if turnover character hit, rotate next rotor
    if( m_Rotors[rnum]->getPosition() - int(tcpos) == 0)
    {
        if(DEBUG) std::cout << m_Rotors[rnum]->getName() << " turnover character '" << m_Rotors[rnum]->getTurnoverChar() << "' hit, rotating next rotor...\n";
        stepRotors(rnum+1);
    }
}

bool Enigma::isValid()
{
    // check that there are a valid amount of rotors (1 static, 1 reflector, and at least 1 encoding rotor)
    if( int(m_Rotors.size()) < 3)
    {
        std::cout << "Invalid rotor setup.  Need first static, then at least 1 encoding, and last reflector.\n";
        return false;
    }

    // check that first rotor is static
    StaticRotor *scheck = dynamic_cast<StaticRotor*>(m_Rotors[0]);
    ReflectorRotor *rcheck = dynamic_cast<ReflectorRotor*>(m_Rotors.back());
    if(scheck == NULL)
    {
        std::cout << "First rotor is not static!\n";
        return false;
    }
    else if(rcheck == NULL)
    {
        std::cout << "Last rotor is not reflector!\n";
        return false;
    }

    return true;
}

bool Enigma::isCharValid(char tc)
{
    size_t tpos = m_Chars.find_first_of(tc);

    if(tpos == std::string::npos) return false;

    return true;
}

char Enigma::enterInput(char tc)
{

    if(!isValid()) return '?';

    // check that input character is valid
    if(!isCharValid(tc)) return '?';
    size_t vchar = m_Chars.find_first_of(tc);

    // run signal through plugboard
    if(m_PlugBoard)
    {
        vchar = m_Chars.find_first_of(m_PlugBoard->inputChar(tc) );
    }

    // step rotors
    stepRotors();

    // run signal up to the reflector
    int sigpos = int(vchar);
    if(DEBUG) std::cout << "Starting signal pos = " << sigpos << std::endl;
    // right to left
    for(int i = 0; i < int(m_Rotors.size() -1); i++)
    {
        if(DEBUG)
        {
            std::cout << m_Rotors[i]->getName() << " IN=" << sigpos << " OUT=";
            sigpos = m_Rotors[i]->getOutputPosition(ROTOR_RIGHT, sigpos);
            std::cout << sigpos << std::endl;
            m_Rotors[i]->show();
            std::cout << "\n";
        }
        else sigpos = m_Rotors[i]->getOutputPosition(ROTOR_RIGHT, sigpos);

    }

    // put through reflector
    if(DEBUG)
    {
        std::cout << m_Rotors.back()->getName() << " IN=" << sigpos << " OUT=";
        sigpos = m_Rotors.back()->getOutputPosition(ROTOR_RIGHT, sigpos);
        std::cout << sigpos << std::endl;
        m_Rotors.back()->show();
        std::cout << "\n";
    }
    else sigpos = m_Rotors.back()->getOutputPosition(ROTOR_RIGHT, sigpos);


    // left to right
    for(int i = int(m_Rotors.size()-2); i >= 0; i--)
    {
        if(DEBUG)
        {
            std::cout << m_Rotors[i]->getName() << " IN=" << sigpos << " OUT=";
            sigpos = m_Rotors[i]->getOutputPosition(ROTOR_LEFT, sigpos);
            std::cout << sigpos << std::endl;
            m_Rotors[i]->show();
            std::cout << "\n";
        }
        else sigpos = m_Rotors[i]->getOutputPosition(ROTOR_LEFT, sigpos);
    }

    // run back out through plugboard
    if(m_PlugBoard)
    {
        sigpos = int(m_Chars.find_first_of( m_PlugBoard->inputChar(m_Chars[sigpos]) ) );
    }

    // return output character
    if(DEBUG) std::cout << "Output : " << m_Chars[sigpos] << std::endl;

    return m_Chars[sigpos];
}

std::string Enigma::enterString(std::string ts)
{
    std::string ostring;

    for(int i = 0; i < int(ts.length()); i++)
    {
        ostring.push_back(enterInput(ts[i]));
    }

    return ostring;
}

void Enigma::show()
{
    std::cout << "Enigma Machine\n";
    std::cout << "--------------\n";
    std::cout << "Valid Chars:\n";
    std::cout << m_Chars << std::endl;

    std::cout << std::endl;
    std::cout << "Enigma Machine Rotor Count:" << m_Rotors.size() << std::endl;

    for(int i = 0; i < int(m_Rotors.size()); i++)
    {
        std::string rtype;

        StaticRotor *scheck = dynamic_cast<StaticRotor*>(m_Rotors[i]);
        ReflectorRotor *rcheck = dynamic_cast<ReflectorRotor*>(m_Rotors[i]);

        if(scheck != NULL) rtype = "Static Rotor";
        else if(rcheck != NULL) rtype = "Reflector Rotor";
        else rtype = "Encoding Rotor";

        std::cout << i << ":" << rtype << " \"" << m_Rotors[i]->getName() << "\"\n";
    }

    std::vector<int> rpos = getRotorPositions();
    std::cout << "Rotor Positions:\n";
    for(int i = 0; i < int(rpos.size()); i++) std::cout << rpos[i] << "(" << m_Chars[rpos[i]] << ") ";
    std::cout << std::endl;

    if(m_PlugBoard)
    {
        std::cout << "\n";
        m_PlugBoard->show();
    }
}
