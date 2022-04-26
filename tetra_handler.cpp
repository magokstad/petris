#include <iostream>

#include "blocks.cpp"
#include "map.cpp"
#include "settings.c"


class TetraHandler {
    private:
        Map map = Map();
        Tetragon tetra;
        int x = START_X;
        int y = START_Y;

    public:
        TetraHandler(Map map) {
            this->tetra = Tetragon('.'); // default tetra
            this->map = map;
            this->x = START_X;
            this->y = START_Y;
        }

        TetraHandler() {
            TetraHandler(Map());
        }

        void change_tetra(char c) {
            tetra = Tetragon(c);
            x = START_X;
            y = START_Y;
        }

        void print_local_status() {
            std::cout << "x: " << x << ", y: " << y << std::endl;
            std::cout << "tetra: " << tetra.get_type() << std::endl;
        }

        bool can_move_left() {
            BlockArr *block = tetra.get_block();
            int length = block->getWidth();
            if (x - 1 < 0) {
                return false;
            }
            for (int i = 0; i < length; i++) {
                if (block->get(i, 0) == 1 && map.get(x - 1, y + i) == 1) {
                    return false;
                }

            }
            return true;
        }

        bool can_move_right() {
            BlockArr *block = tetra.get_block();
            int length = block->getLength();
            int width = block->getWidth();
            if (x + 1 > map.getMapArr().getWidth() - 1) {
                return false;
            }
            for (int i = 0; i < length; i++) {
                if (block->get(i, width) == 1 && map.get(x + width, y + i) == 1) {
                    return false;
                }
            }
            return true;
        }

        bool can_move_down() {
            BlockArr *block = tetra.get_block();
            int width = block->getWidth();
            int length = block->getLength();
            if (y + 1 > map.getMapArr().getLength() - 1) {
                return false;
            }
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < length; j++) {
                    if (block->get(j, i) == 1 && map.get(x + i, y + 1 + j) == 1) {
                        return false;
                    }
                }
            }
            return true;
        }

        void move_left() {
            if (can_move_left()) {
                this->x -= 1;
            }

        }

        void move_right() {
            if (can_move_right()) {
                this->x += 1;
            }

        }

        void move_down() {
            if (can_move_down()) {
                this->y += 1;
            }

        }

        int get_x() {
            return x;
        }

        int get_y() {
            return y;
        }

        Tetragon * get_tetra() {
            return &tetra;
        }

};