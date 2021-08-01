g++ RleCompression.cpp -o RleCompression_gcc
clang++ RleCompression.cpp -o RleCompression_clang
ls -la
docker build -t rlecompression .
