C++ implementation of a content-aware image resizing algorithm using seam carving. The program identifies and removes low-energy pixel seams to reduce an image’s width and height while preserving important visual features

Main components:  
Matrix.cpp: Defines 2D matrix operations for image channels  
Image.cpp: Manages RGB image data and PPM input/output  
processing.cpp: Implements energy, cost, and seam-carving logic  
resize.cpp: Main driver for resizing images via CLI  

