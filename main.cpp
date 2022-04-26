#include <iostream>

#include "screen.cpp"

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main(int argc, char const *argv[])
{
    /*
    Map map = Map();
    TetraHandler hand = TetraHandler(map);
    hand.print_local_status();
    hand.change_tetra('s');
    hand.print_local_status();
    hand.move_left();
    hand.print_local_status();
    */

    /*
    GameState game = GameState();
    game.getTetraHandler()->print_local_status();
    game.getTetraHandler()->change_tetra('t');
    game.getTetraHandler()->print_local_status();
    */
    
    
    Screen screen = Screen();
    screen.update_screen();
    screen.get_game_state()->move_left();
    screen.get_game_state()->move_left();
    screen.update_screen();
    screen.get_game_state()->move_down();
    screen.update_screen();


    /*
    Tetragon t = Tetragon('t');
    cout << t.get_block()->getSize() << endl;
    Map m = Map();
    m.set(19, 9, 1);
    m.print();
    TetraHandler hand = TetraHandler(m);
    hand.change_tetra('o');
    */

    return 0;
}
