# RLE-Compression 
![rle-349606891](https://user-images.githubusercontent.com/50596493/183259051-d13e545d-d4e1-41da-af43-7126a17869e0.jpeg)

A small hobby project to better understand lossless compression. Run Length Compression is one of the more less complicated algorithms to implicate. You look at the byte array of a life and count the occurrence. For example, the number nine occurs six times in a row. Then you write [6][9] as two bytes and repeat until the byte array is done.

## Compile and run
Compile the program with g++ and execute the a.out file with two arguments for the starting and ending path.
```bash
g++ Compress.cpp
```
```bash
./a.out [in_path] [out_path]
```
![Screenshot from 2022-08-06 20-02-30](https://user-images.githubusercontent.com/50596493/183260636-12980fbc-9211-4ae7-a341-638ba1a507a5.png)
