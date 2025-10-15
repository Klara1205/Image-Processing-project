#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  ostringstream s;
  Image_print(&img, s);
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

TEST(test_width_height) {
  Image img;
  Image_init(&img, 30, 40);
  ASSERT_EQUAL(Image_width(&img), 30);
  ASSERT_EQUAL(Image_height(&img), 40);
}

TEST(test_imagemin) {
  
  Image img;
  Pixel black = {0, 0, 0};
  Image_init(&img, 1, 1);

  ASSERT_EQUAL(Image_width(&img), 1);
  ASSERT_EQUAL(Image_height(&img), 1);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), black));
}

TEST(test_imagefill) {
  Image img;
  Pixel blue = {0, 0, 255};
  Image_init(&img, 2, 3);
  Image_fill(&img, blue);

  for (int r = 0; r < Image_height(&img); ++r) {
    for (int c = 0; c < Image_width(&img); ++c) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, r, c), blue));
    }
  }
}

TEST(test_image_pixel) {
  Image img;
  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};

  Image_init(&img, 2, 2);
  Image_fill(&img, red);
  Image_set_pixel(&img, 1, 1, green);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 1), green));
}

TEST(test_image_init_stream_dimensions) {
  string input = "P3\n3 2\n255\n"
                 "0 0 0  255 0 0  0 255 0\n"
                 "0 0 255  255 255 255  100 100 100\n";
  istringstream ss(input);
  Image img;
  Image_init(&img, ss);

  ASSERT_EQUAL(Image_width(&img), 3);
  ASSERT_EQUAL(Image_height(&img), 2);
}

TEST(test_image_init_stream) {
  string input = "P3\n2 2\n255\n"
                 "255 0 0  0 255 0\n"
                 "0 0 255  255 255 255\n";
  istringstream ss(input);
  Image img;
  Image_init(&img, ss);

  Pixel red = {255, 0, 0};
  Pixel green = {0, 255, 0};
  Pixel blue = {0, 0, 255};
  Pixel white = {255, 255, 255};

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 1), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 0), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 1), white));
}

TEST(test_image_stream) {
  string input = "P3\n2 1\n255\n255 0 0 0 255 0 \n";
  istringstream ss_input(input);
  Image img;
  Image_init(&img, ss_input);

  ostringstream ss_output;
  Image_print(&img, ss_output);

  ASSERT_EQUAL(ss_output.str(), input);
}

TEST(test_image_equal) {
  Image img1, img2;
  Image_init(&img1, 2, 2);
  Image_init(&img2, 2, 2);

  Pixel white = {255, 255, 255};
  Image_fill(&img1, white);
  Image_fill(&img2, white);

  ASSERT_TRUE(Image_equal(&img1, &img2));
}

TEST(test_image_black) {
  Image img;
  Pixel black = {0, 0, 0};
  Image_init(&img, 2, 2);
  Image_fill(&img, black);

  for (int r = 0; r < Image_height(&img); ++r) {
    for (int c = 0; c < Image_width(&img); ++c) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, r, c), black));
    }
  }
  ostringstream out;
  Image_print(&img, out);
  string expected = "P3\n2 2\n255\n0 0 0 0 0 0 \n0 0 0 0 0 0 \n";
  ASSERT_EQUAL(out.str(), expected);
}

TEST(test_image_white) {
  Image img;
  Pixel white = {255, 255, 255};
  Image_init(&img, 2, 2);
  Image_fill(&img, white);

  for (int r = 0; r < Image_height(&img); ++r) {
    for (int c = 0; c < Image_width(&img); ++c) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, r, c), white));
    }
  }
  ostringstream out;
  Image_print(&img, out);
  string expected = "P3\n2 2\n255\n255 255 255 255 255 255 \n255 255 255 255 255 255 \n";
  ASSERT_EQUAL(out.str(), expected);
}

TEST_MAIN() // Do NOT put a semicolon here