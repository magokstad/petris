#include <iostream>

#include "screen.cpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char const *argv[]) {    

    srand(time(NULL));
    
    Screen screen = Screen();
    screen.get_game_state()->add_block('l'); // FIXME should be random
    //screen.get_game_state()->set_a_cube(4,4);
    screen.update_screen();
    
    for (;;) {
        //if (screen.get_game_state()->handle_input() == 1) {break;}
        if (screen.update_screen() == 1) {break;}
    }

    return 0;
}
