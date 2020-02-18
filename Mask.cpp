#include<iostream>
#include<cstring>
#include"Mask.hpp"

Mask::Mask(){

	pixel = new int*[13];

	for(int i = 0; i < 13; i++){
        pixel[i] = new int[13];
        memset(pixel[i], 0, 13);
    }

}

Mask::~Mask(){

    for(int i = 0; i < 13; i++){
        delete [] pixel[i];
    }

	delete [] pixel;

}

void Mask::setMaskSize(int size){
    maskSize = size;
}

int Mask::getMaskPixel(int x, int y){
    return pixel[x][y];
}

int Mask::getMaskSize(){
    return maskSize;
}

void Mask::setCrossMask(){

    int padding = (maskSize - 1)/2;

    for(int y = 0; y < maskSize; y++){
		for(int x = 0; x < maskSize; x++){
			if(x == padding || y == padding){
                pixel[x][y] = 1;
            }
		}
	}
}

void Mask::setFullMask(){

	for(int y = 0; y < maskSize; y++){
		for(int x = 0; x < maskSize; x++){
			pixel[x][y] = 1;
		}
	}

}
