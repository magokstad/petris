#include <ncurses.h>

#include "logic.cpp"

class Screen {
    private:
        GameState game_state = GameState();
    public:
        Screen() {
            initscr();
            noecho();
            cbreak();
            keypad(stdscr, TRUE);
            curs_set(0);
        }

        ~Screen() {
            endwin();
        }

        void sclear() {clear();}
        void srefresh() {refresh();}
        int sgetch() {return getch();}

        void update_screen() {
            sclear();
            wprint_map();
            wprint_current_block();
            get_tetra_state();
            srefresh();
            sgetch();
        }

        void get_tetra_state() {
            int x = game_state.getTetraHandler()->get_x();
            int y = game_state.getTetraHandler()->get_y();
            mvprintw(23,0, "x: %d, y: %d", x, y);
        }

        GameState *get_game_state() {
            return &game_state;
        }

    private:
        char * convert_map_to_string() {
            int *array = game_state.getMap().getMapArr().getArray();
            int size = game_state.getMap().getMapArr().getSize();
            int width = game_state.getMap().getMapArr().getWidth();
            char *str = new char[size];
            for (int i = 0; i < size; i++) {
                str[i] = array[i] + '0';
            }
            return str;
        }

        char translate_input(int input) {
            if (input == 0 ) {
                return '.';
            }
            else {
                return '#';
            }
        }

        void wprint_current_block() {
            int x = game_state.getTetraHandler()->get_x();
            int y = game_state.getTetraHandler()->get_y();
            Tetragon tetra = *game_state.getTetraHandler()->get_tetra();

            BlockArr *block = tetra.get_block();
            int length = block->getLength();
            int width = block->getWidth();

            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    if (block->get(i, j) == 1) {
                        char c = translate_input(block->get(i, j));
                        mvprintw(y + i, (x + j)*2, "%c", '#');
                        mvprintw(y + i, (x + j)*2 +1, "%c", '#');
                    }
                }
            }

        }

        void wprint_map() {
            int *array = game_state.getMap().getMapArr().getArray();
            int size = game_state.getMap().getMapArr().getSize();
            int width = game_state.getMap().getMapArr().getWidth();
            for (int i = 0; i < size; i++) {
                char c = translate_input(array[i]);
                // OG: mvprintw(i / width, i % width, "%c", c);
                // This doubles the number of characters printed so it looks more like a grid
                mvprintw(i / width, (i % width) * 2, "%c", c);
                mvprintw(i / width, (i % width) * 2 +1, "%c", c);
                
            }
        }


};