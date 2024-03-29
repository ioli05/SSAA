#ifndef HOMEWORK_H1
#define HOMEWORK_H1

typedef struct {
	unsigned char colorPixel;
} pixel;

typedef struct {
	char type[2];
	int width, height, maxval;
	int distance;
	pixel** pixels;
}image;


void initialize(image *im);
void render(image *im);
void writeData(const char * fileName, image *img);

#endif /* HOMEWORK_H1 */