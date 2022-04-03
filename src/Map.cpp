#include "map.h"

Map::Map(size_t map_width, size_t map_height, size_t window_width, size_t window_height)
    : m_map_width(map_width), m_map_height(map_height) {
    m_wall_w = window_width / (2*m_map_width);
    m_wall_h = window_height / m_map_height;	
};

void Map::draw(uint32_t* frame_buffer, size_t window_width, size_t window_height) {
    for(size_t i=0; i<m_map_height; i++) {
        for(size_t j=0; j<m_map_width; j++) {
            if(map[j+i*m_map_width] == '0') {
                draw_rect(frame_buffer, window_width, window_height,
			  j*m_wall_w, i*m_wall_h, m_wall_w, m_wall_h);
            } else if(map[j+i*m_map_width] == '1') {
                draw_rect(frame_buffer, window_width, window_height,
			  j*m_wall_w, i*m_wall_h, m_wall_w, m_wall_h, pack_rgb(168, 211, 178));
            }
        }
    }
}

bool Map::is_tile_empty(float camera_x_pos, float camera_y_pos) {
    int normalized_x_pos = int(camera_x_pos / m_wall_w);
    int normalized_y_pos = int(camera_y_pos / m_wall_h);
	
    return (map[normalized_x_pos + normalized_y_pos*m_map_width] != ' ');
}
