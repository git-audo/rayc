#include "utils.h"

uint32_t pack_rgb(const uint8_t r, const uint8_t g, const uint8_t b) {
    return (255<<24) + (b<<16) + (g<<8) + r;
}

void draw_rect(uint32_t* pixels, const size_t win_width, const size_t win_height,
               const size_t x, const size_t y, const size_t w, const size_t h,
               const uint32_t color) {
    for(size_t i=y; i<h+y; i++) {
        for(size_t j=x; j<w+x; j++) {
            pixels[j+i*win_width] = color;
        }
    }
}

void draw_circle(uint32_t* pixels, const size_t win_width, const size_t win_height,
                 const size_t x, const size_t y, const size_t radius) { 
    for(size_t i=y-radius; i<y+radius; i++) {
        for(size_t j=x-radius; j<x+radius; j++) {
            if(((j-x)*(j-x)+(i-y)*(i-y)) < radius*radius)
                pixels[j+i*win_width] = pack_rgb(130, 196, 255);
        }
    }
}
