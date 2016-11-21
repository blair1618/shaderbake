```
> mkdir build
> cd build
> cmake ..
> cmake --build .
> ./shader2png
Usage: shader2png [options] <infile>
Options:
  <infile>     = Input GLSL fragment shader file.
  -o <outfile> = Set output image file to <file>. Default is 'out.png'.
  -w <width>   = Set output image width to <width> pixels. Default is 256.
  -h <height>  = Set output image height to <height> pixels. Default is 256.
  -i           = Use stdin as input file (ignores <infile> argument).
  -d           = Display the output image instead of saving to a file.
```
