## Building and Testing
### Make
Build the programs by running `make`. This will create `bin/graph`

Build the tests by running `make test`. This will create `test.ppm`. Open `test.ppm` with an image viewer and inspect the result.

### GCC
Run `mkdir bin`

Compile `graph` with `gcc -O2 src/graph.c -o bin/graph -lm -Iinclude`

Compile `julia` with `gcc -O2 src/julia.c -o bin/julia -lm -Iinclude`

Run `julia` and pipe the output to `graph` using these benchmark settings:
```
echo "P6 1024 1024 255" > test.ppm; bin/julia -r 1024x1024 -s 3x3 -t -1.5+-1.5i -n 384 -b 1024 -c -0.757730701301672+0.121160627920417i | bin/graph -r 1024x1024 -s 107 >> test.ppm
```
Open `test.ppm` with an image viewer and inspect the result.

## Using `graph`
`graph` reads bytes from `stdin` and uses a 256-color palette to map the input to a 24-bit RGB image. The output is written to `stdout` as 3-byte RGB tripplets. `graph` requires an `-r` option to specify the size of the image. Options include:
* `-r` size e.g. `-r 1024x1024` specify an image size of 1024 by 1024 pixels
* `-s` shift e.g. `-s 107` shift the palette by 107 positions
