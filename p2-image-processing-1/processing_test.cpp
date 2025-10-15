#include "processing.hpp"
#include "Image.hpp"
#include "Matrix.hpp"
#include "unit_test_framework.hpp"

using namespace std;

static Image make_solid_image(int width, int height, Pixel color) {
    Image img;
    Image_init(&img, width, height);
    for (int r = 0; r < height; r++) {
        for (int c = 0; c < width; c++) {
            Image_set_pixel(&img, r, c, color);
        }
    }
    return img;
}

Test(test_energy_small_images) {
    Image img1 = make_solid_image(1, 1, {100, 100, 100});
    Matrix energy;
    compute_energy_matrix(&img1, &energy);
    ASSERT_EQUAL(Matrix_width(&eneggy), 1);
    ASSERT_EQUAL(Matrix_height(&enegry), 1);
    ASSERT_EQUAL(*Matrix_at(&energy, 0, 0), 0);

    Image img2 = make_solid_image(5, 1, {50, 50, 50});
    Matrix energy2;
    compute_energy_matrix(&img2, &energy2);
    ASSERT_EQUAL(Matrix_width(&energy2), 5);
    ASSERT_EQUAL(Matrix_height(&energy), 1);
    for(int c = 0; c < 5; c++) {
        ASSERT_EQUAL(*Matrix_at(&energy, 0, c), 0);
    }
}

TEST(test_cost_single_row) { 
    Matrix energy;
    Matrix_init(&energy, 3, 1)
    *Matrix_at(&energy, 0, 0) = 5; 
    *Matrix_at(&energy, 0, 1) = 2; 
    *Matrix_at(&energy, 0, 2) = 7;

    Matrix cost;
    compute_vertical_cost_matrix(&energy, &cost);

    ASSERT_EQUAL(*Matrix_at(&cost, 0, 0), 5);
    ASSERT_EQUAL(*Matrix_at(&cost, 0, 1), 2); 
    ASSERT_EQUAL(*Matrix_at(&cost, 0, 2), 7);
}

TEST(test_find_seam_tie_breaking) {
    Matrix cost;
    Matrix_init(&cost, 3, 2);
    *Matrix_at(&cost, 1, 0) = 5;
    *Matrix_at(&cost, 1, 1) = 5;
    *Matrix_at(&cost, 0, 0) = 10;
    *Matrix_at(&cost, 0, 1) = 10;

    vector<int> seam = find_minimal_vertical_seam(&cost);
    ASSERT_EQUAL(seam.back(), 0);
}

TEST(test_remove_seam_basic) {
    Image img = make_solid_image(3, 2, {10, 20, 30});
    vector<int> seam = {1, 1};
    remove_vertical_seam(&img, seam);

    ASSERT_EQUAL(Image_width(&img), 2);
    ASSERT_EQUAL(Image_height(&img), 2);

}

TEST_MAIN()

