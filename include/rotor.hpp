#ifndef CLASS_ROTOR
#define CLASS_ROTOR

#include <string>
#include <vector>

enum ROTOR_SIDE{ROTOR_LEFT, ROTOR_RIGHT};

class Rotor
{
protected:

    std::string m_Name;
    std::string m_Chars;
    std::string m_WiredChars;
    char m_TurnoverChar;

    int m_Position;

    bool isValid();

public:
    Rotor(std::string rname, std::string chars, std::string wiredchars, char turnoverc);
    virtual ~Rotor();

    std::string getName() { return m_Name;}
    int getCharCount() { return int(m_Chars.length());}
    int getPosition() { return m_Position;}
    char getTurnoverChar() { return m_TurnoverChar;}
    int getOutputPosition(ROTOR_SIDE rside, int tpos);

    virtual bool setZeroPositionToChar(char tc);
    virtual void turn();

    virtual void show();
};

class StaticRotor: public Rotor
{
private:

public:
    StaticRotor(std::string rname, std::string chars) : Rotor(rname, chars, chars, chars[0]) {};
    ~StaticRotor();

    bool setZeroPositionToChar(char tc) { return false;}
    void turn() {};

};

class ReflectorRotor: public Rotor
{
private:

public:
    ReflectorRotor(std::string rname, std::string chars, std::string wiredchars) : Rotor(rname, chars, wiredchars, chars[0]) {};
    ~ReflectorRotor();

    bool setZeroPositionToChar(char tc) {return false;}
    void turn() {};
};
#endif // CLASS_ROTOR
