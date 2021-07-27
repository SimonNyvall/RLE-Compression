#include <fstream>
#include <iterator>
#include <vector>
//#include <iostream>

int main()
{

    std::ifstream input("/home/simon/Desktop/test/test.txt", std::ios::binary);

    // Read the file in binary
    std::vector<char> inFileBytes(
        (std::istreambuf_iterator<char>(input)),
        (std::istreambuf_iterator<char>()));

    input.close();

    // RLE compression
    std::vector<char> outFileBytes;
    int lastChar = inFileBytes[0];
    for (int i = 0, count = -1; i < inFileBytes.size(); i++)
    {
        count++;

        if (inFileBytes[i] != lastChar)
        {
            outFileBytes.push_back(count);
            outFileBytes.push_back(lastChar);

            lastChar = inFileBytes[i];
            count = 0;
        }
    }

    // Write the new file
    std::ofstream output("/home/simon/Desktop/test/test.frle", std::ofstream::binary);

    char *buffer = new char[outFileBytes.size()];

    // Convert vector to char array
    for (int i = 0; i < outFileBytes.size(); i++)
    {
        buffer[i] = outFileBytes[i];
    }

    output.write(buffer, outFileBytes.size());

    delete[] buffer;

    output.close();

    return 0;
}