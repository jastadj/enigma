#ifndef CLASS_PLUGBOARD
#define CLASS_PLUGBOARD

#include <string>
#include <vector>

class PlugBoard
{
private:

    std::string m_Name;
    std::string m_Chars;

    std::string m_WiredChars;
public:
    PlugBoard(std::string pname, std::string chars);
    ~PlugBoard();

    bool configure(std::string wiredchars);

    char inputChar(char tc);

    void clear();

    void show();

};
#endif // CLASS_PLUGBOARD
