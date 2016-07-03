/*
# File Image.h:
# File Description: Image Header File
# Project Title: Image Processing
# Assignment: CSC3022H C++ Assignment 4
# Author : Kuziwa Sachikonye
# Student Number: SCHKUZ002
# Date: 12/05/15
# Created on 09 May 2015, 11:06 PM
*/

#ifndef IMAGE_H
#define	IMAGE_H

#include <iostream>
#include <fstream>
#include <memory>
#include <string>

namespace SCHKUZ002 {

    class Image {
    private:
        /*CLASS VARIABLES*/
        int width, height;
        std::unique_ptr<unsigned char[] > data; // Image Data Member
    public:

        /*CONSTRUCTORS*/
        Image(); // Image Default Constructor
        Image(Image& orig); // Image Copy Constructor
        Image(int h, int w); // Image Alternate Dimension Constructor
        ~Image(); // Image Destructor

        /*CLASS MEMBER FUNCTIONS*/
        void load(std::string filename); // Load Image Operation
        void save(std::string filename); // Save Image Operation

        int getHeight() const {
            return height;
        }

        int getWidth() const {
            return width;
        }

        unsigned char * getBuffer() {
            return data.get();
        }

        void setHeight(int h) {
            height = h;
        }

        void setWidth(int w) {
            width = w;
        }

        void setData(unsigned char * a) {
            data.reset(a);
        }
        /*IMAGE OPERATIONS*/

        /*ITERATOR*/
        class imgIterator {
        private:
            unsigned char *ptr;
            friend class Image;

            imgIterator(unsigned char *u_charPtr) {
                //std::cout << "Iterator Constructed" << std::endl;
                ptr = u_charPtr;
            }
        public:

            imgIterator(const imgIterator & rhs) {
                //std::cout << "Iterator Constructed" << std::endl;
                ptr = rhs.ptr;
            }

            /*ITERATOR OPERATORS*/

            unsigned char& operator*() {
                //std::cout << "Iterator Dereferenced" << std::endl;
                return *ptr;
            }

            imgIterator& operator=(const imgIterator & rhs) {
                ptr = rhs.ptr;
                //std::cout << "Iterator Re-Assigned" << std::endl;
                return *this;
            }

            imgIterator operator++(int) {
                //std::cout << "Iterator Incremented" << std::endl;
                imgIterator temp = *this;
                ++ptr;
                return temp;
            }

            bool operator==(imgIterator &cP2) {
                return ptr == cP2.ptr;
                //std::cout << "Methods Compared" << std::endl;
            }

            bool operator!=(imgIterator &cP2) {
                return !(ptr == cP2.ptr);
                //std::cout << "Methods Compared Again" << std::endl;
            }

        };

        imgIterator begin(void) {
            return imgIterator((unsigned char*) data.get());
        }

        imgIterator end(void) {
            return imgIterator(data.get()+(width * height));
        }

        /*OPERATORS*/
        bool operator&&(Image &otherImage); //Image Dimension Comparator Operator

        Image& operator=(Image otherImage); //Image Copy Assignment Operator

        Image& operator!(); //Image Inversion Operator

        Image& operator/(Image otherImage); //Image Mask Operator

        Image& operator+(Image otherImage); //Image Add Operator

        Image& operator-(Image otherImage); //Image Subtraction Operator

        Image& operator*(int threshold); //Image Threshold Operator
    };
}

#endif	/* IMAGE_H */
