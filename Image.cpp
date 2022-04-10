//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"



bool Image::load(string filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary|std::ios::in); // need to spec. binary & input mode for Windows users
    try
    {
        if (ifs.fail())
        {
            throw("Can't open input file");
        }

        std::string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
        ifs >> w >> h >> b;
        this->w = w;
        this->h = h;
        this->pixels = new Rgb[w * h];  // this will throw an exception if bad_alloc
        ifs.ignore(256, '\n'); // skip empty lines if necessary until we get to the binary data

        unsigned char pixel_buffer[3]; // buffer to store one pixel, with three channels red,green and blue

        // read each pixel one by one and convert bytes to floats
        for (int i = 0; i < (w * h); ++i)
        {
            ifs.read(reinterpret_cast<char *>(pixel_buffer), 3);
            this->pixels[i].r = pixel_buffer[0]; // / 255.f;
            this->pixels[i].g = pixel_buffer[1]; // / 255.f;
            this->pixels[i].b = pixel_buffer[2]; // / 255.f;
        }
        ifs.close();
    }
    catch (const char *err)
    {
        fprintf(stderr, "%s\n", err);
        ifs.close();
    }
    return true;

}

bool Image::loadRaw(string filename)
{
    return false;
}

bool Image::savePPM(string filename)
{
    if (this->w == 0 || this->h == 0)
    {
        fprintf(stderr, "Can't save an empty image\n");
        return false;
    }

    std::ofstream ofs;
    try
    {
        ofs.open(filename, std::ios::binary|std::ios::out); // need to spec. binary mode for Windows users
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << this->w << " " <<  this->h << "\n255\n";

        unsigned char r, g, b;
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i <  this->w *  this->h; ++i)
        {
//            r = static_cast<unsigned char>(std::min(1.f,  this->pixels[i].r) * 255);
//            g = static_cast<unsigned char>(std::min(1.f,  this->pixels[i].g) * 255);
//            b = static_cast<unsigned char>(std::min(1.f,  this->pixels[i].b) * 255);
//            ofs << r << g << b;

            ofs.write(reinterpret_cast<char *>(&this->pixels[i].r),1);    // write 1 byte;
            ofs.write(reinterpret_cast<char *>(&this->pixels[i].g),1);    // write 1 byte;
            ofs.write(reinterpret_cast<char *>(&this->pixels[i].b),1);    // write 1 byte;
        }
        ofs.close();
    }
    catch (const char *err)
    {
        fprintf(stderr, "%s\n", err);
        ofs.close();
    }
    return true;
}

void Image::filterRed()
{
    for (int i = 0; i < (w * h); i++)
    {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterGreen()
{
    for (int i = 0; i < (w * h); i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterBlue()
{
    for (int i = 0; i < (w * h); i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
    }
}
void Image::greyScale()
{
    for (int i = 0; i < (w * h); i++)
    {
        float averageGrey = (this->pixels[i].r + this->pixels[i].g + this->pixels[i].b)/3;
        this->pixels[i].r = averageGrey;
        this->pixels[i].g = averageGrey;
        this->pixels[i].b = averageGrey;
    }
}

void Image::flipHorizontal()
{
    for(int i = 0; i < getWidth()/2; i++)
    {
        for (int j = 0; j < getHeight(); j++)
        {
            Rgb pixel;
            pixel = this->pixels[i];

            this->pixels[i] = this->pixels[i];
            this->pixels[i] = pixel;
        }
    }
}
void Image::flipVertically()
{
    for(int i = 0; i < getHeight()/2; i++)
    {
        for (int j = 0; j < getWidth(); j++)
        {
            Rgb pixel;
            pixel = this->pixels[i];

            this->pixels[i] = this->pixels[i];
            this->pixels[i] = pixel;
        }
    }
}

void Image::AdditionalFunction2()
{

}
void Image::AdditionalFunction3()
{

}
void Image::AdditionalFunction1()
{

}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}