#include <iostream>
#include <fstream>
#include <vector>

std::vector<char> outFile;

void RLEDecompression(const std::string path, std::vector<char> data){
    int times = 0;
    
    for (int i = 0; i < data.size() - 1; i++){

        if (i % 2 == 0){
            times = data[i];
    
            for (int j = 0; j < times; j++){
                outFile.push_back(data[i + 1]);
            }
        }
    }
}

int main(int argc, char *argv[]){

    if (argc != 3){
        std::cout << "Useage: compress <infile> <outfile>\n";
        return 1;
    }

    std::string inPath = argv[1];
    std::string outPath = argv[2];
    
    std::ifstream input(inPath, std::ios::binary);

        std::vector<char> bytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

        input.close();

    RLEDecompression(inPath, bytes);

    // Write the new file
    std::ofstream output(outPath, std::ofstream::binary);

    char *buffer = new char[outFile.size()];

    // Convert vector to char array
    for (int i = 0; i < outFile.size(); i++)
    {
        buffer[i] = outFile[i];
    }

    output.write(buffer, outFile.size());

    delete[] buffer;

    output.close();
    std::cout << "Done";

    return 0;
}