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
            tetralist = "";
            update_tetralist();
            add_block(get_random_tetra_char());
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
            update_tetralist();
            char ans = tetralist[0];
            tetralist.erase(0,1);
            return ans;
        }

        void update_tetralist() {
            std::string tetras = "szljoti";
            if (tetralist.length() <= tetras.length()) {
                std::string blocks = "szljoti";
                for (int i = 0; i < blocks.length(); i++) {
                    int j = rand() % blocks.length();
                    char tmp = blocks[i];
                    blocks[i] = blocks[j];
                    blocks[j] = tmp;
                }
                tetralist += blocks;
            }
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

