#include<iostream>
#include"Image.h"

using namespace std;
using namespace WLSGRA012;

void AddImages(Image & I1, Image & I2);

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
        cout << "subtracting images" << endl;
    } else if(command == "-i"){
        cout << "inverting image" << endl;
    } else if(command == "-l"){
        cout << "masking images" << endl;
    } else if(command == "-t"){
        cout << "threshold images" << endl;
    } else {
        cout << "no such command " << command << endl;
    }
}

void AddImages(Image & I1, Image & I2){
    Image out;
    out = I1 + I2;
    out.Write("Read.pgm");
}