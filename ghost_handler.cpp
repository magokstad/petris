#include "tetra_handler.cpp"


/*
// DEPRECATED CODE 
class GhostHandler : TetraHandler {
    public:
        // should probably be private?
        void set_ghost_tetra(Tetragon * t, int x, int y) {
            this->tetra = *t;
            this->x = x;
            this->y = y;
            int * arr = tetra.get_block()->get_array();
            for (int i = 0; i < tetra.get_block()->getSize(); i++) {
                if (arr[i] >= 1) {
                    arr[i] = -2;
                }
            }
            while (can_move_down()) {
                move_down();
            }
            map.place_tetra(t, x, y);
            
        }

};*/