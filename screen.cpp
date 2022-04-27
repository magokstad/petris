#include <ncurses.h>
#include <sys/time.h>

#include "logic.cpp"

class Screen {
    private:
        GameState game_state;
        long msec;
        long msec_counter;
    public:
        Screen() {
            game_state = GameState();
            initscr();
            noecho();
            nodelay(stdscr, TRUE); // no need to wait for input
            cbreak();
            keypad(stdscr, TRUE);
            curs_set(0);

            // get time at start
            timeval start_time;
            gettimeofday(&start_time, NULL);
            msec = start_time.tv_sec * 1000 + start_time.tv_usec / 1000;

            start_color();

            init_color(COLOR_ORANGE, 1000, 500, 0);

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
            wprint_current_block();
            get_tetra_state();
            srefresh();
            // wait 500ms
            if (get_time_dif() > 500) {
                game_state.getTetraHandler()->move_down();
                msec = msec_counter;


            }
            if (game_state.handle_input() == 1) {return 1;};
            return 0;
        }

        long get_time_dif() {
            timeval end_time;
            gettimeofday(&end_time, NULL);
            long end_msec = end_time.tv_sec * 1000 + end_time.tv_usec / 1000;
            long dif = end_msec - msec;
            msec_counter = end_msec;
            return dif;
        }

        void get_tetra_state() {
            int x = game_state.getTetraHandler()->get_x();
            int y = game_state.getTetraHandler()->get_y();
            int leftest = game_state.getTetraHandler()->get_tetra()->get_block()->get_leftest();
            int rightest = game_state.getTetraHandler()->get_tetra()->get_block()->get_rightest();
            int lowest = game_state.getTetraHandler()->get_tetra()->get_block()->get_lowest();
            color_int(WSPACE);
            mvprintw(23,0, "x: %d, y: %d", x, y);
            mvprintw(24,0, "leftest: %d, rightest: %d, lowest: %d", leftest, rightest, lowest);
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
                return '?';
            }
        }

        void color_int(int val) {
            if      (val == WSPACE) {attron(COLOR_PAIR(BGC_PAIR));}
            else if (val == BINT_T) {attron(COLOR_PAIR(TBLOCK_PAIR));}
            else if (val == BINT_L) {attron(COLOR_PAIR(LBLOCK_PAIR));}
            else if (val == BINT_J) {attron(COLOR_PAIR(JBLOCK_PAIR));}
            else if (val == BINT_I) {attron(COLOR_PAIR(IBLOCK_PAIR));}
            else if (val == BINT_O) {attron(COLOR_PAIR(OBLOCK_PAIR));}
            else if (val == BINT_S) {attron(COLOR_PAIR(SBLOCK_PAIR));}
            else if (val == BINT_Z) {attron(COLOR_PAIR(ZBLOCK_PAIR));}
            else                    {attron(COLOR_PAIR(BASIC_TETRA_PAIR));}
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