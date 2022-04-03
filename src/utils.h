#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <cstddef>

uint32_t pack_rgb(const uint8_t r, const uint8_t g, const uint8_t b);

void draw_rect(uint32_t* pixels, const size_t win_width, const size_t win_height,
               const size_t x, const size_t y, const size_t w, const size_t h,
               const uint32_t color = pack_rgb(103, 58, 43));

void draw_circle(uint32_t* pixels, const size_t win_width, const size_t win_height,
                 const size_t x, const size_t y, const size_t radius);

#endif
