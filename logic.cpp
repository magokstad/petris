#include <iostream>

#include "tetra_handler.cpp"

class GameState {
    private:
        Map map;
        TetraHandler hand;

    public:
        GameState() {
            map = Map();
            hand = TetraHandler(map);
            add_block('s');
        }

        Map getMap() {
            return map;
        }

        TetraHandler *getTetraHandler() {
            return &hand;
        }

        void add_block(char tetrac) {
            hand.change_tetra(tetrac);
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

