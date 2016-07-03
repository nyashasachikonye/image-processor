/*
# File UnitTest.cpp:
# File Description: File containing the unit tests
# Project Title: Image Processing
# Assignment: CSC3022H C++ Assignment 4
# Author : Kuziwa Sachikonye
# Student Number: SCHKUZ002
# Date: 12/05/15
# Created on 09 May 2015, 11:06 PM
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Image.h"
#include <random>

bool dimCheck(SCHKUZ002::Image i1, SCHKUZ002::Image i2)
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
        return true;
        } else /* Statement Description: If the images have different dimensions
                * print an error*/
        {
        std::cout << "Invalid Image Dimension Error" << std::endl;
        std::cout << "Exiting Program" << std::endl;
        /* Statement Description: Exit program*/
        return false;

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

TEST_CASE("Image Operations", "[Image]")
    {
    SCHKUZ002::Image I, I1, I2, outputImg;

    REQUIRE(I.getHeight() == 0);
    REQUIRE(I.getWidth() == 0);

    SECTION("Command Line Parser")
        {
        int option;
        option = cmdParser('a');
        REQUIRE(option == 1);
        option = cmdParser('s');
        REQUIRE(option == 2);
        option = cmdParser('i');
        REQUIRE(option == 3);
        option = cmdParser('l');
        REQUIRE(option == 4);
        option = cmdParser('t');
        REQUIRE(option == 5);
        option = cmdParser('f');
        REQUIRE(option == 6);
        option = cmdParser('x');
        REQUIRE(option == 0);
        }

    SECTION("Dimension Checker")
        {
        I.setHeight(4);
        I.setWidth(5);

        I1.setHeight(4);
        I1.setWidth(5);

        I2.setHeight(9);
        I2.setWidth(10);

        REQUIRE(dimCheck(I, I2) == false);
        REQUIRE(dimCheck(I, I1) == true);
        REQUIRE(dimCheck(I1, I2) == false);
        }

    SECTION("Image Loading")
        {
        I.load("Sample Images/shrek_rectangular-1.pgm");
        REQUIRE(I.getHeight() == 1207);
        REQUIRE(I.getWidth() == 1280);
        }

    SECTION("Image Addition")
        {
        I1.load("Sample Images/shrek_rectangular-1.pgm");
        I2.load("Sample Images/donkey_mask-1.pgm");

        REQUIRE(dimCheck(I1, I2) == true);
        outputImg = I1 + I2;

        REQUIRE(outputImg.getHeight() == 1207);
        REQUIRE(outputImg.getWidth() == 1280);
        }

    SECTION("Image Subtraction")
        {
        I1.load("Sample Images/shrek_rectangular-1.pgm");
        I2.load("Sample Images/donkey_mask-1.pgm");

        REQUIRE(dimCheck(I1, I2) == true);
        outputImg = I1 - I2;

        REQUIRE(outputImg.getHeight() == 1207);
        REQUIRE(outputImg.getWidth() == 1280);
        }

    SECTION("Image Inversion")
        {
        I1.load("Sample Images/shrek_rectangular-1.pgm");
        outputImg = !I1;

        REQUIRE(outputImg.getHeight() == 1207);
        REQUIRE(outputImg.getWidth() == 1280);
        }

    SECTION("Image Threshold")
        {
        I1.load("Sample Images/shrek_rectangular-1.pgm");

        outputImg = I1 * 100;

        REQUIRE(outputImg.getHeight() == 1207);
        REQUIRE(outputImg.getWidth() == 1280);
        }

    SECTION("Image Mask")
        {
        I1.load("Sample Images/shrek_rectangular-1.pgm");
        I2.load("Sample Images/donkey_mask-1.pgm");

        REQUIRE(dimCheck(I1, I2) == true);
        outputImg = I1 / I2;

        REQUIRE(outputImg.getHeight() == 1207);
        REQUIRE(outputImg.getWidth() == 1280);
        }

    SECTION("Image Save")
        {
        I1.load("Sample Images/shrek_rectangular-1.pgm");

        outputImg = I1;

        REQUIRE(outputImg.getHeight() == 1207);
        REQUIRE(outputImg.getWidth() == 1280);
        }

    }
