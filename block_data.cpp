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

const BlockInfo BlockData::t_block = BlockInfo(2, 3, new int[6]{
    1, 1, 1,
    0, 1, 0
});
const BlockInfo BlockData::l_block = BlockInfo(3, 2, new int[6]{
    1, 0,
    1, 0,
    1, 1
});
const BlockInfo BlockData::j_block = BlockInfo(3, 2, new int[6]{
    0, 1,
    0, 1,
    1, 1
});
const BlockInfo BlockData::o_block = BlockInfo(2, 2, new int[4]{
    1, 1,
    1, 1
});
const BlockInfo BlockData::i_block = BlockInfo(2, 4, new int[8]{
    1, 1, 1, 1,
    0, 0, 0, 0
});
const BlockInfo BlockData::s_block = BlockInfo(2, 3, new int[6]{
    0, 1, 1,
    1, 1, 0
});
const BlockInfo BlockData::z_block = BlockInfo(2, 3, new int[6]{
    1, 1, 0,
    0, 1, 1
});

