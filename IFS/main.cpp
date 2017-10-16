#include "matrix.h"
#include "vectors.h"
#include "ifs.h"
#include "image.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int main(int argc, char** argv)
{
	char *input_file = NULL;
	int points = 0;
	char *output_file = NULL;
	int n = 0;
	int width = 100;
	int height = 100;

	//ifs -input sierpinski_triangle.txt -points 10000 -iters 0 -size 200 -output sierpinski_triangle_0.tga

	for (int i = 1; i < argc; i++){
		if (!strcmp(argv[i], "-input")){
			i++; assert(i < argc);
			input_file = argv[i];
		}else if (!strcmp(argv[i], "-points")){
			i++; assert(i < argc);
			points = atoi(argv[i]);
		}else if (!strcmp(argv[i], "-iters")){
			i++; assert(i < argc);
			n = atoi(argv[i]);
		}else if (!strcmp(argv[i], "-size")){
			i++; assert(i < argc);
			int size = atoi(argv[i]);
			width = size;
			height = size;
		}else if (!strcmp(argv[i], "-output")){
			i++; assert(i < argc);   
			output_file = argv[i];
		}else {
			printf("whoops error with command line argument %d: '%s'\n", i, argv[i]);
			assert(0);
		}
	}

	Image image(width, height);
	IFS ifs(input_file);
	ifs.fractalRendering(image, points, n, output_file);
}