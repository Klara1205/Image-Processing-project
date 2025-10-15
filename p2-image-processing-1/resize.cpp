#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include "Image.hpp"
#include "processing.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 4 && argc != 5) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
     << "WIDTH and HEIGHT must be less than or equal to original" << endl; 
        return 1;
    }

    Image img;
    string in_filename = argv[1];
    string out_filename = argv[2];
    int new_width = stoi(argv[3]);


    ifstream fin(in_filename);
    if(!fin.is_open()) {
        cout << "Error opening file: " << in_filename << endl;
    }

    Image_init(&img, fin);

    int new_height = Image_height(&img);
    if(argc == 5) {
        new_height = stoi(argv[4]);
    }

    if(new_width <= 0 || new_width > Image_width(&img) 
    || new_height <= 0 || new_height > Image_height(&img)) {
        cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
             << "WIDTH and HEIGHT must be less than or equal to original" << endl;
        return 1;
    }

    seam_carve(&img, new_width, new_height);

    ofstream fout(out_filename);
    if(!fout.is_open()) {
        cout << "Error opening file: " << in_filename << endl;
    }

    Image_print(&img, fout);

    return 0;
}

