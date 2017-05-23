#include<iostream>
#include<string>
#include"Image.h"

using namespace std;
using namespace WLSGRA012;

void AddImages(Image & I1, Image & I2);
void SubtractImages(Image & I1, Image & I2);
void InvertImage(Image & I1);
void ThreshImage(Image & I1, string f);

int main(int argc, char const *argv[]){
    using namespace std;
    Image I1, I2;
    if (argc == 4){
        //there are 2 images passed in
        I1.Read(argv[2]);
        I2.Read(argv[3]);
    } else if (argc == 3){
        //there is 1 image passed in 
        I1.Read(argv[2]);
    }

    string command = string(argv[1]);
    if (command == "-a"){
        AddImages(I1, I2);
    } else if(command == "-s"){
        SubtractImages(I1, I2);
    } else if(command == "-i"){
        InvertImage(I1);
    } else if(command == "-l"){
        cout << "masking images" << endl;
    } else if(command == "-t"){
        ThreshImage(I1, argv[3]);
    } else {
        cout << "no such command " << command << endl;
    }
}

void AddImages(Image & I1, Image & I2){
    Image out;
    out = I1 + I2;
    out.Write("Add.pgm");
}

void SubtractImages(Image & I1, Image & I2){
    Image out;
    out = I1 - I2;
    out.Write("Sub.pgm");
}

void InvertImage(Image & I1){
    Image out;
    out = !I1;
    out.Write("Invert.pgm");
}

void ThreshImage(Image & I1, string f){
    int thresh = stoi(f);
    Image out;
    out = I1 * thresh;
    out.Write("Thresh.pgm");
}
