# Author: Kuziwa Sachikonye
# Project Title: Image Processor
# Date 12/05/15 12 May 2015 03h59
# File Description: Makefile

####################### MAKEFILE #######################

CPP=g++
CPPFLAGS= -std=c++11

imageops: driver.o Image.o
	$(CPP) -o imageops driver.o Image.o  $(CCFLAGS)

unittest: UnitTest.o Image.o
	$(CPP) -o unittest UnitTest.o Image.o  $(CCFLAGS)

clean:
	rm -f *.o
	rm -f imageops
	rm -f unittest
	rm -f Output\ Files/*.pgm

test:	unittest
	./unittest

run:	imageops
	./imageops l Sample\ Images/shrek_rectangular-1.pgm Sample\ Images/donkey_mask-1.pgm Output\ Files/MaskModeOutput.pgm
	gimp Output\ Files/MaskModeOutput.pgm
