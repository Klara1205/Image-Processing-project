#include <cassert>
#include "Matrix.hpp"


void Matrix_init(Matrix* mat, int width, int height) {
  assert(mat != nullptr);
  assert(0 < width && 0 < height); 
  mat->width = width;
  mat->height = height;
mat->data.assign(width * height, 0);
}
  
void Matrix_print(const Matrix* mat, std::ostream& os) {
  assert(mat!= nullptr);
  os << mat->width << " " << mat->height << "\n";
  for (int row = 0; row < mat->height; ++row) {
    for (int col = 0; col < mat->width; ++col) {
      int index = row * mat->width + col;
      os << mat->data[index] << " ";
    }
    os << "\n"; 
  }
}

int Matrix_width(const Matrix* mat) {
 assert(mat!= nullptr); 
  return mat->width;
}


int Matrix_height(const Matrix* mat) {
  assert(mat!= nullptr);
  return mat->height;
}


int* Matrix_at(Matrix* mat, int row, int column) {

  assert(mat!= nullptr);
  assert(0 <= row && row < mat->height);
  assert(0 <= column && column < mat->width);
  int i = row * mat->width + column;
  return &mat->data[i];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  assert(mat != nullptr);
  assert(0 <= row && row < mat->height);
  assert(0 <= column && column < mat->width);
  int i = row * mat->width + column;
  return &mat->data[i];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  assert(mat!= nullptr);
    for (int r = 0; r < mat->height; ++r) {
        for (int c = 0; c < mat->width; ++c) {
            *Matrix_at(mat, r, c) = value;
        }
    }
}

void Matrix_fill_border(Matrix* mat, int value) {
  assert(mat!= nullptr);
      for (int c = 0; c < mat->width; ++c) {
        *Matrix_at(mat, 0, c) = value;                 
        *Matrix_at(mat, mat->height - 1, c) = value;     
    }

    // Left and right columns
    for (int r = 0; r < mat->height; ++r) {
        *Matrix_at(mat, r, 0) = value;                   
        *Matrix_at(mat, r, mat->width - 1) = value;      
    }
}


// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
   assert(mat!= nullptr);
   int max = mat->data[0];
    for (int r = 0; r < mat->height; ++r) {
        for (int c = 0; c < mat->width; ++c) {
            int val = *Matrix_at(mat, r, c);
            if (val > max) {
                max = val;
            }
        }
    }
    return max;
}

int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  assert(mat != nullptr);
    assert(0 <= row && row < mat->height);
    assert(0 <= column_start && column_start < column_end && column_end <= mat->width);

    int mincol = column_start;
    int minval = *Matrix_at(mat, row, column_start);

    for (int c = column_start + 1; c < column_end; ++c) {
        int val = *Matrix_at(mat, row, c);
        if (val < minval) {
            minval = val;
            mincol = c;
        }
    }
    return mincol;
}


int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {                         
  assert(mat != nullptr);
  assert(0 <= row && row < mat->height);
  assert(0 <= column_start && column_start < column_end && column_end <= mat->width);
    int min = *Matrix_at(mat, row, column_start);
    for (int c = column_start + 1; c < column_end; ++c) {
        int val = *Matrix_at(mat, row, c);
        if (val < min) {
            min = val;
        }
    }
    return min;
}

