WLSGRA012 - Grant Wilson
Assignment 4 - Image processing

HOW TO RUN THE PROGRAM.
Please take note that my make file will do everything for you.
You do not have to enter any commands yourself as the make file will do this for you.

You can perform the following using the make file:
Assuming I1 = "Lenna_hat_mask.pgm" and I2 = "Lenna_standard.pgm"
make add - will add I1 and I2
make sub - will subtract I1 and I2
make mask - will mask I2 using I1
make invert = will invert I1
make thresh = will thresh I1 with an f value of 120
make test - will run all of my test cases

Please note that after you use one of the above function, the make file will clean up after itself.
This prevents you from calling your own functions. So this should be really easy to mark.

---------------------------------------------------------------------------------------------------

Files:
Image.h - contains header for Image class
Image.cpp - contains bodies for header definitions in Image.h
test.cpp - contains all test cases
main.cpp - runs the program

Functions of Image class:
Image &operator+(Image &I); add I1 and I2
Image &operator-(Image &I); subtract I1 and I2
Image &operator/(Image &I); mask I2 using I1
Image &operator!(void); invert I1
Image &operator* (int f); create a mask of I1 using thresh hold value f
bool operator== (Image &I); checks for equality with I1
void operator<<(std::string s); loads file s into I
void operator>>(std::string s); writes file s into I

Functions of Iterator class:
iterator & operator=(const iterator & rhs); assigns one pixel value to the current pixel
iterator & operator=(int pixel); assigns pixel value pixel to the pixel
iterator & operator++(void); increments iterator to next pixel
unsigned char operator*(void); dereferences iterator to access its pointer
bool operator!=(const iterator & rhs); checks for inequality between two pixels

---------------------------------------------------------------------------------------------------
