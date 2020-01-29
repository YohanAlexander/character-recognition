#include<iostream>
#include<cstring>
#include"Image.hpp"

int main(){

	char path[51];

	printf("Nome do arquivo pbm: ");
	scanf("%s", path);

	Image input;
	input.loadImage(path);
	input.saveImage("input image test.pbm");

	Image eroded = input.erodeImage();
	eroded.saveImage("eroded image.pbm");

	Image dilated = eroded.dilatateImage().dilatateImage();
	dilated.saveImage("dilated image.pbm");

	return 0;

}
