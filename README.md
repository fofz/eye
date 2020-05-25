## Compiling the programs
### Make
Run `make` to compile `palette`, `graph`, `dither`, `dtou16`, `normalize` and `julia`

All of the compiled programs will be in `bin`

## Using `graph`
`graph` reads bytes from `stdin` and uses a 256-color palette to map the input to a 24-bit RGB image. The output is written to `stdout` as 3-byte RGB tripplets. `graph` requires an `-r` option to specify the size of the image. Options include:
* `-r` size e.g. `-r 1024x1024` specify an image size of 1024 by 1024 pixels
* `-n` psize e.g. `-n 256` specify a palette size of 256 colors
* `-s` pshift e.g. `-s 107` shift the palette by 107 positions

## Demo
Run `./demo.sh` to create `palette.data`, `julia.data`, `banner.jpg` and `animation.gif`
