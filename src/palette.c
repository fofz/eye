#include <unistd.h>
#include <getopt.h>
#include <stdint.h>
#include <math.h>
#include "util.h"

size_t size; int i, opt; uint8_t *out;

int main(int argc, char **argv) {
	/* parse arguments */
	do switch(opt = getopt(argc, argv, "n:")) {
	case 'n': size = atoi(optarg); break;
	default: break;
	} while(opt != -1);
	
	out = malloc(3 * size); if(out == NULL) return 1;
	for(i = 0; i < size; ++i) if(i < size / 2)
		out[i * 3    ] = pow((double)i * 2 / size, 2)   * 0xff,
		out[i * 3 + 1] =     (double)i * 2 / size       * 0xff,
		out[i * 3 + 2] = pow((double)i * 2 / size, 0.5) * 0xff;
	else
		out[i * 3    ] = pow((double)(size - i) * 2 / size, 0.5) * 0xff,
		out[i * 3 + 1] =     (double)(size - i) * 2 / size       * 0xff,
		out[i * 3 + 2] = pow((double)(size - i) * 2 / size, 2)   * 0xff;
	if(write(1, out, 3 * size) < 0) return 2;
}
