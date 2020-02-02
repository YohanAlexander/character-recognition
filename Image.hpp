#ifndef IMAGE_H
#define IMAGE_H

class Image{

	private:
        //atributtes
		int** pixels;
		int imageX, imageY;
        //private methods
        bool checkIfTouch(int x, int y) const;
        bool checkIfInside(int x, int y) const;
        int getAveragePixel(int x, int y) const;

    public:
        //constructor
        Image();
        //destructor
        ~Image();
        //sobrecarga do operador de igualdade
        Image& operator=(const Image& returned);
        //public methods
        void setPixel(int x, int y, int value);
        void setImageSize(int xSize, int ySize);
        int getPixel(int x, int y) const;
        Image dilatateImage() const;
        Image erodeImage() const;
        Image getAverageImage() const;
        void saveImage(char* name);
        void loadImage(char* name);

};

#endif
