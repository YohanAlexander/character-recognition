#include<iostream>
#include<cstring>
#include"Image.hpp"

bool Image::checkIfTouch(int x, int y) const{

	if(pixels[x][y] == 1 || pixels[x-1][y] == 1 || pixels[x][y-1] == 1 || pixels[x+1][y] == 1 || pixels[x][y+1] == 1){
        return true;
    }

    else{
        return false;
    }

}

bool Image::checkIfInside(int x, int y) const{

	if(pixels[x][y] == 1 && pixels[x][y-1] == 1 && pixels[x][y+1] == 1 && pixels[x-1][y] == 1 && pixels[x+1][y] == 1){
        return true;
    }

    else{
        return false;
    }

}

//constructor
Image::Image(){

	pixels = new int*[4096];

    for(int i = 0; i < 4096; i++){
        pixels[i] = new int[4096]; memset(pixels[i], 0, 4096);
    }

}

//destructor
Image::~Image(){

	for(int i = 0; i < 4096; i++){
        delete [] pixels[i];
    }

    delete [] pixels;

}

Image& Image::operator=(const Image& returned){

	setImageSize(returned.imageX, returned.imageY);

	for(int x = 0; x < imageX; x++){
		for(int y = 0; y < imageY; y++){
			setPixel(x,y, returned.getPixel(x,y));
		}
	}

}

void Image::setPixel(int x, int y, int value){
    pixels[x][y] = value;
}

void Image::setImageSize(int xSize, int ySize){
    imageX = xSize;
    imageY = ySize;
}

int Image::getPixel(int x, int y) const{
    return pixels[x][y];
}

Image Image::dilatateImage() const{

	Image output;
	output.setImageSize(imageX, imageY);

	for(int x = 2; x < imageX - 2; x++){
		for(int y = 1; y < imageY - 1; y++){

			if(checkIfTouch(x,y)){
				output.setPixel(x,y,1);
			}

			else{
				output.setPixel(x,y,0);
			}
		}
	}

	return output;

}

Image Image::erodeImage() const{

	Image output;
	output.setImageSize(imageX, imageY);

	for(int x = 1; x < imageX - 1; x++){
		for(int y = 1; y < imageY - 1; y++){
			if(checkIfInside(x,y)){
				output.setPixel(x,y,1);
			}

			else{
				output.setPixel(x,y,0);
			}
		}
	}

	return output;

}

void Image::saveImage(char* path){

		FILE* savingImg;
		savingImg = fopen(path, "w+");

		fprintf(savingImg , "P1\n# CREATOR: GIMP PNM Filter Version 1.1\n%d %d\n", imageX, imageY);
		int endlIndex = 0;

		for(int line = 0; line < imageY ; line++){
			for(int column = 0; column < imageX; column++){

				if(endlIndex == 69){
					fprintf(savingImg, "%d\n", pixels[column][line]);
					endlIndex = 0;
				}

				else{
					fprintf(savingImg, "%d", pixels[column][line]);
					endlIndex++;
				}
			}
		}

		fclose(savingImg);
		std::cout << "Saved " << path << " \n";

}

void Image::loadImage(char* path){

	//Ler imagem em imagem.ppm
	FILE* file;
	file = fopen(path , "r");

	char header[5];
	fscanf(file, "%s", header);

	//Pular linha:
	char buffer[100];
	fgets(buffer, 100, file);
	char ignore[1024];
	fgets(ignore, sizeof(ignore), file);

	/////////////
	fscanf(file, "%d", &imageX);
	fscanf(file, "%d", &imageY);
	std::cout << "Resolucao: " << imageX << "x" << imageY << '\n';

	for(int line = 0; line < imageY ; line++){
		for(int column = 0; column < imageX; column++){

			char inputChar;
			fscanf(file, "%c", &inputChar);

			if(inputChar == '1'){
				pixels[column][line] = 1;
			}

			else if(inputChar == '0'){
				pixels[column][line] = 0;
			}

			else{
				column--;
			}
		}
	}

	fclose(file);

}
