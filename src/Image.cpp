#include<iostream>
#include<fstream>
#include<sstream>
#include<memory>
#include"Image.h"

using namespace WLSGRA012;
using namespace std;

Image::Image(){
}

Image::~Image(){
}

void Image::Read(string fileName){
    fstream reader(fileName, ios::in | ios::binary);
    string line;
    stringstream ss;

    //remove the version line and the comments
    //remove version line
    getline(reader, line);
    
    //remove comments
    getline(reader, line);
    streampos oldPos;
    while (line.substr(0,1) == "#"){
        oldPos = reader.tellg();
        cout << line << endl;
        getline(reader, line);
    }
    reader.seekg(oldPos);

    //read number of rows and columns
    ss << reader.rdbuf();
    ss >> height >> width;
    cout << height << " : " << width << endl;

    //read thresh
    ss >> thresh;
    cout << thresh << endl;

    //read data
    char* tempData = new char[width*height];
    reader.read(tempData, height*width);
    fstream writer("output.pgm", ios::out | ios::trunc);
    writer.write("P5\n", 3);
    writer.write("#This is a copy", 15);
    writer.write("512 512", 8);
    writer.write("255", 3);
    // writer.write(tempData, height*width);

    fstream feader("output.pgm", ios::in);
    getline(feader, line);
    cout << "out: " << line << endl;
}

Image Image::operator+(Image I){
    cout << "adding Image" << endl;
}

