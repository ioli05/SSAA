#ifndef HOMEWORK_H
#define HOMEWORK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned char R, G, B;
}pixel;

typedef struct {
	char type[3];
	int width, height;
	int maxval;
	pixel** pixels;
}image;

void readInput(const char * fileName, image *img);

void writeData(const char * fileName, image *img);

void resize(image *in, image * out);

#endif /* HOMEWORK_H */