#include "utils.h"

uint32_t pack_rgb(const uint8_t r, const uint8_t g, const uint8_t b)
{
    return (255<<24) + (b<<16) + (g<<8) + r;
}
