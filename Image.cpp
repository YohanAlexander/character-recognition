#include<iostream>
#include<cstring>
#include"Image.hpp"
#include"Mask.hpp"

bool Image::checkIfTouch(int x, int y) const{

	if(pixels[x][y] == 1 || pixels[x-1][y] == 1 || pixels[x][y-1] == 1 || pixels[x+1][y] == 1 || pixels[x][y+1] == 1){
        return true;
    }

    else{
        return false;
    }

	/*bool checkIfTouch(int xIndex, int yIndex, Mask mask) const{

		for(int x = 0; x < mask.getMaskSize(); x++){
			for(int y = 0; y < mask.getMaskSize(); y++){
				if(mask.getMaskPixel(x,y) && getPixel((xIndex-1) + x, (yIndex-1) + y))
				return true;
			}
		}
		return false;
	}*/

}

bool Image::checkIfInside(int x, int y) const{

	if(pixels[x][y] == 1 && pixels[x][y-1] == 1 && pixels[x][y+1] == 1 && pixels[x-1][y] == 1 && pixels[x+1][y] == 1){
        return true;
    }

    else{
        return false;
    }

	/*bool checkIfInside(int xIndex, int yIndex, Mask mask) const{

		int maskSize = mask.getMaskSize();
		for(int x = 0; x < maskSize; x++){
			for(int y = 0; y < maskSize ; y++){
				if(mask.getMaskPixel(x,y) == 1 && getPixel((xIndex-1) + x ,(yIndex-1) + y) == 0)
				return false;
			}
		}
		return true;
	}*/

}

int Image::getAveragePixel(int x, int y) const{

	float averageCount = 0;

	for(int xIndex = x - 1; xIndex <= x + 1; xIndex++){
		for(int yIndex = y; yIndex <= y + 1; yIndex++){
			averageCount += Image::getPixel(xIndex,yIndex);
		}
	}

	averageCount = averageCount/9.0;

	if(averageCount >= 0.2){
		return 1;
	}

	else{
		return 0;
	}

}

Image Image::getDiff(Image img) const{

	Image output;
	output.setImageSize(imageX, imageY);

	for(int x = 1; x < imageX; x++){
		for(int y = 1; y < imageY; y++){

			if(getPixel(x,y) == 1 && img.getPixel(x,y) == 1){
				output.setPixel(x, y, 0);
			}

			else{
				output.setPixel(x, y, getPixel(x, y));
			}

		}

	}

	return output;

}

void Image::drawHighlight(int start, int end, Line line){

	for(int index = start; index <= end ; index++){
		setPixel(index, line.ceiling, 1);
	}

	for(int index = start; index <= end; index++){
		setPixel(index, line.floor, 1);
	}

	for(int index = line.ceiling; index <= line.floor; index++){
		setPixel(start, index, 1);
	}

	for(int index = line.ceiling; index <= line.floor; index++){
		setPixel(end, index, 1);
	}

	//std::cout << "XInit " << start << " XEnd " << end << " YInit " << line.ceiling << " YEnd " << line.floor << '\n';

}

//constructor
Image::Image(){

	pixels = new int*[4096];

    for(int i = 0; i < 4096; i++){
        pixels[i] = new int[4096]; memset(pixels[i], 0, 4096);
    }

}

//copy constructor
Image::Image(const Image& i):Image(){

	//std::cout << "Constructing cpy " << this << '\n';

	*this = i;

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

	return *this;

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

			if(checkIfTouch(x, y)){
				output.setPixel(x, y, 1);
			}

			/*if(checkIfTouch(x, y, mask)){
				output.setPixel(x, y, 1);
			}*/

			else{
				output.setPixel(x, y, 0);
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

			if(checkIfInside(x, y)){
				output.setPixel(x, y, 1);
			}

			/*if(checkIfInside(x, y, mask)){
				output.setPixel(x, y, 1);
			}*/

			else{
				output.setPixel(x,y,0);
			}
		}
	}

	return output;

}

Image Image::getAverageImage() const{

	Image output;
	output.setImageSize(imageX, imageY);

	for(int x = 1; x < imageX - 1; x++){
		for(int y = 1; y < imageY - 1; y++){
			int average = Image::getAveragePixel(x,y);
			output.setPixel(x,y,average);
		}
	}

	return output;

}

Image Image::getInternalGradient() const{

	//Mask gradientMask;
	//gradientMask.setMaskSize(3);
	//gradientMask.setFullMask();

	Image temp = erodeImage();
	Image output = getDiff(temp);
	return output;

}

