#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include "utils.h"

class Map {
public:
    Map(size_t map_width, size_t map_height, size_t window_width, size_t window_height);

    void draw(uint32_t* frame_buffer, size_t window_width, size_t window_height);
    bool is_tile_empty(float camera_x_pos, float camera_y_pos);

    char map[101] = "0000000000"\
                    "0        0"\
                    "0    000 0"\
                    "0        0"\
                    "0      000"\
                    "0  0     0"\
                    "0  0     0"\
                    "0  000   0"\
                    "0        0"\
                    "0000000000";

    size_t m_map_width;
    size_t m_map_height;
    size_t m_wall_w;
    size_t m_wall_h;
};

#endif
