## Compiling the programs
### Make
Run `make` to compile `palette`, `graph`, `dither`, `dtou16`, `normalize` and `julia`. All of the compiled programs are in `bin`.

## Using `graph`
`graph` starts by reading 24-bit RGB palette data from `stdin`. The palette data is formatted as a sequence of `uint8_t` tripplets. The number of colors in the palette is specified using the `-n` option. After reading the palette data, `graph` reads 8-bit grayscale image data from `stdin`. The image data is a sequence of `uint8_t`. The size of the image is specified with the `-r` option. `graph` uses the palette data to transform the input data into a 24-bit RGB image. The image data is written to `stdout` as a sequence of `uint8_t` tripplets. Options for `graph` include:
* `-r` size e.g. `-r 1024x1024` specify an image size of 1024 by 1024 pixels
* `-n` psize e.g. `-n 256` specify a palette size of 256 colors
* `-s` pshift e.g. `-s 107` shift the palette by 107 positions

To create a PPM image using graph, first create a file with a PPM header: `echo "P6 1024 1024 255" > out.ppm`.

Run `graph`, passing it palette data followed by input data, and append the output to the `out.ppm`.
```
graph -r 1024x1024 -n 256 -s 107 < cat palette.data in.data >> out.ppm
```

`out.ppm` can be viewed with an image viewer.

## Demo
Running `demo.sh` requires Make and ImageMagick. Ubuntu users can install the required software with `sudo apt install make imagemagick`. 

Run `./demo.sh` to create `palette.data`, `julia.data`, `banner.jpg` and `animation.gif`. If elevated privilages are required, try running `chmod 755 demo.sh` first.
