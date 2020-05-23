## Building and Testing
### Make
Build the programs by running `make`. This will create `bin/julia`, `bin/mandelbrot` and `bin/graph`.

Build the tests by running `make test`. This will create `j.data` and `j.ppm`. Open `j.ppm` with an image viewer and inspect the result.

### GCC
Create a `bin` directory with `mkdir bin`
Compile `graph` with `gcc src/graph.c -o bin/graph -lm -Iinclude`
Compile `julia` with `gcc src/julia.c -o bin/julia -lm`
Run `julia` and pipe the output to `graph` using these benchmark settings:
```
bin/julia -w 1024 -h 1024 -n 384 -b 1024 -x 3 -y 3 -u -1.5 -v -1.5 -r -0.757730701301672 -i 0.121160627920417 | 	bin/graph -w 1024 -h 1024 -p palette/flowers -s 0 -r 8192 > j.ppm
```
Open `j.ppm` with an image viewer and inspect the result.

## Using the programs
### `julia` and `mandelbrot`
Both programs produce the same format of output and use the same interface. The programs write an array of `double` to `stdout`. The output is intended to be saved to a file or piped into `graph`. 

To specify the image size, use `-w [int]` and `-h [int]`. To specify the maximum iterations, use `-n [int]`. To specify the bailout radius, use `-b [double]`. To specify the x-scale and y-scale, use `-x [double]` and `-y [double]`. To specify the x-offset and y-offset, use `-u [double]` and `-v [double]`. To specify the c value for a julia set, use `-r [double]` and `i [double]`.

Example:
```
bin/julia -w 1024 -h 1024 -n 384 -b 1024 -x 3 -y 3 -u -1.5 -v -1.5 -r -0.757730701301672 -i 0.121160627920417 > j.data
```
This writes `1024 * 1024 * sizeof(double)` bytes to `j.data`.  `graph` can used to create an image from `j.data`

### `graph`
This program reads an array of `double` from `stdin`, uses a palette to transform them into `uint8_t` tripplets, then writes the `uint8_t` to stdout prefixed with a PPM image file header. The output is intended to be saved to a file ending in `.ppm`. and viewed with an image viewing app. 

A palette file must be specified with `-p [filename]` as well as a palette range and a palette shift using `-r [int]` and `-s [double]` respectively.

Example:
```
bin/graph -w 1024 -h 1024 -p palette/flowers -s 0 -r 8192 < j.data > j.ppm
```
This reads `1024 * 1024 * sizeof(double)` from `j.data` and, uses `palette/flowers` as the palette file, and writes approximately `1024 * 1024 * 3` bytes to `j.ppm` Open `j.ppm` with an image viewer to inspect the result.
