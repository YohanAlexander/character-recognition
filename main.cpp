#include<iostream>
#include<cstring>
#include"Image.hpp"

int main(){

	char nome[51];
	printf("Nome do arquivo pbm: ");
	scanf("%s", nome);

	Image input;
	input.loadImage(nome);

	Image filteredImage = input.erodeImage().dilatateImage().dilatateImage().erodeImage().dilatateImage();
	//filteredImage.saveImage("Filtered.pbm");

	//Image filteredImage = input.getAverageImage();
	//filteredImage.saveImage("Filtered.pbm");

	Image highlights = filteredImage.erodeImage().highlight();
	//highlights.saveImage("Highlights.pbm");

	Image allInOne = filteredImage;
	allInOne.merge(highlights);
	allInOne.saveImage("destacada.pbm");

	return 0;

}
