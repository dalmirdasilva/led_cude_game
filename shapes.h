/**
 * Shapes definitions
 */

#include <stdint.h>

typedef struct {
    uint8_t x;
    uint8_t y;
    uint8_t z;
} point_t;

typedef struct {
    point_t point0;
    point_t point1;
} rectangle_t;

typedef struct {
    rectangle_t rec0;
    rectangle_t rec1;
} square_t;
