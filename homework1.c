#include "homework1.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int num_threads;
int resolution;
image *img;

void* threadFunction(void* var) {
	int thread_id = *(int*)var;

	for (int i = img->height - 1; i >= 0; i--) {
		int start = (thread_id) * (img->width / num_threads);
		int end = (thread_id + 1) * (img->width / num_threads);
		if (thread_id == num_threads - 1) {
			end = img->width;
		}
		for (int j = start; j < end; j++) {

			float x = j, y = resolution - i - 1;

			float scalingFactor = ((float) resolution) / 100;
			double distance = (-1 * (float)(x + 0.5f)) / scalingFactor + (2 * (float)(y + 0.5f)) / scalingFactor;
			distance = abs(distance) / sqrt(2 * 2 + 1 * 1);

			if (distance <= 3.0f) {
				img->pixels[i][j].colorPixel = 0;
			}
		}
	}
	

}
void initialize(image *im) {
	strcpy(im->type, "P5");
	im->width = resolution;
	im->height = resolution;
	im->maxval = 255;
	im->distance = 0;

	im->pixels = malloc(resolution * sizeof(pixel*));
	for (int i = 0; i < resolution; i++) {
		im->pixels[i] = malloc(resolution * sizeof(pixel));
		for (int j = 0; j < resolution; j++) {
			im->pixels[i][j].colorPixel = 255;
		}
	}
}

void render(image *im) {
	img = im;
	pthread_t tid[num_threads];
	int thread_id[num_threads];
	for (int i = 0; i < num_threads; i++)
		thread_id[i] = i;

	for (int i = 0; i < num_threads; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for (int i = 0; i < num_threads; i++) {
		pthread_join(tid[i], NULL);
	}

}

void writeData(const char * fileName, image *img) {
	FILE *file = fopen(fileName, "wb");

	if (file == NULL) {
		return;
	}
	else {
		fprintf(file, "%s\n", img->type);
		fprintf(file, "%d %d\n", img->width, img->height);
		fprintf(file, "%d\n", img->maxval);
		for (int i = 0; i < img->height; i++) {
			for (int j = 0; j < img->width; j++) {
					fwrite(&img->pixels[i][j].colorPixel, sizeof(unsigned char), 1, file);
			}
		}
		fclose(file);
	}
}

