#include <iostream>

#include "tetra_handler.cpp"
#include "ncurses_input.cpp"

class GameState {
    private:
        Map map;
        TetraHandler hand;
        NcursesInputHandler input;
        std::string tetralist;

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

        void set_a_cube(int x, int y, int value) {
            map.set(x, y,value);
        }

        char get_random_tetra_char() {
            std::string tetras = "szljoti";
            int random_index = rand() % tetras.length();
            return tetras[random_index];
        }

        void place_tetra() {
            while (hand.can_move_down()) {
                hand.move_down();
            }
            map.place_tetra(hand.get_tetra(), hand.get_x(), hand.get_y());
            char ny_tetra = get_random_tetra_char();
            hand.change_tetra(ny_tetra); //FIXME
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
                case ' ':
                    place_tetra();
                    break;
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

