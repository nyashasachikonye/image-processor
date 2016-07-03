/*
# File Image.cpp:
# File Description: File containing the image class implementation
# Project Title: Image Processing
# Assignment: CSC3022H C++ Assignment 4
# Author : Kuziwa Sachikonye
# Student Number: SCHKUZ002
# Date: 12/05/15
# Created on 09 May 2015, 11:06 PM
*/

#include "Image.h"

/*CONSTRUCTORS*/
SCHKUZ002::Image::Image() // Image Default Constructor
    {
    height = 0;
    width = 0;
    data.reset(new unsigned char [width * height]);
    //std::cout << "Image Default Constructor Created" << std::endl;
    }

SCHKUZ002::Image::Image(int h, int w) // Image Alternate Dimension Constructor
    {
    height = h;
    width = w;
    data.reset(new unsigned char [width * height]);
    //std::cout << "Image Non - Default Constructor Created" << std::endl;
    }

SCHKUZ002::Image::Image(Image& orig) // Image Copy Constructor
    {
    //std::cout << "Image Copy Constructor Called\n";
    height = orig.height;
    width = orig.width;
    data.reset(new unsigned char [width * height]);
    SCHKUZ002::Image::imgIterator beg = this->begin();
    SCHKUZ002::Image::imgIterator inBeg = orig.begin();
    SCHKUZ002::Image::imgIterator inEnd = orig.end();
    while (inBeg != inEnd)
        {
        *beg = *inBeg;
        beg++;
        inBeg++;
        }

    }

SCHKUZ002::Image::~Image() // Image Destructor
    {
    //std::cout << "Image Destructor Called\n";
    height = 0;
    width = 0;
    data.reset();
    //std::cout << "Image Destroyed\n";
    }

/*CLASS MEMBER FUNCTIONS*/
void SCHKUZ002::Image::load(std::string filename) // Load Image Operation
    {
    //std::cout << "Loading Image: " << filename << std::endl;
    std::ifstream inFile(filename, std::ios::binary);
    std::string f;
    do
        {
        getline(inFile, f);
        if (inFile.peek() == '2') //WARNING: Program may malfunction here.
            {
            width = atoi((f.substr(0, f.find(' '))).c_str());
            height = atoi((f.substr(f.find(' '))).c_str());
            //std::cout << "Image Dimensions | Height:" << height << " Width: " << width << std::endl;
            }
        } while ((f.compare("255")));
    unsigned char * inputD = new unsigned char [height * width];
    if (inFile.is_open())
        {
        inFile.read(reinterpret_cast<char*> (inputD), (height * width));
        } else
        {
        //std::cout << "Failed Read Operation: Unable To Open File" << std::endl;
        exit(0);
        }
    inFile.close();
    data.reset(inputD);
    //std::cout << "Image Loaded: " << filename << std::endl;
    }

void SCHKUZ002::Image::save(std::string filename) // Save Image Operation
    {
    //std::cout << "Saving Image: " << filename << std::endl;
    std::ofstream outFile((filename), std::ios::binary);
    if (outFile.is_open())
        {
        outFile << std::noskipws << "P5\n";
        outFile << std::noskipws << "# CREATOR: GIMP PNM Filter Version 1.1\n";
        outFile << std::noskipws << width << " " << height << "\n";
        outFile << std::noskipws << "255\n";
        outFile.write(reinterpret_cast<char*> (data.get()), (height * width));
        } else
        {
        std::cout << "Failed Write Operation: Unable To Open File" << std::endl;
        exit(0);
        }
    outFile.close();
    //std::cout << "Image Saved: " << filename << std::endl;
    }

/*IMAGE OPERATIONS*/

/*OPERATORS*/
bool SCHKUZ002::Image::operator&&(SCHKUZ002::Image &otherImage)
    {
    //std::cout << "Dimensions Compared\n";
    return ((height == otherImage.getHeight())&&(width == otherImage.getWidth()));
    }

SCHKUZ002::Image& SCHKUZ002::Image::operator=(SCHKUZ002::Image otherImage) //Image Copy Assignment: Image1 = Image2;
    {
    //std::cout << "Copy Assignment of Image\n";
    height = otherImage.height;
    width = otherImage.width;
    data.reset(new unsigned char [width * height]);
    //data.reset(otherImage.data.get());
    SCHKUZ002::Image::imgIterator beg = this->begin();
    SCHKUZ002::Image::imgIterator inBeg = otherImage.begin();
    SCHKUZ002::Image::imgIterator inEnd = otherImage.end();
    while (inBeg != inEnd)
        {
        *beg = *inBeg;
        beg++;
        inBeg++;
        }
    //std::cout << "Image Copy Assigned\n";
    return *this;
    }

