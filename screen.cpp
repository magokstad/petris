#include <ncurses.h>
#include <sys/time.h>

#include "logic.cpp"

class Screen {
    private:
        GameState game_state;
    public:
        Screen() {
            game_state = GameState();
            initscr();
            noecho();
            nodelay(stdscr, TRUE); // no need to wait for input
            cbreak();
            keypad(stdscr, TRUE);
            curs_set(0);

            start_color();

            init_color(COLOR_ORANGE, 1000, 500, 0);
            init_color(COLOR_DGRAY, 200, 200, 200);

            init_pair(BGC_PAIR, COLOR_WHITE, COLOR_BLACK); // FIXME should be in a settings file
            init_pair(BASIC_TETRA_PAIR, COLOR_WHITE, COLOR_WHITE); // FIXME should be in a settings file
            init_pair(TBLOCK_PAIR, COLOR_MAGENTA, COLOR_MAGENTA);
            init_pair(LBLOCK_PAIR, COLOR_ORANGE, COLOR_ORANGE);
            init_pair(JBLOCK_PAIR, COLOR_BLUE, COLOR_BLUE); // FIXME should be orange
            init_pair(OBLOCK_PAIR, COLOR_YELLOW, COLOR_YELLOW);
            init_pair(IBLOCK_PAIR, COLOR_CYAN, COLOR_CYAN);
            init_pair(SBLOCK_PAIR, COLOR_GREEN, COLOR_GREEN);
            init_pair(ZBLOCK_PAIR, COLOR_RED, COLOR_RED); //FIXME should be correct red
        }

        ~Screen() {
            endwin();
        }

        void sclear() {clear();}
        void srefresh() {refresh();}
        int sgetch() {return getch();}

        int update_screen() {
            //sclear();
            wprint_map();
            wprint_ghost_block();
            wprint_current_block();
            get_tetra_state();
            srefresh();
            
            // wait 500ms and return 1 if game is over
            return game_state.drop_loop();
        }

        void get_tetra_state() {
            int x = game_state.getTetraHandler()->get_x();
            int y = game_state.getTetraHandler()->get_y();
            int gy = game_state.getTetraHandler()->get_gy();
            int leftest = game_state.getTetraHandler()->get_tetra()->get_block()->get_leftest();
            int rightest = game_state.getTetraHandler()->get_tetra()->get_block()->get_rightest();
            int lowest = game_state.getTetraHandler()->get_tetra()->get_block()->get_lowest();
            color_int(WSPACE);
            mvprintw(23,0, "x: %d, y: %d, gx: %d", x, y, gy);
            mvprintw(24,0, "leftest: %d, rightest: %d, lowest: %d", leftest, rightest, lowest);
            mvprintw(25,0, "Lines cleared: %d", TempScore::get_score());
        }

        GameState *get_game_state() {
            return &game_state;
        }

    // FIXME too many chars in this section are hardcoded. Make macro in settings.c
    private:
        char * convert_map_to_string() {
            int *array = game_state.getMap()->getMapArr()->getArray();
            int size = game_state.getMap()->getMapArr()->getSize();
            int width = game_state.getMap()->getMapArr()->getWidth();
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
            else if (input >= 1){
                return '#';
            }
            else {
                return '^';
            }
        }

        void color_int(int val) {
            int color_pair = 0;
            switch (val) {
                case WSPACE:
                    color_pair = BGC_PAIR;
                    break;
                case BINT_T:
                    color_pair = TBLOCK_PAIR;
                    break;
                case BINT_L:
                    color_pair = LBLOCK_PAIR;
                    break;
                case BINT_J:
                    color_pair = JBLOCK_PAIR;
                    break;
                case BINT_I:
                    color_pair = IBLOCK_PAIR;
                    break;
                case BINT_O:
                    color_pair = OBLOCK_PAIR;
                    break;
                case BINT_S:
                    color_pair = SBLOCK_PAIR;
                    break;
                case BINT_Z:
                    color_pair = ZBLOCK_PAIR;
                    break;
                default:
                    color_pair = BASIC_TETRA_PAIR;
            }
            attron(COLOR_PAIR(color_pair));
        }

        void color_off() {
            // Turns off all color
            for (int i = 0; i < LAST_COLOR_PAIR; i++) {
                attroff(COLOR_PAIR(i));
            }
        }

        void wprint_current_block() {
            int x = game_state.getTetraHandler()->get_x();
            int y = game_state.getTetraHandler()->get_y();
            Tetragon *tetra = game_state.getTetraHandler()->get_tetra();

            BlockArr *block = tetra->get_block();
            int length = block->getLength();
            int width = block->getWidth();

            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    if (block->get(i, j) >= 1) {
                        int val = tetra->get_block()->get(i, j); 
                        char c = translate_input(val);
                        color_int(val);
                        mvprintw(y + i, (x + j)*2, "%c", c);
                        mvprintw(y + i, (x + j)*2 +1, "%c", c);
                    }
                }
            }

        }

        // Too repetitive fix
        void wprint_ghost_block() {
            int x = game_state.getTetraHandler()->get_x();
            int y = game_state.getTetraHandler()->get_gy();
            Tetragon *tetra = game_state.getTetraHandler()->get_tetra();

            BlockArr *block = tetra->get_block();
            int length = block->getLength();
            int width = block->getWidth();

            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    if (block->get(i, j) >= 1) {
                        int val = BGHOST; 
                        char c = translate_input(val);
                        color_int(val);
                        mvprintw(y + i, (x + j)*2, "%c", c);
                        mvprintw(y + i, (x + j)*2 +1, "%c", c);
                    }
                }
            }
        }

        void wprint_map() {
            int *array = game_state.getMap()->getMapArr()->getArray();
            int size = game_state.getMap()->getMapArr()->getSize();
            int width = game_state.getMap()->getMapArr()->getWidth();
            for (int i = 0; i < size; i++) {
                int val = array[i];
                char c = translate_input(val);
                // OG: mvprintw(i / width, i % width, "%c", c);
                // This doubles the number of characters printed so it looks more like a grid
                color_int(val);
                mvprintw(i / width, (i % width) * 2, "%c", c);
                mvprintw(i / width, (i % width) * 2 +1, "%c", c);
                
            }
        }


};