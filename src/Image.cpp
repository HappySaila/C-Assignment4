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
    data.reset();
}

//copy constructor
Image::Image(Image &I) : height(I.height), width(I.width), thresh(I.thresh), name(I.name){
    data = unique_ptr<unsigned char[]>(new unsigned char[width*height]);

    Image::iterator beg = this->begin(), end = this->end(); 
    Image::iterator inStart = I.begin(), inEnd = I.end();
    while ( beg != end) { 
        beg = *inStart;

        ++beg; ++inStart; 
    }
}

//move assignment constructor
Image &Image::operator=(Image && I){
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
    fileName = "SourceImages/"+fileName;
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
    fileName = "CreatedImages/"+fileName;
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

bool Image::SameSize(const Image & I){
    return (height == I.height && width == I.width);
}

int Image::GetDimensions(){
    return height * width;
}

unique_ptr<unsigned char[]> &Image::GetData(){
    return data;
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

Image &Image::operator/(Image &I){
    cout << "Masking" << endl;

    Image::iterator beg = this->begin(), end = this->end(); 
    Image::iterator inStart = I.begin(), inEnd = I.end();
    while ( beg != end ) { 
        int pixel = (*beg - *inStart);
        
        if ((int)*beg == 255){
            //pixel is white - copy other images pixel over
            pixel = (int)*inStart;
        } else {
            //pixel is not white - keep images 
            pixel = 0;
        }
        
        beg = pixel;
        ++beg; ++inStart; 
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

bool Image::operator== (Image &I){
    if (height==I.height && width==I.width && thresh==I.thresh && name==I.name){
        //all variables are the same - check the data
        Image::iterator beg = this->begin(), end = this->end(); 
        Image::iterator inStart = I.begin(), inEnd = I.end();
        while ( beg != end) { 
            int pixel = (*inStart - *beg);
            if (pixel != 0){
                return false;
            }
           
            ++beg; ++inStart; 
        }
    }
    return true;
}


void Image::operator<<(string s){
    cout << "Reading image from " << s << "..." << endl;
    Read(s);
}

void Image::operator>>(string s){
    cout << "Writing image to " << s << "..." << endl;
    Write(s);
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
