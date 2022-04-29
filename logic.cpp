#include <iostream>

#include "tetra_handler.cpp"
#include "ncurses_input.cpp"

class GameState {
    private:
        Map map;
        TetraHandler hand;
        NcursesInputHandler input;
        std::string tetralist;

        long msec;
        long msec_counter;

    public:
        GameState() {
            map = Map();
            hand = TetraHandler(map);
            input = NcursesInputHandler();

            // get time at start
            timeval start_time;
            gettimeofday(&start_time, NULL);
            msec = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;

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

        // Theres logic in screen.... FIXME
        long get_time_dif() {
            timeval end_time;
            gettimeofday(&end_time, NULL);
            long end_msec = end_time.tv_sec * 1000 + end_time.tv_usec / 1000;
            long dif = end_msec - msec;
            msec_counter = end_msec;
            return dif;
        }

        int drop_loop() {
            if (get_time_dif() > 500) {
                if (hand.can_move_down()) {
                    hand.move_down();
                }
                else {
                    place_tetra();
                }
                msec = msec_counter;
                hand.update_ghost_coords();
            }
            // This handles input and returns 1 if game is over
            if (handle_input() == 1) {return 1;};
            return 0;
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
            bool update_ghost = true;
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
                    update_ghost = false;
                    break;
            }
            if (update_ghost) {
                hand.update_ghost_coords();
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

