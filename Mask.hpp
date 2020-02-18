#ifndef MASK_H
#define MASK_H

class Mask{

	private:
        //atributtes
		int maskSize = 0;
		int** pixel;

	public:
        //constructor
	    Mask();
        //destructor
	    ~Mask();
        //public methods
        void setMaskSize(int size);
	    int getMaskPixel(int x, int y);
	    int getMaskSize();
	    void setCrossMask();
        void setFullMask();

};

#endif
