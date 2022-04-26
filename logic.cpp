#include <iostream>

#include "tetra_handler.cpp"
#include "ncurses_input.cpp"

class GameState {
    private:
        Map map;
        TetraHandler hand;
        NcursesInputHandler input;

    public:
        GameState() {
            map = Map();
            hand = TetraHandler(map);
            input = NcursesInputHandler();
            //add_block('s'); //FIXME
        }

        Map * getMap() {
            return &map;
        }

        TetraHandler *getTetraHandler() {
            return &hand;
        }

        void add_block(char tetrac) {
            hand.change_tetra(tetrac);
        }

        void set_a_cube(int x, int y) {
            map.set(x, y);
        }

        char get_input() {
            return input.get_input();
        }

        int handle_input() {
            char c = get_input();
            switch (c) {
                case 'a':
                    hand.move_left();
                    break;
                case 'd':
                    hand.move_right();
                    break;
                case 's':
                    hand.move_down();
                    break;
                case 'w':
                    hand.rotate_right();
                    break;
                case 'o':
                    return 1;
                default:
                    break;
            }
            return 0;
        }

        void move_left() {
            hand.move_left();
        }

        void move_right() {
            hand.move_right();
        }

        void move_down() {
            hand.move_down();
        }
};

