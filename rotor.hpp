#ifndef CLASS_ROTOR
#define CLASS_ROTOR

#include <string>
#include <vector>

enum ROTOR_SIDE{ROTOR_LEFT, ROTOR_RIGHT};

class Rotor
{
protected:

    std::string m_Name;
    std::string m_WiredChars;
    char m_TurnoverChar;

    int m_Position;

    bool isValid();

public:
    Rotor(std::string rname, std::string wiredchars, char turnoverc);
    virtual ~Rotor();

    static const std::string m_Chars;

    virtual void turn();
    int getCharCount() { return int(m_Chars.length());}

    int getOutputPosition(ROTOR_SIDE rside, int tpos);

    virtual void show();
};

class StaticRotor: public Rotor
{
private:

public:
    StaticRotor(std::string rname) : Rotor(rname, m_Chars, m_Chars[0]) {};
    ~StaticRotor();

    void turn() {};

};
#endif // CLASS_ROTOR
