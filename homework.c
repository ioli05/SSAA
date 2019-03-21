#include "homework.h"
#include <stddef.h>
#include <string.h>
#include <pthread.h>

int num_threads;
int resize_factor;
int num;
image *input, *output;
void readInput(const char * fileName, image *img) {
	FILE *file;
	file = fopen(fileName, "rb");
	if (file == NULL) {
		return;
	}
	else {
		if (strcmp(img->type, "P5") == 0) {
			fscanf(file, "%s\n", img->type);
			fscanf(file, "%d %d\n", &img->width, &img->height);
			fscanf(file, "%d\n", &img->maxval);

			img->pixels = (pixel**)malloc(img->height * sizeof(pixel*));
			for (int i = 0; i < img->height; i++) {
				img->pixels[i] = (pixel*)malloc(img->width * sizeof(pixel));
				for (int j = 0; j < img->width; j++) {
					fread(&img->pixels[i][j].R, sizeof(unsigned char), 1, file);
					}
				}
			}
		else {
			fscanf(file, "%s\n", img->type);
			fscanf(file, "%d %d\n", &img->width, &img->height);
			fscanf(file, "%d\n", &img->maxval);

			img->pixels = (pixel**)malloc(img->height * sizeof(pixel*));
			for (int i = 0; i < img->height; i++) {
				img->pixels[i] = (pixel*)malloc(img->width * sizeof(pixel));
				for (int j = 0; j < img->width; j++) {
					if (strcmp(img->type, "P5") == 0) {
						fread(&img->pixels[i][j].R, sizeof(unsigned char), 1, file);
					}
					else {
						fread(&img->pixels[i][j], sizeof(pixel), 1, file);
					}
				}
			}
		}
	}
	fclose(file);
}

void writeData(const char * fileName, image *img) {
	FILE *file = fopen(fileName, "wb");

	if (file == NULL) {
		return;
	}
	else {
		if (strcmp(img->type, "P5") == 0) {
			fprintf(file, "%s\n", img->type);
			fprintf(file, "%d %d\n", img->width, img->height);
			fprintf(file, "%d\n", img->maxval);
			for (int i = 0; i < img->height; i++) {
				for (int j = 0; j < img->width; j++) {
					fwrite(&img->pixels[i][j].R, sizeof(unsigned char), 1, file);
				}
			}
		}
		else {
			fprintf(file, "%s\n", img->type);
			fprintf(file, "%d %d\n", img->width, img->height);
			fprintf(file, "%d\n", img->maxval);
			for (int i = 0; i < img->height; i++) {
				for (int j = 0; j < img->width; j++) {
					fwrite(&img->pixels[i][j], sizeof(pixel), 1, file);
				}
			}
		fclose(file);
		}
	}
}

