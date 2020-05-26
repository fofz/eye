#include <unistd.h>
#include <getopt.h>
#include "util.h"

vec2i size;
int i, opt;
double min, max, *in, *out;

int main(int argc, char **argv) {
	/* parse arguments */
	while((opt = getopt(argc, argv, "r:")) != -1)
		if(opt == 'r') size = atovec2i(optarg, "x");
	
	in = malloc(sizeof(double) * size.x * size.y); if(in == NULL) return 1;
	out = malloc(sizeof(double) * size.x * size.y); if(out == NULL) return 2;
	if(read(0, in, sizeof(double) * size.x * size.y) < 0) return 3;
	min = in[0]; max = in[0];
	for(i = 0; i < size.x * size.y; ++i)
		min = (in[i] < min ? in[i] : min),
		max = (in[i] > max ? in[i] : max);
	for(i = 0; i < size.x * size.y; ++i)
		out[i] = (in[i] - min) / (max - min);
	if(write(1, out, sizeof(double) * size.x * size.y) < 0) return 4;
	return 0;
}
