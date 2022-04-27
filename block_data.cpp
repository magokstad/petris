#include <iostream>

class BlockInfo {
    public:
        const int length;
        const int width;
        const int *array;
        BlockInfo(int length, int width, int* array) : array(array), length(length), width(width) {}
};

class BlockData {
    public:
        static const BlockInfo t_block;
        static const BlockInfo l_block;
        static const BlockInfo j_block;
        static const BlockInfo o_block;
        static const BlockInfo i_block;
        static const BlockInfo s_block;
        static const BlockInfo z_block;

        static BlockInfo get_block(char c) {
            switch (c) {
                case 't': 
                    return t_block;
                case 'l':
                    return l_block;
                case 'j':
                    return j_block;
                case 'o':
                    return o_block;
                case 'i':
                    return i_block;
                case 's':
                    return s_block;
                case 'z':
                    return z_block;
                default:
                    return BlockInfo(0, 0, nullptr);
            }
        }
};

int t_block_array[] = {
    0, 0, 0,
    1, 1, 1,
    0, 1, 0
};

int l_block_array[] = {
    0, 2, 0,
    0, 2, 0,
    0, 2, 2
};

int j_block_array[] = {
    0, 3, 0,
    0, 3, 0,
    3, 3, 0
};

int o_block_Array[] = {
    0, 0, 0, 0,
    0, 4, 4, 0,
    0, 4, 4, 0,
    0, 0, 0, 0
};

int i_block_array[] = {
    0, 0, 5, 0,
    0, 0, 5, 0,
    0, 0, 5, 0,
    0, 0, 5, 0
};

int s_block_array[] = {
    0, 0, 0,
    0, 6, 6,
    6, 6, 0
};

int z_block_array[] = {
    0, 0, 0,
    7, 7, 0,
    0, 7, 7
};


const BlockInfo BlockData::t_block = BlockInfo(3, 3, t_block_array);
const BlockInfo BlockData::l_block = BlockInfo(3, 3, l_block_array);
const BlockInfo BlockData::j_block = BlockInfo(3, 3, j_block_array);
const BlockInfo BlockData::o_block = BlockInfo(4, 4, o_block_Array);
const BlockInfo BlockData::i_block = BlockInfo(4, 4, i_block_array);
const BlockInfo BlockData::s_block = BlockInfo(3, 3, s_block_array);
const BlockInfo BlockData::z_block = BlockInfo(3, 3, z_block_array);