void* threadFunction(void* var) {
	int thread_id = *(int*)var;

	if (resize_factor % 2 == 0) {
		if (strcmp(output->type, "P6") == 0) {
			unsigned int auxiliaryR, auxiliaryG, auxiliaryB;

			for (int i = 0; i < output->height; i++) {
				int start = (thread_id) * (output->width / num_threads);
				int end = (thread_id + 1) * (output->width / num_threads);
				if (thread_id == num_threads - 1) {
					end = output->width;
				}
				for (int j = start; j < end; j++) {

					auxiliaryR = 0, auxiliaryG = 0, auxiliaryB = 0;

					for (int row = i * resize_factor; row < i * resize_factor + resize_factor; row++) {
						for (int column = j * resize_factor; column < j * resize_factor + resize_factor; column++) {
							auxiliaryR += input->pixels[row][column].R;
							auxiliaryG += input->pixels[row][column].G;
							auxiliaryB += input->pixels[row][column].B;
						}
					}
					output->pixels[i][j].R = auxiliaryR / (resize_factor * resize_factor);
					output->pixels[i][j].G = auxiliaryG / (resize_factor * resize_factor);
					output->pixels[i][j].B = auxiliaryB / (resize_factor * resize_factor);

				}
			}
		}
		else {
			unsigned int auxiliaryR;

			for (int i = 0; i < output->height; i++) {
				int start = (thread_id) * (output->width / num_threads);
				int end = (thread_id + 1) * (output->width / num_threads);
				if (thread_id == num_threads - 1) {
					end = output->width;
				}
				for (int j = start; j < end; j++) {
					auxiliaryR = 0;

					for (int row = i * resize_factor; row < i * resize_factor + resize_factor; row++) {
						for (int column = j * resize_factor; column < j * resize_factor + resize_factor; column++) {
							auxiliaryR += input->pixels[row][column].R;
						}
					}
					output->pixels[i][j].R = auxiliaryR / (resize_factor * resize_factor);
				}
			}
		}
	}
	else {
		if (strcmp(output->type, "P6") == 0) {
			unsigned char gaussianKernel[3][3] = { { 1,2,1 },{ 2,4,2 },{ 1,2,1 } };
			pixel matriceAux[3][3];
			for (int i = 0; i < output->height; i++) {
				int start = (thread_id) * (output->width / num_threads);
				int end = (thread_id + 1) * (output->width / num_threads);
				if (thread_id == num_threads - 1) {
					end = output->width;
				}
				for (int j = start; j < end; j++) {
					int x = 0, y = 0;
					for (int row = i * resize_factor; row < i * resize_factor + resize_factor; row++) {
						for (int column = j * resize_factor; column < j * resize_factor + resize_factor; column++) {
							matriceAux[x][y] = input->pixels[row][column];
							y++;
						}
						x++;
						y = 0;
					}

					int auxiliaryR = 0, auxiliaryG = 0, auxiliaryB = 0;
					for (int row = 0; row < 3; row++) {
						for (int column = 0; column < 3; column++) {
							auxiliaryR += matriceAux[row][column].R * gaussianKernel[row][column];
							auxiliaryG += matriceAux[row][column].G * gaussianKernel[row][column];
							auxiliaryB += matriceAux[row][column].B * gaussianKernel[row][column];

						}
					}
					output->pixels[i][j].R = auxiliaryR / 16;
					output->pixels[i][j].G = auxiliaryG / 16;
					output->pixels[i][j].B = auxiliaryB / 16;
				}
			}
		}
		else {
			unsigned char gaussianKernel[3][3] = { { 1,2,1 },{ 2,4,2 },{ 1,2,1 } };
			unsigned char matriceAux[3][3];
			for (int i = 0; i < output->height; i++) {
				int start = (thread_id) * (output->width / num_threads);
				int end = (thread_id + 1) * (output->width / num_threads);
				if (thread_id == num_threads - 1) {
					end = output->width;
				}
				for (int j = start; j < end; j++) {
					int x = 0, y = 0;
					for (int row = i * resize_factor; row < i * resize_factor + resize_factor; row++) {
						for (int column = j * resize_factor; column < j * resize_factor + resize_factor; column++) {
							matriceAux[x][y] = input->pixels[row][column].R;
							y++;
						}
						x++;
						y = 0;
					}

					int auxiliaryR = 0;
					for (int row = 0; row < 3; row++) {
						for (int column = 0; column < 3; column++) {
							auxiliaryR += matriceAux[row][column] * gaussianKernel[row][column];
						}
					}
					output->pixels[i][j].R = auxiliaryR / 16;
				}
			}
		}
	}


}
void resize(image *in, image * out) { 
	
	strcpy(out->type, in->type);
	out->height = in->height / resize_factor;
	out->width = in->width / resize_factor;
	out->maxval = in->maxval;

	out->pixels = (pixel**) malloc(out->height * sizeof(pixel*));
	for (int i = 0; i < out->height; i++) {
		out->pixels[i] = (pixel*) malloc(out->width * sizeof(pixel));
	}
	input = in;
	output = out;
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