SCHKUZ002::Image& SCHKUZ002::Image::operator!() //Image Inversion Operator
    {
    //std::cout << "Image Invert Operation Called\n";
    SCHKUZ002::Image::imgIterator beg = this->begin();
    SCHKUZ002::Image::imgIterator end = this->end();
    while (beg != end)
        {
        *beg = 255 - *beg;
        beg++;
        }
    //std::cout << "Image Inverted\n";
    return *this;
    }

SCHKUZ002::Image& SCHKUZ002::Image::operator/(SCHKUZ002::Image otherImage) //Image Mask Operator
    {
    //std::cout << "Image Mask Operation Called\n";
    SCHKUZ002::Image *temp = new SCHKUZ002::Image(height, width);
    SCHKUZ002::Image::imgIterator beg = this->begin();
    SCHKUZ002::Image::imgIterator end = this->end();
    SCHKUZ002::Image::imgIterator inBeg = otherImage.begin();
    SCHKUZ002::Image::imgIterator outBeg = temp->begin();
    while (beg != end)
        {
        if ((*inBeg) == 255)
            {
            *outBeg = *beg;
            } else
            {
            *outBeg = 0;
            }
        beg++;
        outBeg++;
        inBeg++;
        }
    //std::cout << "Image Masked \n";
    return *temp;
    }

SCHKUZ002::Image& SCHKUZ002::Image::operator+(SCHKUZ002::Image otherImage) //Image Addition Operator
    {
    //std::cout << "Image Addition Operation Called\n";
    SCHKUZ002::Image *temp = new SCHKUZ002::Image(height, width);
    SCHKUZ002::Image::imgIterator beg = this->begin();
    SCHKUZ002::Image::imgIterator end = this->end();
    SCHKUZ002::Image::imgIterator inBeg = otherImage.begin();
    SCHKUZ002::Image::imgIterator outBeg = temp->begin();
    while (beg != end)
        {
        *outBeg = *inBeg + *beg;
        beg++;
        outBeg++;
        inBeg++;
        }
    //std::cout << "Images Added \n";
    return *temp;
    }

SCHKUZ002::Image& SCHKUZ002::Image::operator-(SCHKUZ002::Image otherImage) //Image Subtraction Operator
    {
    //std::cout << "Image Subtraction Operation Called\n";
    SCHKUZ002::Image *temp = new SCHKUZ002::Image(height, width);
    SCHKUZ002::Image::imgIterator beg = this->begin();
    SCHKUZ002::Image::imgIterator end = this->end();
    SCHKUZ002::Image::imgIterator inBeg = otherImage.begin();
    SCHKUZ002::Image::imgIterator outBeg = temp->begin();
    while (beg != end)
        {
        *outBeg = *beg - *inBeg;
        beg++;
        outBeg++;
        inBeg++;
        }
    //std::cout << "Image Subtracted \n";
    return *temp;
    }

SCHKUZ002::Image& SCHKUZ002::Image::operator*(int threshold) //Image Threshold Operator
    {
    //std::cout << "Image Threshold Operation Called\n";
    SCHKUZ002::Image::imgIterator beg = this->begin();
    SCHKUZ002::Image::imgIterator end = this->end();
    while (beg != end)
        {
        if (*beg > threshold)
            {
            *beg = 255;
            } else
            {
            *beg = 0;
            }

        beg++;
        }
    //std::cout << "Image Thresholded\n";
    return *this;
    }

//FILTER METHODS

struct imgFilter
    {
    int fSz;
    float ** fData;

    imgFilter(std::string filtrFileName)
        {

        std::string line;
        std::ifstream myfile(filtrFileName);
        myfile >> fSz;
        fData = new float *[fSz];
        while (myfile.good())
            {
            for (int row = 0; row < fSz; row++)
                {
                fData[row] = new float [fSz];
                for (int col = 0; col < fSz; col++)
                    {
                    myfile >> line;
                    fData[row][col] = atof(line.c_str());
                    }

                }
            }
        myfile.close();

        }

    void printFilter()
        {
        for (int row = 0; row < fSz; row++)
            {
            for (int col = 0; col < fSz; col++)
                {
                std::cout << fData[row][col] << "      ";
                }
            std::cout << std::endl;
            }
        }
    };

