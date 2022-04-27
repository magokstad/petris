#include <iostream>
#include "block_data.cpp"
#include "settings.c"

class BlockArr {
    private:
        int *array;
        int leftest, rightest, lowest;
        int size, length, width;
    public:
        BlockArr(int length, int width, int* array) {
            this->length = length;
            this->width = width;
            this->size = length * width;
            this->array = array;
            update_extremes();
        }

        BlockArr() {
            this->length = 0;
            this->width = 0;
            this->size = 0;
            this->array = nullptr;
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

        int get_leftest() {
            return leftest;
        }

        int get_rightest() {
            return rightest;
        }

        int get_lowest() {
            return lowest;
        }

        int get(int l, int w) {
            return array[l * width + w];
        }

        void rotate_right() {
            int *new_array = new int[size];
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    new_array[j * length + i] = array[i * width + (width - 1 - j)];
                }
            }
            //delete[] array;
            this->array = new_array;
            int tmp = this->length;
            this->length = this->width;
            this->width = tmp;
            update_extremes();
        }

        void rotate_left() {
            int *new_array = new int[size];
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    new_array[i * width + j] = array[(length - 1 - i) * width + j];
                }
            }
            //delete[] array;
            this->array = new_array;
            int tmp = this->length;
            this->length = this->width;
            this->width = tmp;
            update_extremes();
        }

    private:

        void update_extremes() {
            int *widsum = new int[width];
            int *lensum = new int[length];
            for (int i = 0; i < width; i++) {
                widsum[i] = 0;
            }
            for (int i = 0; i < length; i++) {
                lensum[i] = 0;
            }
            for (int i = 0; i < size; i++) {
                widsum[i % width] += array[i];
                lensum[i / width] += array[i];
            }
            this->leftest = 0;
            this->rightest = 0;
            this->lowest = 0;
            for (int i = 0; i < width; i++) {
                if (widsum[i] > 0) {
                    this->leftest = i;
                    break;
                }
            }
            for (int i = width - 1; i >= 0; i--) {
                if (widsum[i] > 0) {
                    this->rightest = i;
                    break;
                }
            }
            for (int i = width -1; i >= 0; i--) {
                if (lensum[i] > 0) {
                    this->lowest = i;
                    break;
                }
            }
            //delete[] widsum;
            //delete[] lensum;
        }
};

class Tetragon {
    protected:
        BlockArr block_arr;
        char block_type;
    public:
        Tetragon(char type) {
            // gets block type 
            BlockInfo info = BlockData::get_block(type);
            block_type = type;
            // creates block array
            block_arr = BlockArr((int)info.length, (int)info.width, (int*)info.array);
        }

        Tetragon() {
            block_type = '\0';
            block_arr = BlockArr(0, 0, NULL);
        }

        //~Tetragon() {
        //    delete block_arr;
        //}

        char get_type() {
            return block_type;
        }

        int get_val() {
            return char_to_val(block_type);
        }

        BlockArr* get_block() {
            return &block_arr;
        }

        BlockArr get_copy_of_block() {
            return block_arr;
        }

    private:
        int char_to_val(char c) {
            switch (c) {
                case 'i':
                    return BINT_I;
                case 'j':
                    return BINT_J;
                case 'l':
                    return BINT_L;
                case 'o':
                    return BINT_O;
                case 's':
                    return BINT_S;
                case 't':
                    return BINT_T;
                case 'z':
                    return BINT_Z;
                default:
                    return B_NULL;
            }
        }
};