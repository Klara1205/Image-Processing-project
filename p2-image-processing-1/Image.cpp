#include <cassert>
#include "Image.hpp"

void Image_init(Image* img, int width, int height) {
assert(img != nullptr);
assert(width >0 && height>0);
img->width = width;
img->height = height;
Matrix_init(&img->red_channel, width, height);
Matrix_init(&img->green_channel, width, height);
Matrix_init(&img->blue_channel, width, height);
Matrix_fill(&img->red_channel, 0);
Matrix_fill(&img->green_channel, 0);
Matrix_fill(&img->blue_channel, 0);
}

void Image_init(Image* img, std::istream& is) {
    assert(img != nullptr);
    std::string val;
    is >>val;
    assert(val== "P3");
    int width, height, max_val;
    is >> width>> height >> max_val;
    assert(width >0 && height > 0);
    assert(max_val == MAX_INTENSITY);
    Image_init(img, width, height);
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            int red, green, blue;
            is >> red >> green >> blue;

            *Matrix_at(&img->red_channel, r, c) = red;
            *Matrix_at(&img->green_channel, r, c) = green;
            *Matrix_at(&img->blue_channel, r, c) = blue;
        }
    }
}

void Image_print(const Image* img, std::ostream& os) {
assert(img != nullptr);
os << "P3\n";
os << img->width << " " << img->height << "\n";
os << MAX_INTENSITY << "\n";
for (int r = 0; r < img->height; ++r) {
  for (int c = 0; c < img->width; ++c) {
    os << *Matrix_at(&img->red_channel, r, c) << " ";
    os << *Matrix_at(&img->green_channel, r, c) << " ";
    os << *Matrix_at(&img->blue_channel, r, c) << " ";
  }
  os << "\n";
}
}

int Image_width(const Image* img) {
    assert(img != nullptr);
    return img->width;
}

int Image_height(const Image* img) {
    assert(img != nullptr);
    return img->height;
}

Pixel Image_get_pixel(const Image* img, int row, int column) {
    assert(img != nullptr);
    assert(0 <= row && row < Image_height(img));
    assert(0 <= column && column < Image_width(img));

    Pixel p;
    p.r = *Matrix_at(&img->red_channel, row, column);
    p.g = *Matrix_at(&img->green_channel, row, column);
    p.b = *Matrix_at(&img->blue_channel, row, column);
    return p;
}

void Image_set_pixel(Image* img, int row, int column, Pixel color) {
    assert(img != nullptr);
    assert(0 <= row && row < Image_height(img));
    assert(0 <= column && column < Image_width(img));

    *Matrix_at(&img->red_channel, row, column) = color.r;
    *Matrix_at(&img->green_channel, row, column) = color.g;
    *Matrix_at(&img->blue_channel, row, column) = color.b;
}


void Image_fill(Image* img, Pixel color) {
    assert(img != nullptr);

    for (int r = 0; r < Image_height(img); ++r) {
        for (int c = 0; c < Image_width(img); ++c) {
            Image_set_pixel(img, r, c, color);
        }
    }
}