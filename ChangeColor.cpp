#include <iostream>

namespace colors {
    const char* RED = "\033[91m";
    const char* GREEN = "\033[92m";
    const char* YELLOW = "\033[93m";
    const char* BLUE = "\033[94m";
    const char* MAGENTA = "\033[95m";
    const char* CYAN = "\033[96m";
    const char* RESET = "\033[0m";  
}

int main() {
    std::cout << colors::RED << "This text is red!" << colors::RESET << std::endl;
    std::cout << colors::GREEN << "This text is green!" << colors::RESET << std::endl;
    std::cout << colors::BLUE << "This text is blue!" << colors::RESET << std::endl;

    return 0;
}