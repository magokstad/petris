#include <iostream>
#include "block_data.cpp"

class BlockArr {
    private:
        int *array;
        int size, length, width;
    public:
        BlockArr(int length, int width, int* array) {
            this->length = length;
            this->width = width;
            this->size = length * width;
            this->array = array;
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

        int& get(int i, int j) {
            return array[i * width + j];
        }

        void rotate_right() {
            int *new_array = new int[size];
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    new_array[j * length + i] = array[i * width + (width - 1 - j)];
                }
            }
            delete[] array;
            array = new_array;
            int tmp = length;
            length = width;
            width = tmp;
        }

        void rotate_left() {
            int *new_array = new int[size];
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    new_array[i * width + j] = array[(length - 1 - i) * width + j];
                }
            }
            delete[] array;
            array = new_array;
            int tmp = length;
            length = width;
            width = tmp;
        }
};

class Tetragon {
    protected:
        BlockArr *block_arr;
        char block_type;
    public:
        Tetragon(char type) {
            // gets block type 
            BlockInfo info = BlockData::get_block(type);
            block_type = type;
            // creates block array
            block_arr = new BlockArr((int)info.length, (int)info.width, (int*)info.array);
        }

        Tetragon() {
            block_type = '\0';
            block_arr = new BlockArr(0, 0, NULL);
        }

        //~Tetragon() {
        //    delete block_arr;
        //}

        char& get_type() {
            return block_type;
        }

        BlockArr* get_block() {
            return block_arr;
        }
};