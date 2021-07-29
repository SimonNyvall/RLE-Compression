#include <fstream>
#include <iterator>
#include <vector>

#include <sys/types.h>
#include <dirent.h>

char fileCountInDirectory(char *path)
{
    DIR *dp;
    int fileCount = 0;
    struct dirent *ep;
    dp = opendir("./");

    if (dp != NULL)
    {
        while (ep = readdir(dp))
            fileCount++;

        (void)closedir(dp);
    }
    else
        perror("Couldn't open the directory");

    printf("There's %d files in the current directory.\n", fileCount);

    return fileCount;
}

int main()
{
    std::vector<char> outFileBytes;
    char *path = "/home/simon/Desktop/test/test.txt";

    std::vector<char> header;
    outFileBytes.push_back(1);
    outFileBytes.push_back(fileCountInDirectory(path));

    // Read the file in binary
    std::ifstream input(path, std::ios::binary);

    std::vector<char> inFileBytes(
        (std::istreambuf_iterator<char>(input)),
        (std::istreambuf_iterator<char>()));

    input.close();

    // RLE compression
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