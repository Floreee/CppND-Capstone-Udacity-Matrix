#include <fstream>
#include <cstdint>
#include <cmath>
#include <iostream>

#include "matrix.h"
#include "image.h"

void Udacity::ImageBMP::input(const std::string &filename)
{
  // Open the file in binary mode
  std::ifstream file(filename, std::ios::binary);
  if (!file)
  {
    throw std::runtime_error("Unable to open file");
  }

  // Read the file header
  BITMAPFILEHEADER bf;
  // Read the bfType field (2 bytes)
  file.read((char *)&bf.bfType, sizeof(bf.bfType));

  // Read the bfSize field (4 bytes)
  file.read((char *)&bf.bfSize, sizeof(bf.bfSize));

  // Read the bfReserved1 and bfReserved2 fields (2 bytes each)
  file.read((char *)&bf.bfReserved1, sizeof(bf.bfReserved1));
  file.read((char *)&bf.bfReserved2, sizeof(bf.bfReserved2));

  // Read the bfOffBits field (4 bytes)
  file.read((char *)&bf.bfOffBits, sizeof(bf.bfOffBits));

  // Check that this is a bitmap file
  if (bf.bfType != 0x4d42)
  {
    throw std::runtime_error("File is not a bitmap");
  }

  // Read the info header
  BITMAPINFOHEADER bi;
  file.read((char *)&bi, sizeof(bi));

  // Calculate the size of the image in bytes
  int imageSize = bi.biSizeImage;
  if (imageSize == 0)
  {
    imageSize = bi.biWidth * bi.biHeight * (bi.biBitCount / 8);
  }

  // Read the image data
  std::vector<unsigned char> imageData(imageSize);
  file.read((char *)imageData.data(), imageSize);

  // Close the file
  file.close();

  // Create the matrix
  int _rows = bi.biHeight;
  int _cols = bi.biWidth;
  int channels = bi.biBitCount / 8; // Number of color channels in the image

  _mat->resize(_rows, _cols * channels);

  // Fill the matrix with the image data
  int index = 0;
  for (int i = 0; i < _rows; i++)
  {
    for (int j = 0; j < _cols; j++)
    {
      for (int k = 0; k < channels; k++)
      {
        _mat->set(i, j * channels + k, imageData[index]); // / 255.0;
        index++;
      }
    }
  }
}

void Udacity::ImageBMP::output(const std::string &filename)
{
  // Open the file in binary mode
  std::ofstream file(filename, std::ios::binary);
  if (!file)
  {
    // Error opening file
    throw std::runtime_error("Unable to open file");
  }

  int _cols = _mat->getCols() / 3;
  int _rows = _mat->getRows();

  // Calculate the number of bytes per row in the image data
  int bytesPerRow = ((3 * _cols + 3) / 4) * 4; // 3 bytes per pixel, rounded up to multiple of 4

  // Set the BITMAPFILEHEADER and BITMAPINFOHEADER values
  BITMAPFILEHEADER bf;
  bf.bfType = 0x4d42;                        // 'BM'
  bf.bfSize = 14 + 40 + bytesPerRow * _rows; // File size
  bf.bfReserved1 = 0;
  bf.bfReserved2 = 0;
  bf.bfOffBits = 14 + 40; // Offset to image data

  BITMAPINFOHEADER bi;
  bi.biSize = 40; // Size of BITMAPINFOHEADER
  bi.biWidth = _cols;
  bi.biHeight = _rows;
  bi.biPlanes = 1;                      // Must be 1
  bi.biBitCount = 24;                   // 24 bits per pixel
  bi.biCompression = 0;                 // No compression
  bi.biSizeImage = bytesPerRow * _rows; // Image size
  bi.biXPelsPerMeter = 0;
  bi.biYPelsPerMeter = 0;
  bi.biClrUsed = 0;
  bi.biClrImportant = 0;

  // Write the BITMAPFILEHEADER
  file.write((char *)&bf.bfType, 2);
  file.write((char *)&bf.bfSize, 4);
  file.write((char *)&bf.bfReserved1, 2);
  file.write((char *)&bf.bfReserved2, 2);
  file.write((char *)&bf.bfOffBits, 4);

  // Write the BITMAPINFOHEADER
  file.write((char *)&bi, sizeof(bi));

  // Write the image data
  for (int i = 0; i < _rows; i++)
  {
    // Write each row of the image
    for (int j = 0; j < _cols; j++)
    {
      // Write each pixel value
      unsigned char r = (unsigned char)(_mat->get(i, j * 3));     // * 255);
      unsigned char g = (unsigned char)(_mat->get(i, j * 3 + 1)); // * 255);
      unsigned char b = (unsigned char)(_mat->get(i, j * 3 + 2)); // * 255);
      file.put(r);
      file.put(g);
      file.put(b);
    }

    // Pad the row with zeros if necessary
    for (int j = 3 * _cols; j < bytesPerRow; j++)
    {
      file.put(0);
    }
  }

  file.close();
}

void Udacity::ImageBMP::flip(bool horizontal)
{
  // Get the number of rows and columns in the matrix
  int rows = _mat->getRows();
  int cols = _mat->getCols();

  // Create a new matrix to store the flipped image
  Matrix<double> flipped(rows, cols);

  // Flip the image horizontally or vertically
  if (horizontal)
  {
    // Flip the image horizontally
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j+=3)
      {
        //flipped.set(i, cols - 1 - j, _mat->get(i, j));
        flipped.set(i, cols - 1 - j - 2, _mat->get(i, j));
        flipped.set(i, cols - 1 - j - 1, _mat->get(i, j + 1));
        flipped.set(i, cols - 1 - j, _mat->get(i, j + 2));
      }
    }
  }
  else
  {
    // Flip the image vertically
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
      {
        flipped.set(rows - 1 - i, j, _mat->get(i, j));
      }
    }
  }

  // Replace the original matrix with the flipped matrix
  *_mat = std::move(flipped);
}

void Udacity::ImageBMP::grayscale()
{
  // Get the number of rows and columns in the matrix
  int rows = _mat->getRows();
  int cols = _mat->getCols();

  // Convert the image to grayscale
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j += 3)
    {
      // Calculate the grayscale value using the luminosity method
      double gray = 0.21 * _mat->get(i, j) + 0.72 * _mat->get(i, j + 1) + 0.07 * _mat->get(i, j + 2);

      // Set the grayscale value for all color channels
      _mat->set(i, j, gray);
      _mat->set(i, j + 1, gray);
      _mat->set(i, j + 2, gray);
    }
  }
}