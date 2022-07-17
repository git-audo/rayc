#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <fstream>
#include "utils.h"

class Map {
public:
    Map();
    ~Map();    

    bool load(size_t window_width, size_t window_height);
    void draw(uint32_t* frame_buffer, size_t window_width, size_t window_height);
    bool is_wall_tile(float camera_x_pos, float camera_y_pos);

private:    
    size_t m_map_width;
    size_t m_map_height;
    size_t m_wall_w;
    size_t m_wall_h;

    char *map;
};

#endif
