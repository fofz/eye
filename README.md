## Building and Testing
### Make
Build the programs by running `make`. This will create `bin/graph`

Build the tests by running `make test`. This will create `test.ppm`. Open `test.ppm` with an image viewer and inspect the result.

### GCC
Run `mkdir bin`

Compile `graph` with `gcc src/graph.c -o bin/graph -lm -Iinclude`

Compile `julia` with `gcc src/julia.c -o bin/julia -lm -Iinclude`

Run `julia` and pipe the output to `graph` using these benchmark settings:
```
bin/julia -r 1024x1024 -s 3x3 -t -1.5+-1.5i -n 384 -b 1024 -c -0.757730701301672+0.121160627920417i | bin/graph -r 1024x1024 -p palette/flowers -s 640 test.ppm
```
Open `test.ppm` with an image viewer and inspect the result.

## Using `graph`
`graph` reads bytes from `stdin` and creates a 24-bit rgb image by indexing a 24-bit color palette with the input values. The output is written to a file as a binary PPM image. `graph` requires command line arguments. The first argument that is not an option specifies the output file. For example `graph out.ppm` will write to `out.ppm` Options for `graph` include:
* `-r` size e.g. `-r 320x240` specify the size of the image
* `-p` palette e.g. `-p palette/flowers` specify the palette
* `-s` shift e.g. `-s 640` shift the palette by 640 positions
