#include <iostream>
#include <fstream>
#include <vector>

std::vector<char> outFile;

void RLECompression(const std::string path, std::vector<char> data){

    int lastShort = data[0];

    for (int i = 0, count = -1; i < data.size(); i++){
        count++;

        if (data[i] != lastShort){
            outFile.push_back(count);
            outFile.push_back(lastShort);

            lastShort = data[i];
            count = 0;
        }
    }

}

int main(int argc, char *argv[]){

    if (argc != 3){
        std::cout << "Useage: compress <infile> <outfile>\n";
        return 1;
    }

    std::fstream file;
    std::string inPath = argv[1];
    std::string outPath = argv[2];

    std::vector<short> fileBytes;

    // Read the file in binary
        std::ifstream input(inPath, std::ios::binary);

        std::vector<char> bytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

        input.close();

    RLECompression(inPath, bytes);

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