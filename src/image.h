#ifndef IMAGE_H
#define IMAGE_H

#include <cstdint>
#include <memory>
#include "matrix.h"

namespace Udacity
{
    // Create abstract image class, so that all operations are supported independant of the image type (BMP,JPG,..) 
    class Image 
    {
        public:
            Image() : _mat(std::make_unique<Udacity::Matrix<double>>()) {}; 
            virtual ~Image() {};
            virtual void input(const std::string &filename) =  0;
            virtual void output(const std::string &filename) = 0;
            virtual void flip(bool horizontal) = 0;
            virtual void grayscale() = 0;
        protected: 
            std::unique_ptr<Udacity::Matrix<double>> _mat;
    };

    class ImageBMP : public Image
    {

    public:
        ImageBMP() {};
        ~ImageBMP() {};
        void input(const std::string &filename) override;
        void output(const std::string &filename) override;
        void flip(bool horizontal) override;
        void grayscale() override;
        

    private:
        struct BITMAPFILEHEADER
        {
            uint16_t bfType;
            uint32_t bfSize;
            uint16_t bfReserved1;
            uint16_t bfReserved2;
            uint32_t bfOffBits;
        };

        struct BITMAPINFOHEADER
        {
            uint32_t biSize;
            int32_t biWidth;
            int32_t biHeight;
            uint16_t biPlanes;
            uint16_t biBitCount;
            uint32_t biCompression;
            uint32_t biSizeImage;
            int32_t biXPelsPerMeter;
            int32_t biYPelsPerMeter;
            uint32_t biClrUsed;
            uint32_t biClrImportant;
        };
    };
}

#endif