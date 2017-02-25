#ifndef ASCII_CURSES_H
#define ASCII_CURSES_H

#include <ncurses.h>
#include <png.h>

#define ASCII_DRAW		1
#define ASCII_CONVERT		2
#define ASCII_BACKGROUND_DARK	4

typedef unsigned char BYTE;

/* Single RGBA pixel */
typedef struct {
	BYTE r, g, b, a;
} pixelRGBA_t;

/* Single RGB pixel */
typedef struct {
	BYTE r, g, b;
} pixelRGB_t;

/* Image data */
typedef struct {
	BYTE *pixel_data;
	int width, height;
	int color_type;
	int pixel_size;
} bitmap_t;

/* ASCII image data */
typedef struct {
	bitmap_t *bmp;
	BYTE *ascii_data;
	int width, height;
	int pos_x, pos_y;
	int block_size;
	int flags;
} ascii_image_t;

/* Read PNG image and store it in a bitmap_t structure */
bitmap_t *read_png_image(const char *file_name);

/* Return pointer to pixel at location (y, x) */
BYTE *pixel_at(bitmap_t *bmp, int y, int x);

/* Calculate grayscale value out a pixel taking into account its alpha, if present */
BYTE grayscale_value(BYTE *pixel, int color_type, int background);
/* Average the grayscale value of all pixels in a row of size count starting from (y, x) */
BYTE avg_grayscale(ascii_image_t *img, int y, int x, int count);
/* Average the grayscale value of all pixels in a block of size * size starting from (y, x) */
BYTE avg_grayscale_block(ascii_image_t *img, int y, int x);

/* Calculate ASCII equivaluent of the specified image */
void to_ascii(ascii_image_t *img);
/* Just print the damn thing */
void print_ascii(ascii_image_t *img);

#endif /* ASCII_CURSES_H */
