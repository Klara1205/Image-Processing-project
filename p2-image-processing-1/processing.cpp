#include <cassert>
#include <vector>
#include "processing.hpp"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  assert(energy != nullptr);
  assert(img != nullptr);
  int width = Image_width(img);
  int height = Image_height(img);

  Matrix_init(energy, width, height);
  
  if(width < 3 || height < 3) {
    for(int r = 0; r < height; r++) {
      for(int c = 0; c < width; c++) {
        *Matrix_at(energy, r ,c) = 0;
      }
    }
    return;
  }

  int max_energy = 0;

 for(int r = 1; r < height - 1; r++) {
  for(int c = 1; c < width - 1; c++) {
    Pixel N = Image_get_pixel(img, r - 1, c);
    Pixel S = Image_get_pixel(img, r + 1, c);
    Pixel E = Image_get_pixel(img, r, c + 1);
    Pixel W = Image_get_pixel(img, r, c - 1);
    *Matrix_at(energy, r, c) = squared_difference(N, S) + squared_difference(W, E);
    
    if(*Matrix_at(energy, r, c) > max_energy) {
      max_energy = *Matrix_at(energy, r, c);
    } 
  }
}

 for(int r = 0; r < height; r++) {
  for(int c = 0; c < width; c++) {
    if(r == 0 || r == height - 1 || c == 0 || c == width - 1) {
      *Matrix_at(energy, r, c) = max_energy;
    }
  }
 }
 
 for(int r = 0; r < height; r++) {
  for(int c = 0; c < width; c++) {
    assert(*Matrix_at(energy, r ,c) >= 0);
    assert(*Matrix_at(energy, r, c) <= max_energy);
  }
 }
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  assert(cost != nullptr);
  assert(energy != nullptr);
  assert(energy != cost);
  int width = Matrix_width(energy);
  int height = Matrix_height(energy);

  Matrix_init(cost, width, height);

  if(height == 0 || width == 0) {
    return;
  }

  for(int c = 0; c < width; c++) {
    *Matrix_at(cost, 0, c) = *Matrix_at(energy, 0, c);
    }

  if(height == 1) {
    return;
  }
  
  for(int r = 1; r < height; r++) {
    for(int c = 0; c < width; c++) {
      int cost_above = *Matrix_at(cost, r - 1, c);
      
      if(c > 0) {
        cost_above = std::min(cost_above, *Matrix_at(cost, r - 1, c - 1));
      }
      if(c < width - 1) {
        cost_above = std::min(cost_above, *Matrix_at(cost, r - 1, c + 1));
      }

      *Matrix_at(cost, r, c) = *Matrix_at(energy, r, c) + cost_above;
      

      }
    }
  }


// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, with index 0 representing the lowest numbered
//           row (top of image). The length of the returned vector is equal to
//           Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
//           Note: When implementing the algorithm, compute the seam starting at the
//           bottom row and work your way up.
vector<int> find_minimal_vertical_seam(const Matrix* cost) {
  assert(cost != nullptr);
  int width = Matrix_width(cost);
  int height = Matrix_height(cost);
  vector<int> seam(height);

  if(height == 0 || width == 0) {
    return seam;
  }

  int last_row = height - 1;
  int min_val = *Matrix_at(cost, last_row, 0);
  int min_col = 0;

  for(int c = 1; c < width; c++) {
    if(*Matrix_at(cost, last_row, c) < min_val) {
      min_val = *Matrix_at(cost, last_row, c);
      min_col = c;
    }
  }
  seam[last_row] = min_col;

  int cur_col = min_col;
  for(int r = last_row - 1; r >= 0; r--) {
    int best_col = cur_col;
    int best_val = *Matrix_at(cost, r, cur_col);
    if(cur_col > 0) {
      if(*Matrix_at(cost, r, cur_col - 1) <= best_val) {
        best_val = *Matrix_at(cost, r, cur_col - 1);
        best_col = cur_col -1;
      }
    }

    if(cur_col < width - 1) {
      if(*Matrix_at(cost, r, cur_col + 1) < best_val 
      || (*Matrix_at(cost, r, cur_col + 1) == best_val && cur_col + 1 < best_col)) {
        best_val = *Matrix_at(cost, r, cur_col + 1);
        best_col = cur_col + 1;
      } 
    }

    seam[r] = best_col;
    cur_col = best_col;

  }
  return seam;  
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  int width = Image_width(img);
  int height = Image_height(img);

  assert(img != nullptr);
  assert(width >= 2);
  assert(seam.size() == height);

  Image new_img;
  Image_init(&new_img, width - 1, height);
  assert(Image_width(&new_img)  == width - 1);
  assert(Image_height(&new_img) == height);

  for(int r = 0; r < height; r++) {
    int seam_col = seam[r];
    assert(seam_col >= 0 && seam_col < width);

    for(int c = 0; c < seam_col; c++) {
      Pixel p = Image_get_pixel(img, r, c);
      Image_set_pixel(&new_img, r, c, p);
    }

    for(int c = seam_col + 1; c < width; c++) {
      Pixel p = Image_get_pixel(img, r, c);
      Image_set_pixel(&new_img, r, c - 1, p);
    }
  }
  *img = new_img;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use a vector to hold the seam, and make sure that it has
//           the right size. You can use .data() on a vector to get
//           the underlying array.
void seam_carve_width(Image *img, int newWidth) {
  assert(img != nullptr);
  int width = Image_width(img);

  assert(newWidth > 0 && newWidth <= width);

  while(width > newWidth) {
    Matrix energy;
    compute_energy_matrix(img, &energy);

    Matrix cost;
    compute_vertical_cost_matrix(&energy, &cost);
    vector<int> seam = find_minimal_vertical_seam(&cost);
    remove_vertical_seam(img, seam);

    width = Image_width(img);
    
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  assert(img != nullptr);
  int height = Image_height(img);
  assert(newHeight > 0 && newHeight <= height);

  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  assert(img != nullptr);
  int height = Image_height(img);
  int width = Image_width(img);

  assert(newWidth > 0 && newWidth <= width);
  assert(newHeight > 0 && newHeight <= height);
  
  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}
