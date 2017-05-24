#include<iostream>
#include<string>
#include"Image.h"

using namespace std;
using namespace WLSGRA012;

string srcImagesDirectory = "srcImages/";

void AddImages(Image & I1, Image & I2);
void SubtractImages(Image & I1, Image & I2);
void InvertImage(Image & I1);
void MaskImages(Image & I1, Image & I2);
void ThreshImage(Image & I1, string f);

int main(int argc, char const *argv[]){
    using namespace std;
    Image I1, I2;
    if (argc == 4){
        //there are 2 images passed in
        I1 << argv[2]; //read image 1
        I2 << argv[3]; //read image 1
    } else if (argc == 3){
        //there is 1 image passed in 
        I1 << argv[2]; //read image 1
    }

    string command = string(argv[1]);
    if (command == "-a"){
        AddImages(I1, I2);
    } else if(command == "-s"){
        SubtractImages(I1, I2);
    } else if(command == "-i"){
        InvertImage(I1);
    } else if(command == "-l"){
        MaskImages(I1, I2);
    } else if(command == "-t"){
        ThreshImage(I1, argv[3]);
    } else {
        cout << "no such command " << command << endl;
    }
}

void AddImages(Image & I1, Image & I2){
    if (!I1.SameSize(I2)){
        cout << "Files are not the same size. Can not add." << endl;
        return;
    }
    Image out;
    out = I1 + I2;
    out >> "Add.pgm";
}

void SubtractImages(Image & I1, Image & I2){
    if (!I1.SameSize(I2)){
        cout << "Files are not the same size. Can not add." << endl;
        return;
    }
    Image out;
    out = I1 - I2;
    out >> "Sub.pgm";
}

void InvertImage(Image & I1){
    Image out;
    out = !I1;
    out >> "Invert.pgm";
}

void ThreshImage(Image & I1, string f){
    int thresh = stoi(f);
    Image out;
    out = I1 * thresh;
    out >> "Thresh.pgm";
}

void MaskImages(Image & I1, Image & I2){
    if (!I1.SameSize(I2)){
        cout << "Files are not the same size. Can not add." << endl;
        return;
    }
    Image out;
    out = I1 / I2;
    out >> "Mask.pgm";
}
