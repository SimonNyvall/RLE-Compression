#include <fstream>
#include <iterator>
#include <vector>
#include <filesystem>

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

std::vector<char> outFileBytes;

// Returns the number of files in a directory
char fileCountInDirectory(char *path)
{
    DIR *dp;
    int fileCount = 0;
    struct dirent *ep;
    printf(path);
    dp = opendir(/*path*/ "/home/simon/Desktop/tests");

    if (dp != NULL)
    {
        while (ep = readdir(dp))
            fileCount++;

        (void)closedir(dp);
    }
    else
        perror("Couldn't open the directory");

    //printf("There's %d files in the current directory.\n", fileCount);

    return fileCount;
}

// Returns the byte size of the file
char getFileSize(char *path)
{
    std::ifstream inFile(path, std::ios::binary);
    inFile.seekg(0, std::ios::end);
    int fileSize = inFile.tellg();

    return fileSize;
}

void RLECompression(char *path, std::vector<char> fileBytes)
{
    int lastChar = fileBytes[0];
    for (int i = 0, count = -1; i < fileBytes.size(); i++)
    {
        count++;

        if (fileBytes[i] != lastChar)
        {
            outFileBytes.push_back(count);
            outFileBytes.push_back(lastChar);

            lastChar = fileBytes[i];
            count = 0;
        }
    }
}

int main()
{
    char *path = "/home/simon/Desktop/tests.test.txt";

    //std::vector<char> header;
    outFileBytes.push_back(1);
    outFileBytes.push_back(fileCountInDirectory(path));
    outFileBytes.push_back(getFileSize(path));

    // Loops through the files in the directory and compress them
    DIR *dir;
    struct dirent *diread;
    std::vector<char *> files;

    if ((dir = opendir(path)) != nullptr)
    {
        while ((diread = readdir(dir)) != nullptr)
        {
            files.push_back(diread->d_name);
        }
        closedir(dir);
    }
    else
    {
        perror("opendir");
        return EXIT_FAILURE;
    }

    for (auto file : files)
    {
        // Read the file in binary
        std::ifstream input(file, std::ios::binary);

        std::vector<char> inFileBytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

        input.close();

        RLECompression(file, inFileBytes);
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