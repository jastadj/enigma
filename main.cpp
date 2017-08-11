#include <cstdlib>

#include "enigma.hpp"

int main(int argc, char *argv[])
{

    Enigma enigma;

    std::string teststring = "T";

    std::cout << teststring << std::endl;
    std::cout << enigma.enterString(teststring) << std::endl;
    return 0;
}
