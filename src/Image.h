#ifndef IMAGE_H
#define IMAGE_H

#include<memory>

namespace WLSGRA012{
    class Image{
        
        private:
            int width, height;
            std::string name;
            std::unique_ptr<unsigned char[]> data;
        public:
            int thresh;
            Image();
            Image &operator=(const Image & i);
            Image &operator=(Image && i);
            Image(Image &I);
            Image(Image &&I);

            ~Image();

            void Read(std::string fileName);
            void Write(std::string fileName);
            bool SameSize(const Image & I);
            int GetDimensions();
            std::unique_ptr<unsigned char[]> &GetData();
            //overloads
            Image &operator+(Image &I);
            Image &operator-(Image &I);
            Image &operator/(Image &I);
            Image &operator!(void);
            Image &operator* (int f);
            bool operator== (Image &I);
            void operator<<(std::string s);
            void operator>>(std::string s);

            class iterator{ 
                friend class Image;
                private:
                    unsigned char *ptr;
                public:
                    // construct only via Image class (begin/end)
                    iterator(u_char *p) : ptr(p) {

                    }
                    //copy construct is public
                    iterator( const iterator & rhs) : ptr(rhs.ptr) {}
                    // define overloaded ops: *, ++, --, =
                    iterator & operator=(const iterator & rhs);
                    iterator & operator=(int pixel);
                    iterator & operator++(void);
                    unsigned char operator*(void);
                    bool operator!=(const iterator & rhs);

            };

            iterator begin(void) { 
                return iterator(data.get());
            }

            iterator end(void) { 
                u_char *ptr = &data.get()[(width*height)];
                return iterator(ptr);
            }
    };

}





#endif