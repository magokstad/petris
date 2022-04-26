#include <ncurses.h>

class NcursesInputHandler {
    public:
        char get_input() {
            char c = getch();
            return c;
        }

};