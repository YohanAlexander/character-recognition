#include<iostream>
#include<cstring>
#include"Image.hpp"

int main(){

	char path[51];

	printf("Nome do arquivo pbm: ");
	scanf("%s", path);

	Image input;
	input.loadImage(path);
	//input.saveImage("input image test.pbm");

	Image average = input.getAverageImage();
	//average.saveImage("average image.pbm");

	Image eroded = average.erodeImage();
	//eroded.saveImage("eroded image.pbm");

	Image dilated = eroded.dilatateImage();
	//dilated.saveImage("dilated image.pbm");
	dilated.saveImage("sem ruido.pbm");


	return 0;

}
