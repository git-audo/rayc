#include "map.h"

Map::Map() {};

Map::~Map() {
    delete map;
};

bool Map::load(size_t window_width, size_t window_height) {
    std::ifstream map_file("data/map.txt");
    if (!map_file.is_open())
        return false;

    map_file >> m_map_width >> m_map_height;
    
    uint32_t map_size = m_map_width*m_map_height;
    map = new char[sizeof(char) * map_size];

    char *cursor = map;        
    map_file.getline(cursor, map_size);
    
    while(map_file.getline(cursor, map_size)) {
        cursor += sizeof(char) * m_map_width;
    }
    
    m_wall_w = window_height / m_map_width;
    m_wall_h = window_height / m_map_height;	

    return true;
}

void Map::draw(uint32_t* frame_buffer, size_t window_width, size_t window_height) {
    for(size_t i=0; i<m_map_height; i++) {
        for(size_t j=0; j<m_map_width; j++) {
            if(map[j+i*m_map_width] == '0') {
                draw_rect(frame_buffer, window_width, window_height,
			  j*m_wall_w/3, i*m_wall_h/3, m_wall_w/3, m_wall_h/3);
            }
        }
    }
}

bool Map::is_wall_tile(float camera_x_pos, float camera_y_pos) {
    int normalized_x_pos = int(camera_x_pos / m_wall_w);
    int normalized_y_pos = int(camera_y_pos / m_wall_h);
	
    return (map[normalized_x_pos + normalized_y_pos*m_map_width] != ' ');
}
