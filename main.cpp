#include <cstdlib>

#include "enigma.hpp"

int main(int argc, char *argv[])
{

    Enigma enigma;

    std::cout << enigma.enterString("THISISATEST") << std::endl;

    enigma.reset();
    enigma.configurePlugBoard("");

    std::cout << enigma.enterString("THISISATEST") << std::endl;


    return 0;
}
