#include <cstdlib>

#include "enigma.hpp"

int main(int argc, char *argv[])
{

    Enigma enigma;

    std::string teststring = "THISISATEST";

    std::cout << teststring << std::endl;
    std::cout << enigma.enterString(teststring) << std::endl;

    std::cout << "\n\n";

    teststring = "NLKKNCKHLOO";
    enigma.reset();
    std::cout << teststring << std::endl;
    std::cout << enigma.enterString(teststring) << std::endl;

    enigma.show();

    return 0;
}
