# CPPND: Udacity Capstone Matrix Project

This is the repo for the Udacity Capstone Matrix project within the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Matrix Project offers the ability to store matrices and do operations on them. Frequently used operators were overloaded to use the data structured in a convenient way. The target of the matrix class was simplicity (light-weight compared to public libraries).

Furthermore the matrix class is used to show real world use-cases. 
Within this project an image class was created which is using the matrix class as internal representation of the image and does operations using other matrices on it. 

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./UdacityMatrix`

## File and Class Structure

## Rubric Points Required 
1. A README with instructions is included with the project.
2. The README indicates which project is chosen.
3. The README includes information about each rubric point addressed.

4. The submission must compile and run. (Tested on Ubuntu 22.04 x64)

5. The project demonstrates an understanding of C++ functions and control structures. (image.h:30)
6. The project reads data from a file and process the data, or the program writes data to a file. (image.cpp:84)
7. The project accepts user input and processes the input. (main.cpp:28)

8. The project uses Object Oriented Programming techniques. (matrix.h:11)
9. Classes use appropriate access specifiers for class members. (matrix.h:57)
10. Class constructors utilize member initialization lists. (matrix.cpp:17)
11. Classes abstract implementation details from their interfaces. (image.h:16)
12. Classes encapsulate behavior. (matrix.h:22)
13. Classes follow an appropriate inheritance hierarchy. (image.h:24)
14. Overloaded functions allow the same function to operate on different parameters. (matrix.h:36)
15. Derived class functions override virtual base class functions. (image.h:30)
16. Templates generalize functions in the project. (matrix.h:10)

17. The project makes use of references in function declarations. (matrix.h:43)
18. The project uses destructors appropriately. (image.h:29)
19. The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate. (not used)
20. The project follows the Rule of 5. (matrix.h:16)
21. The project uses move semantics to move data, instead of copying it, where possible. (image.cpp:188)
22. The project uses smart pointers instead of raw pointers. (image.h:21)

23. The project uses multithreading. (matrix.cpp:212)
24. A promise and future is used in the project. (not used)
25. A mutex or lock is used in the project. (matrix.cpp:254)
26. A condition variable is used in the project. (not used)