Image Image::getExternalGradient() const{

	//Mask gradientMask;
	//gradientMask.setMaskSize(3);
	//gradientMask.setFullMask();

	Image temp = dilatateImage();
	Image output = temp.getDiff(temp.erodeImage());

	return output;

}

Image Image::highlight(){

	Image output;
	output.setImageSize(imageX, imageY);

	Line arrayOfLines[2048];
	int numberOfLines = 0;

	Letter arrayOfLetters[4096];
	int numberOfLetters = 0;
	int totalNumberOfLetters = 0;

	Word arrayOfWords[4096];
	int numberOfWords = 0;
	int totalNumberOfWords = 0;

	bool inLine = false;

	for(int y = 1; y < imageY - 1; y++){

		bool foundSmth = false;

		for(int x = 1; x < imageX - 1; x++){
			if(getPixel(x, y) == 1){
				foundSmth = true;
			}
		}

		if(foundSmth && !inLine){
			inLine = true;
			arrayOfLines[numberOfLines].ceiling = y;
		}

		if(!foundSmth && inLine){
			inLine = false;
			arrayOfLines[numberOfLines].floor = y;
			numberOfLines++;
		}

	}

	for(int nLine = 0; nLine < numberOfLines; nLine++){

		//std::cout << "Ceiling " << arrayOfLines[nLine].ceiling << " Floor " << arrayOfLines[nLine].floor << '\n'

		//Resetting array for each line
		for(int i = 0; i < numberOfLetters ; i++){
			arrayOfLetters[i].start = 0;
			arrayOfLetters[i].start = 0;
		}

		numberOfLetters = 0;

		for(int i = 0; i < numberOfWords ; i++){
			arrayOfWords[i].start = 0;
			arrayOfWords[i].start = 0;
		}

		numberOfWords = 0;
		bool inLetter = false;

		for(int x = 1; x < imageX; x++){

			bool foundSmth = false;

			for(int y = arrayOfLines[nLine].ceiling ; y <= arrayOfLines[nLine].floor; y++){
				if(getPixel(x, y) == 1){
					foundSmth = true;
				}
			}

			if(foundSmth && !inLetter){
				inLetter = true;
				arrayOfLetters[numberOfLetters].start = x;
			}

			if(!foundSmth && inLetter){
				inLetter = false;
				arrayOfLetters[numberOfLetters].end = x;
				numberOfLetters++;
			}

		}

		//Draw highlight of letters:
		/*for(int letterIndex = 0; letterIndex < numberOfLetters; letterIndex++){
			output.drawHighlight(arrayOfLetters[letterIndex].start, arrayOfLetters[letterIndex].end, arrayOfLines[nLine]);
		}*/

		//Draw highlight of words:
		bool inWord = false;
		Word word;

		for(int letterIndex = 0; letterIndex < numberOfLetters - 1; letterIndex++){

			int distance = arrayOfLetters[letterIndex+1].start - arrayOfLetters[letterIndex].end;

			if(!inWord){
				word.start = arrayOfLetters[letterIndex].start;
				inWord = true;
			}

			if(distance >= 6){
				word.end = arrayOfLetters[letterIndex].end;
				arrayOfWords[numberOfWords] = word;
				numberOfWords++;
				inWord = false;
			}

			if(letterIndex == (numberOfLetters - 2)){
				//std::cout << "Passed here\n";
				word.end = arrayOfLetters[letterIndex + 1].end;
				arrayOfWords[numberOfWords] = word;
				numberOfWords++;
				inWord = false;
			}

		}

		for(int wordIndex = 0; wordIndex < numberOfWords; wordIndex++){
			output.drawHighlight(arrayOfWords[wordIndex].start, arrayOfWords[wordIndex].end, arrayOfLines[nLine]);
		}

		totalNumberOfWords += numberOfWords;
		totalNumberOfLetters += numberOfLetters;

	}

	std::cout << "Number of lines: " << numberOfLines << "\nNumber of words: " << totalNumberOfWords << "\nNumber of letters: " << totalNumberOfLetters << '\n';
	return output;

}

Image Image::merge(Image img){

	Image output;
	output.setImageSize(imageX, imageY);

	for(int x = 1; x < imageX - 1; x++){
		for(int y = 1; y < imageY - 1; y++){
			if(img.getPixel(x, y) == 1){
				setPixel(x, y, 1);
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
