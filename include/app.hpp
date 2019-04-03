#ifndef CLASS_APP
#define CLASS_APP

#include "enigma.hpp"
#include "curses.h"

class App
{
private:

    // enigma machine
    Enigma m_Enigma;

    // main loop
    void mainLoop();

public:
    App();
    ~App();
};
#endif // CLASS_APP
