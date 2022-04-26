#include <iostream>

#include "blocks.cpp"
#include "map.cpp"
#include "settings.c"

// This class most certainly contains codesmell... FIXME
class TetraHandler {
    private:
        Map map;
        Tetragon tetra;
        int x;
        int y;

        Tetragon last_rotatable_state;

    public:
        TetraHandler(Map map) {
            this->tetra = Tetragon('.'); // default tetra
            this->map = map;
            this->x = START_X;
            this->y = START_Y;
        }

        TetraHandler() {
            this->tetra = Tetragon('.'); // default tetra
            this->map = Map();
            this->x = START_X;
            this->y = START_Y;
        }

        void update_rotatable_state() {
            if (can_rotate_right()) {
                this->last_rotatable_state = this->tetra;
            }
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
            int length = block->getLength();
            int width = block->getWidth();
            if ((x-1) + block->get_leftest() < 0) {
                return false;
            }
            x--;
            bool ans = true;
            for (int l = 0; l < length; l++) {
                for (int w = 0; w < width; w++) {
                    if (block->get(l, w) == 1 && map.get(y + l, x + w) == 1) {
                        ans = false;
                    }
                }
            }
            x++;
            return ans;
        }

        bool can_move_right() {
            BlockArr *block = tetra.get_block();
            int length = block->getLength();
            int width = block->getWidth();
            int max_map_width = map.getMapArr()->getWidth();
            if ((x+1) + block->get_rightest() > max_map_width-1) {
                return false;
            }
            x++;
            bool ans = true;
            for (int l = 0; l < length; l++) {
                for (int w = 0; w < width; w++) {
                    if (block->get(l, w) == 1 && map.get(y+l, x+w) == 1) {
                        ans = false;
                    }
                }
            }
            x--;
            return ans;
        }

        bool can_move_down() {
            BlockArr *block = tetra.get_block();
            int width = block->getWidth();
            int length = block->getLength();
            int max_map_y = map.getMapArr()->getLength();
            if ((y+1) + block->get_lowest() > max_map_y-1) {
                return false;
            }
            y++;
            bool ans = true;
            for (int l = 0; l < length; l++) {
                for (int w = 0; w < width; w++) {
                    if (block->get(l, w) == 1 && map.get(y+l, x+w) == 1) {
                        ans = false;
                    }
                }
            }
            y--;
            return ans;
        }


        bool can_rotate_right(Tetragon *t) {
            //BlockArr *block = tetra.get_block(); 
            BlockArr rotablock = tetra.get_copy_of_block();
            rotablock.rotate_right();

            int length = rotablock.getLength();
            int width = rotablock.getWidth();
            
            int map_max_x = map.getMapArr()->getWidth() - 1;
            int right_most_x = x + rotablock.get_rightest();

            int map_max_y = map.getMapArr()->getLength() - 1;
            int bottom_most_y = y + rotablock.get_lowest();

            int left_most_x = x + rotablock.get_leftest();

            if (right_most_x > map_max_x) {
                wall_kick_right();
                return false;
            }
            if (bottom_most_y > map_max_y) {
                return false;
            }
            if (left_most_x < 0) {
                wall_kick_left();
                return false;
            }
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    if (rotablock.get(i, j) == 1 && map.get(y + i, x + j) == 1) {
                        if (!wall_kick_right()) {
                            wall_kick_left();
                        }
                        return false;
                    }
                }
            }
            return true;
        }

        bool can_rotate_right() {
            return can_rotate_right(&this->tetra);
        }

        bool wall_kick_right() {
            if (can_move_left()) {
                x--;
                if (can_rotate_right()) {
                    rotate_right();
                    return true;
                }
            }
            x++;    
            return false;
        }

        bool wall_kick_left() {
            if (can_move_right()){
                x++;
                if (can_rotate_right()) {
                    rotate_right();
                    return true;
                }

            }
            x--;
            return false;
        }

        void rotate_right() {
            if (can_rotate_right()) {
                tetra.get_block()->rotate_right();
            }
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