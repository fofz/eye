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
bin/julia -r 1024x1024 -s 3x3 -t -1.5+-1.5i -n 384 -b 1024 -c -0.757730701301672+0.121160627920417i | bin/graph -r 1024x1024 -p palette/flowers -s 4096 -t 2970 test.ppm
```
Open `test.ppm` with an image viewer and inspect the result.

## Using `graph`
`graph` reads `double` from `stdin` and creates a 24-bit rgb image. The output is written to a file as a binary PPM image. `graph` requires command line arguments. The first argument that is not an option specifies the output file destination. For example `graph out.ppm` will output to `out.ppm` Options include:
* `-r` size e.g. `-r 320x240'
* `-p` palette e.g. `-p palette/flowers`
* `-s` input scale e.g. `-s 4096` to map 0-1 to 0-4096 in the palette
* `-t` input shift e.g. `-t 2970` to shift the palette by 2970 positions
