#include <iostream>

#include "screen.cpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char const *argv[]) {    

    srand(time(NULL));
    
    Screen screen = Screen();
    screen.update_screen();
    
    for (;;) {
        if (screen.update_screen() == 1) {break;}
    }

    return 0;
}
