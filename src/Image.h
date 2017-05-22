#ifndef IMAGE_H
#define IMAGE_H

#include<memory>

namespace WLSGRA012{
    class Image{
        private:
            int width, height;
            int thresh;
            std::unique_ptr<unsigned char[]> data;
        public:
            Image();
            Image &operator=(Image &i)= default;
            Image(const Image & i)= default;

            ~Image();

            void Read(std::string fileName);
            //overloads
            Image operator+(Image I);
            Image operator-(Image I);
            Image operator/(Image I);

            class iterator{ 
                private:
                    unsigned char *ptr;
                    // construct only via Image class (begin/end)
                    iterator(u_char *p) : ptr(p) {}
                public:
                    //copy construct is public
                    iterator( const iterator & rhs) : ptr(rhs.ptr) {}
                    // define overloaded ops: *, ++, --, =
                    iterator & operator=(const iterator & rhs);
            };
    };
}





#endif