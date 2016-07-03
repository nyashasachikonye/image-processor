/*
# File Driver.cpp:
# File Description: File containing the driver for the program
# Project Title: Image Processing
# Assignment: CSC3022H C++ Assignment 4
# Author : Kuziwa Sachikonye
# Student Number: SCHKUZ002
# Date: 12/05/15
# Created on 09 May 2015, 11:06 PM
*/


#include <cstdlib>
#include "Image.h"

void dimCheck(SCHKUZ002::Image i1, SCHKUZ002::Image i2)
    {
    /* Function Definition:
     * This function checks the dimensions of the images to make sure that images
     * are of the same dimension before performing binary operations on them.
     */

    if ((i1 && i2))
        /* Statement Description: If the images have the same height and width,
         * then do nothing.*/
        {
        //std::cout << "Images Have The Same Dimensions\n";
        } else /* Statement Description: If the images have different dimensions
                * print an error*/
        {
        std::cout << "Invalid Image Dimension Error" << std::endl;
        std::cout << "Exiting Program" << std::endl;
        /* Statement Description: Exit program*/
        exit(0);
        }
    }

int cmdParser(char option)
    {
    /* Function Definition:
     * This function converts the command-line "option" into a relevant integer and
     * returns that integer so that can be processed by the switch statement that
     * will decide the mode that the program must operate in.
     */
    if (option == 'a') /* Statement Description: Add Option*/
        {
        return 1;
        }
    if (option == 's') /* Statement Description: Subtract Option*/
        {
        return 2;
        }
    if (option == 'i') /* Statement Description: Invert Option*/
        {
        return 3;
        }
    if (option == 'l') /* Statement Description: Mask Option*/
        {
        return 4;
        }
    if (option == 't') /* Statement Description: Threshold Option*/
        {
        return 5;
        }
    if (option == 'f') /* Statement Description: Filter Option*/
        {
        return 6;
        } else /* Statement Description: Default Option  : This will exit the program*/
        {
        return 0;
        }

    }

int main(int argc, char** argv)
    {
    SCHKUZ002::Image I, I1, I2, outputImg;
    /*Command Line Parser*/
    int option = cmdParser(*argv[1]);
    switch (option) {
        case 1:
            std::cout << "Add Mode Selected" << std::endl;

            I1.load(argv[2]);
            I2.load(argv[3]);
            dimCheck(I1, I2);

            /***********************/
            outputImg = I1 + I2; /**
            ************************/

            outputImg.save(argv[4]);
            /* Statement Description: Add the two respective images pixel by pixel
             * to produce the output image.*/
            break;

        case 2:
            std::cout << "Subtract Mode Selected" << std::endl;
            I1.load(argv[2]);
            I2.load(argv[3]);
            dimCheck(I1, I2);

            /***********************/
            outputImg = I1 - I2; /**
            ************************/

            outputImg.save(argv[4]);
            /* Statement Description: Subtract the two respective images pixel by pixel
             * to produce the output image.*/
            break;

        case 3:
            std::cout << "Invert Mode Selected" << std::endl;
            I1.load(argv[2]);

            /***********************/
            outputImg = !I1; /******
            ************************/

            outputImg.save(argv[3]);
            /* Statement Description: Invert the image intensity (255 less the
             * pixel intensity).*/
            break;

        case 4:
            std::cout << "Mask Mode Selected" << std::endl;
            I1.load(argv[2]);
            I2.load(argv[3]);
            dimCheck(I1, I2);

            /***********************/
            outputImg = I1 / I2; /***
            ************************/

            outputImg.save(argv[4]);
            /* Statement Description: Divide the value of the first image by the value
             * of the second image pixel by pixel to produce the output image.*/

            break;
        case 5:
            std::cout << "Threshold Mode Selected" << std::endl;
            I1.load(argv[2]);
            int threshold;
            threshold = atoi(argv[3]);

            /******************************/
            outputImg = I1 * threshold; /**
            *******************************/

            outputImg.save(argv[4]);

            break;
        case 6:
            std::cout << "Filter Mode Selected" << std::endl;
            std::cout << "No Filter Method Sorry!\n";
            exit(0);
            break;
        default:
            std::cout << "Invalid Mode Selection. Exiting Program" << std::endl;
            exit(0);
    }
    return 0;
    }
