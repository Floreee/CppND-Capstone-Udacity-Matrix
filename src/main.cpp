#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>
#include <filesystem>

#include "matrix.h"
#include "image.h"
#include "test.h"

int main(int argc, char *argv[])
{
    // Create an instance of the ImageBMP class
    Udacity::ImageBMP image;

    // Parse the command line arguments
    bool flip_horizontal = false;
    bool flip_vertical = false;
    bool grayscale = false;
    bool operation = false;
    std::string input_path = "";
    std::string output_path = "";
    std::string input_file = "";
    std::string output_file = "";
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        // Input file or folder
        if (arg == "-i")
        {
            if (i + 1 < argc)
            {
                input_path = argv[i + 1];
                input_path = std::filesystem::absolute(input_path);
                if (!std::filesystem::exists(input_path))
                {
                    std::cout << "Error: input file/folder does not exist." << std::endl;
                    return 1;
                }
            }
            else
            {
                std::cerr << "Error: missing input file or folder name" << std::endl;
                return 1;
            }
        }

        // Output file
        if (arg == "-o")
        {
            if (i + 1 < argc)
            {
                output_path = argv[i + 1];
                output_path = std::filesystem::absolute(output_path);
            }
            else
            {
                std::cerr << "Error: missing output file name" << std::endl;
                return 1;
            }
        }

        // Flip horizontally
        if (arg == "-fh")
        {
            flip_horizontal = true;
        }

        // Flip vertically
        if (arg == "-fv")
        {
            flip_vertical = true;
        }

        // Grayscale
        if (arg == "-g")
        {
            grayscale = true;
        }

        // Test 
        if (arg == "-t")
        {
            test();
            return 0;
        }

        // Help
        if (arg == "-h")
        {
            std::cout << "Usage: program -i input_file_or_folder -o output_file -fh -fv -g -op" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  -i input_file_or_folder  Specify the input file or folder (only .bmp files are supported)" << std::endl;
            std::cout << "  -o output_file           Specify the output file" << std::endl;
            std::cout << "  -fh                      Flip the image horizontally" << std::endl;
            std::cout << "  -fv                      Flip the image vertically" << std::endl;
            std::cout << "  -g                       Convert the image to grayscale" << std::endl;
            std::cout << "  -t                       Test matrix class and its functions (use this argument solely)" << std::endl;
            return 0;
        }
    }

    // Check if the input path is a folder
    DIR *dir = opendir(input_path.c_str());
    if (dir)
    {
        // Input path is a folder, so process all .bmp files in the folder
        std::vector<std::string> files;
        struct dirent *ent;
        while ((ent = readdir(dir)) != NULL)
        {
            if (ent->d_type == DT_REG) // Regular file
            {
                std::string file_name = ent->d_name;
                std::string file_ext = file_name.substr(file_name.find_last_of(".") + 1);
                std::transform(file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower);
                if (file_ext == "bmp")
                {
                    files.push_back(file_name);
                }
            }
        }
        closedir(dir);

        // Process the .bmp files in the folder
        for (const std::string &file : files)
        {
            std::string input_file = input_path + '/' + file;
            if (output_path == "")
            {
                output_path = input_path;
            }
            std::string output_file = output_path + "/edit_" + input_file; 

            image.input(input_file);
            if (flip_horizontal)
            {
                image.flip(true);
            }
            if (flip_vertical)
            {
                image.flip(false);
            }
            if (grayscale)
            {
                image.grayscale();
            }
            image.output(output_file);
        }
    }
    else
    {
        // Input path is a single file, so process it if it is a .bmp file
        std::string file_name = input_path.substr(input_path.find_last_of("/") + 1);
        std::string file_ext = file_name.substr(file_name.find_last_of(".") + 1);
        std::transform(file_ext.begin(), file_ext.end(), file_ext.begin(), ::tolower);
        if (file_ext == "bmp")
        {
            image.input(input_path);
            if (flip_horizontal)
            {
                image.flip(true);
            }
            if (flip_vertical)
            {
                image.flip(false);
            }
            if (grayscale)
            {
                image.grayscale();
            }
            if (output_path == "")
            {
                output_path = input_path.substr(0, input_path.find_last_of("/"));
                output_path += "/edit_" + file_name;
            }
            else if  ((output_path.find(".bmp") == std::string::npos))
            {
                output_path = std::filesystem::absolute(output_path).string() + "/edit_" + file_name;
            }
            image.output(output_path);
        }
        else
        {
            std::cerr << "Error: invalid input file (only .bmp files are supported)" << std::endl;
            return 1;
        }
    }

    return 0;
}