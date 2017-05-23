#include<iostream>
#include<fstream>
#include<sstream>
#include<memory>
#include"Image.h"

using namespace WLSGRA012;
using namespace std;

//Image
Image::Image(){
}

Image::~Image(){
}

//copy assignment constructor
Image::Image(const Image &I) : height(I.height), width(I.width), thresh(I.thresh){
    data = unique_ptr<unsigned char[]>(new unsigned char[width*height]);

    for (int i = 0; i <height*width; i++){
        data.get()[i] = I.data.get()[i];
    }
}

//move assignment constructor
Image &Image::operator=(Image && I){
    //  : height(I.height), width(I.width), thresh(I.thresh)
    cout << "Move assignment" << endl;
    return I;
}

//copy assignment contructor
Image &Image::operator=(const Image & I){
    height = I.height;
    width = I.width;
    thresh = I.thresh;
    data = unique_ptr<unsigned char[]>(new unsigned char[width*height]);

    for (int i = 0; i <height*width; i++){
        data.get()[i] = I.data.get()[i];
    }

    return *this;
}

void Image::Read(string fileName){
    name = fileName;
    fstream reader(fileName, ios::in | ios::binary);
    string line;

    if (reader.good()){
        //remove the version line and the comments
        //remove version line
        getline(reader, line);
        
        //remove comments
        getline(reader, line);
        streampos oldPos;
        while (line.substr(0,1) == "#"){
            oldPos = reader.tellg();
            getline(reader, line);
        }
        reader.seekg(oldPos);

        //read number of rows and columns
        reader >> height >> width;
        // //read thresh
        // reader >> thresh;
        // cout << thresh << endl;
        getline(reader, line);
        thresh = 255;

        //read data
        data = unique_ptr<unsigned char[]>(new unsigned char[width*height]);
        reader.read((char*)data.get(), height*width);
    } else {
         cout << "File: " << fileName << " failed to open!" << endl;
     }

     reader.close();

}

void Image::Write(string fileName){
    //will write Image file to fileName as a PGM
    fstream writer(fileName, ios::out | ios::binary | ios::trunc);
     if (writer.good()){
        writer << "P5" << endl << "#Assignment5 file - WLSGRA012" << endl << width << " " << height << endl << thresh << endl;

        Image::iterator beg = this->begin(), end = this->end(); 
        while (beg != end){
            writer << *beg;
            ++beg;
        }
        
     } else {
         cout << "File: " << fileName << " failed to open!" << endl;
     }

     writer.close();
    }

//operator overloads for Image
Image &Image::operator+(Image &I){
    cout << "Adding image " << name << " and " << I.name << "..." << endl;

    Image::iterator beg = this->begin(), end = this->end(); 
    Image::iterator inStart = I.begin(), inEnd = I.end();
    while ( beg != end) { 
        int pixel = (*inStart + *beg);

        beg = pixel;
        
        ++beg; ++inStart; 
    }

    return *this;
}

Image &Image::operator-(Image &I){
    cout << "Subtracting image " << name << " and " << I.name << "..." << endl;

    Image::iterator beg = this->begin(), end = this->end(); 
    Image::iterator inStart = I.begin(), inEnd = I.end();
    while ( beg != end) { 
        int pixel = (*beg - *inStart);
        beg = pixel;
        
        ++beg; ++inStart; 
    }

    return *this;
}

Image & Image::operator!(void){
    cout << "Inverting" << endl;

    Image::iterator beg = this->begin(), end = this->end(); 
    while ( beg != end) { 
        int pixel = 255 - (*beg);
        beg = pixel;
        
        ++beg;
    }

    return *this;
}

Image &Image::operator*(int f){
    cout << "Thresholding with value: " << f << endl;

    Image::iterator beg = this->begin(), end = this->end(); 
    while ( beg != end) { 
        int pixel = (*beg);
        if (pixel > f){
            pixel = 255;
        } else {
            pixel = 0;
        }
        beg = pixel;
        
        ++beg;
    }

    return *this;
}



//operator overloads for iterator
Image::iterator & Image::iterator::operator++(void){
    ptr++;
    return *this;
}

Image::iterator & Image::iterator::operator=(const Image::iterator & rhs){
    ptr = rhs.ptr;
    return *this;
}

Image::iterator & Image::iterator::operator=(int val){
    val = (val > 255) ? 255 : (val < 0) ? 0 : val;
    *ptr = (unsigned char) val;
    return *this;
}

unsigned char Image::iterator::operator*(void){
    return *ptr;
}

bool Image::iterator::operator!=(const Image::iterator & rhs){
    return rhs.ptr != ptr;
}
