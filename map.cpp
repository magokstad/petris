#include <iostream>
//#include "blocks.cpp"
#include "temp_score.cpp"

class MapArr {
    private:
        int *array;
        int length;
        int width;
        int size;
    public:
        MapArr() {
            this->length = 20;
            this->width = 10;
            this->size = this->length * this->width;
            array = new int[size];
            for (int i = 0; i < size; i++) {
                array[i] = 0;
            }
        }

        int getSize() {
            return size;
        }

        int getLength() {
            return length;
        }

        int getWidth() {
            return width;
        }

        int get(int i, int j) {
            return array[i * width + j];
        }

        void set(int i, int j, int value) {
            this->array[i * width + j] = value;
        }

        int* getArray() {
            return array;
        }
};

class Map {
    private:
        MapArr mapArr;
    public:
        Map() {
            mapArr = MapArr();
        }

        void print() {
            int *array = mapArr.getArray();
            int size = mapArr.getSize();
            int width = mapArr.getWidth();
            for (int i = 0; i < size; i++) {
                std::cout << array[i] << " ";
                if (i % width == width - 1) {
                    std::cout << "\n";
                }
            }
        }

        MapArr * getMapArr() {
            return &mapArr;
        }

        int get(int i, int j) {
            return mapArr.get(i, j);
        }

        void set(int i, int j, int value) {
            mapArr.set(i, j, value);
        }

        // places a block at the given position and checks for cleared rows
        void place_tetra(Tetragon *tetra, int x, int y) {
            BlockArr *block = tetra->get_block();
            int length = block->getLength();
            int width = block->getWidth();
            for (int l = 0; l < length; l++) {
                for (int w = 0; w < width; w++) {
                    if (block->get(l, w) >= 1) {
                        mapArr.set(y + l, x + w, tetra->get_val());
                    }
                }
            }
            clear_rows_if_filled();
        }

    private:

        // Checks if the row is filled.
        bool check_row_filled(int l) {
            int *array = mapArr.getArray();
            int width = mapArr.getWidth();
            for (int i = 0; i < width; i++) {
                if (array[l * width + i] == 0) {
                    return false;
                }
            }
            return true;
        }

        // Clears the row
        void clear_row(int l) {
            int *array = mapArr.getArray();
            int width = mapArr.getWidth();
            for (int i = 0; i < width; i++) {
                array[l * width + i] = -1;
            }
        }

        // Moves the resulting rows down after clearing rows
        // TODO this isnt working correctly. Think of a solution
        void move_resulting_down() {
            int *array = mapArr.getArray();
            int length = mapArr.getLength();
            int width = mapArr.getWidth();

            // Inital check
            for (int l = length-1; l >= 0; l--) {
                if (array[l * width ] == -1) {
                    int line_to_move = l;
                    int count_l = l;
                    while (array[count_l * width] == -1) {
                        count_l--;
                    }
                    if (count_l < 0) {break;}
                    for (int w = 0; w < width; w++) {
                        array[line_to_move * width + w] = array[count_l * width + w];
                        array[count_l * width + w] = -1;
                    }
                }
            }
            // Double check
            for (int l = 0; l < length; l++) {
                if (array[l * width ] == -1) {
                    for (int w = 0; w < width; w++) {
                        array[l * width + w] = 0;
                    }
                }
            }
        }

        // Clears a row if it is filled
        void clear_row_if_filled(int l) {
            if (check_row_filled(l)) {
                clear_row(l);
                TempScore::increment_score();
            }
        }

        // Clears all rows if they are filled
        void clear_rows_if_filled() {
            int length = mapArr.getLength();
            for (int i = 0; i < length; i++) {
                clear_row_if_filled(i);
            }
            move_resulting_down();
        }


};