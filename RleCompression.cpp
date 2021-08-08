#include <fstream>
#include <iterator>
#include <vector>
#include <filesystem>
#include <string>

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

std::vector<char> outFileBytes;

// Returns the number of files in a directory
char fileCountInDirectory(const char *path)
{
    DIR *dp;
    int fileCount = 0;
    struct dirent *ep;
    dp = opendir(path);

    if (dp != NULL)
    {
        while ((ep = readdir(dp)) != 0)
            fileCount++;

        (void)closedir(dp);
    }
    else
        perror("Couldn't open the directory");

    //printf("There's %d files in the current directory.\n", fileCount);

    return fileCount;
}

// Returns the byte size of the file
char getFileSize(std::string path)
{
    std::ifstream inFile(path, std::ios::binary);
    inFile.seekg(0, std::ios::end);
    int fileSize = inFile.tellg();

    return fileSize;
}

void RLECompression(std::string path, std::vector<char> fileBytes)
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
    const char *path = "/home/simon/Desktop/tests/";

    outFileBytes.push_back(1);
    outFileBytes.push_back(fileCountInDirectory(path));

    // Loops through the files in the directory and compress them
    DIR *dir;
    struct dirent *dirent;
    std::vector<std::string> files;

    if ((dir = opendir(path)) != nullptr)
    {
        while ((dirent = readdir(dir)) != nullptr)
        {
            if (dirent->d_type != DT_DIR)
            {
                files.push_back(std::string(dirent->d_name));
            }
        }
        closedir(dir);
    }
    else
    {
        perror("opendir");
        return EXIT_FAILURE;
    }

    // -------------------------------------------------------------------

    std::string pathFile;
    for (int i = 0; i < files.size(); i++)
    {
        pathFile = path;
        pathFile += files[i];

        // Read the file in binary
        std::ifstream input(pathFile, std::ios::binary);

        std::vector<char> inFileBytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

        input.close();

        outFileBytes.push_back(getFileSize(pathFile));

        RLECompression(pathFile, inFileBytes);
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