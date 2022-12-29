#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <filesystem>

#include "matrix.h"
#include "image.h"
#include "test.h"

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        std::cerr << "Usage: UdacityMatrix -i INPUT_FILE -o OUTPUT_FILE [-fh] [-fv] [-g]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "   -i INPUT_FILE  : input file name (must be 24-bit BMP)" << std::endl;
        std::cout << "   -o OUTPUT_FILE : output file name" << std::endl;
        std::cout << "   -fh            : flip image horizontally" << std::endl;
        std::cout << "   -fv            : flip image vertically" << std::endl;
        std::cout << "   -g             : convert image to grayscale" << std::endl;
        std::cout << "   -h             : print this help text and exit" << std::endl;
        std::cout << "   -t            : test matrix class" << std::endl;
        return 0;
    }

    // Parse command line arguments
    std::filesystem::path inputPath;
    std::filesystem::path outputPath;
    bool flipHorizontal = false;
    bool flipVertical = false;
    bool grayscale = false;

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-i")
        {
            inputPath = argv[++i];
        }
        else if (arg == "-o")
        {
            outputPath = argv[++i];
        }
        else if (arg == "-fh")
        {
            flipHorizontal = true;
        }
        else if (arg == "-fv")
        {
            flipVertical = true;
        }
        else if (arg == "-g")
        {
            grayscale = true;
        }
        else if (arg == "-t")
        {
            test();
        }
        else if (arg == "-h")
        {
            std::cerr << "Usage: UdacityMatrix -i INPUT_FILE -o OUTPUT_FILE [-fh] [-fv] [-g] [-h] [-t]" << std::endl;
            std::cout << "   -i INPUT_FILE  : input file name (must be 24-bit BMP)" << std::endl;
            std::cout << "   -o OUTPUT_FILE : output file name" << std::endl;
            std::cout << "   -fh            : flip image horizontally" << std::endl;
            std::cout << "   -fv            : flip image vertically" << std::endl;
            std::cout << "   -g             : convert image to grayscale" << std::endl;
            std::cout << "   -h             : print this help text and exit" << std::endl;
            std::cout << "   -t             : test matrix class" << std::endl;
            return 0;
        }
        else
        {
            std::cerr << "Invalid argument: " << arg << std::endl;
            return 1;
        }
    }

    // Check that required arguments are provided
    if (inputPath.empty())
    {
        std::cerr << "Missing required argument(s) for input" << std::endl;
        std::cerr << "Usage: UdacityMatrix -i INPUT_FILE -o OUTPUT_FILE [-fh] [-fv] [-g] [-h] [-t]" << std::endl;
        return 1;
    }
    
    // Make path absolute 
    inputPath = std::filesystem::absolute(inputPath);
    
    if (outputPath.empty())
    {
        std::cerr << "Missing required argument(s) for output" << std::endl;
        std::cerr << "Usage: UdacityMatrix -i INPUT_FILE -o OUTPUT_FILE [-fh] [-fv] [-g] [-h] [-t]" << std::endl;
        return 1;
        
    }

    // Make path absolute 
    outputPath = std::filesystem::absolute(outputPath); 

    if (!std::filesystem::exists(inputPath)) 
    {
        std::cerr << "Input path does not exist: " << inputPath.string() << std::endl;
        std::cerr << "Usage: UdacityMatrix -i INPUT_FILE -o OUTPUT_FILE [-fh] [-fv] [-g] [-h] [-t]" << std::endl;
        return 1;
    }
    else if (!std::filesystem::exists(outputPath.parent_path()))
    {
        std::cerr << "Output path does not exist: " << outputPath.string() << std::endl;
        std::cerr << "Usage: UdacityMatrix -i INPUT_FILE -o OUTPUT_FILE [-fh] [-fv] [-g] [-h] [-t]" << std::endl;
        return 1;
    }

    // Create an ImageBMP object
    Udacity::ImageBMP image;

    // Load the image from the input file
    std::cout << "Reading file: " << inputPath << std::endl;
    image.input(inputPath.string());

    // Perform requested operations on the image
    if (flipHorizontal)
    {
        std::cout << "..horizontal flip" << std::endl;
        image.flip(true);
    }
    if (flipVertical)
    {
        std::cout << "..vertical flip" << std::endl;
        image.flip(false);
    }
    if (grayscale)
    {
        std::cout << "..grayscale" << std::endl;
        image.grayscale();
    }

    // Save the image to the output file
    std::cout << "Writing file: " << outputPath<< std::endl;
    image.output(outputPath.string());

    return 0;
}