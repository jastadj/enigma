#include "app.hpp"

#include <string>
#include <vector>

App::App()
{

    // init curses
    initscr();

    // start main loop
    mainLoop();

}

App::~App()
{
    endwin();
}


void App::mainLoop()
{
    bool quit = false;

    int ch = 0;
    int ccount = 0;

    const std::string validchars = m_Enigma.getValidChars();
    std::string msg_input;
    std::string msg_output;

    while(!quit)
    {
        clear();

        std::vector<int> pos = m_Enigma.getRotorPositions();


        // draw rotor positions
        for(int i = 0; i < int(pos.size()); i++)
        {
            mvprintw(0, int(pos.size()-i)*2+2 , "%d", i+1);
            mvprintw(1, int(pos.size()-i)*2+2 , "%c", validchars[pos[i]]);
        }

        mvprintw(3,0,"%s", msg_input.c_str());
        mvprintw(4,0,"%s", msg_output.c_str());

        ch = getch();

        if(ch == 27) quit = true;
        else
        {
            // if character is lower-case, convert it to upper case
            if(ch >= int('a') && ch <= int('z')) ch -= 32;

            // check if enter char is valid enigma char
            size_t tpos = 0;
            tpos = validchars.find_first_of(char(ch));

            // if input character is a valid enigma input
            if(tpos != std::string::npos)
            {
                // increment character count
                ccount++;

                // if character count is 5, add spaces to msg strings
                // this puts output text in blocks of 4 chars
                if(ccount >= 5)
                {
                    ccount = 0;
                    msg_input.push_back(' ');
                    msg_output.push_back(' ');
                }

                // add it to input string
                msg_input.push_back(char(ch));

                // add encoded character to output
                msg_output.push_back(m_Enigma.enterInput(char(ch)) );
            }
        }

        refresh();
    }
}
