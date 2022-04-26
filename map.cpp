#include <iostream>

class MapArr {
    private:
        int *array;
        int length = 20;
        int width = 10;
        int size = length * width;
    public:
        MapArr() {
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
            array[i * width + j] = value;
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

        MapArr getMapArr() {
            return mapArr;
        }

        int get(int i, int j) {
            return mapArr.get(i, j);
        }

        void set(int i, int j, int value) {
            mapArr.set(i, j, value);
        }


};