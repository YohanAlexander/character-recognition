#ifndef IMAGE_H
#define IMAGE_H

class Letter{
	public:
		int start, end;
};

class Word{
	public:
		int start, end;
};

class Line{
	public:
		int ceiling, floor;
};

class Image{

	private:
        //atributtes
		int** pixels;
		int imageX, imageY;
        //private methods
        bool checkIfTouch(int x, int y) const;
        bool checkIfInside(int x, int y) const;
        int getAveragePixel(int x, int y) const;
        Image getDiff(Image img) const;
        void drawHighlight(int start, int end, Line line);

    public:
        //constructor
        Image();
        //destructor
        ~Image();
        //copy constructor
        Image(const Image& i);
        //sobrecarga do operador de igualdade
        Image& operator=(const Image& returned);
        //public methods
        void setPixel(int x, int y, int value);
        void setImageSize(int xSize, int ySize);
        int getPixel(int x, int y) const;
        Image dilatateImage() const;
        Image erodeImage() const;
        Image getAverageImage() const;
        Image getInternalGradient() const;
        Image getExternalGradient() const;
        Image highlight();
        Image merge(Image img);
        void saveImage(char* name);
        void loadImage(char* name);

};

#endif
