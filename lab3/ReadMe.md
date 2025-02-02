# Buffer-Based Image Processing Project

## Overview
This project implements a producer-consumer model using C++ to process images in parallel. Producers read images from a directory, and consumers apply transformations using OpenCV, saving the processed images to another directory.

## Features
- Multithreaded producer-consumer model.
- Safe concurrent access to the buffer using mutex and condition variables.
- Image processing with OpenCV (e.g., bitwise NOT operation).
- Configurable number of producers, consumers, and delays.
- Execution time measurement for performance evaluation.

## Prerequisites
- C++17 compatible compiler.
- OpenCV library.
- CMake (minimum version 3.5).

## Setup and Build Instructions
1. **Clone the repository:**
   ```bash
   git clone <repository_url>
   cd <repository_directory>
   ```

2. **Create a build directory and navigate to it:**
   ```bash
   mkdir build && cd build
   ```

3. **Run CMake to generate build files:**
   ```bash
   cmake ..
   ```

4. **Build the project:**
   ```bash
   make
   ```

5. **Run the executable:**
   ```bash
   ./Buffer <Initial_Directory_Images_Path> <Result_Directory_Images_Path>
   ```

## File Structure
- **main.cpp:** Contains the main logic for setting up producers and consumers.
- **Image.hpp / Image.cpp:** Defines the `Image` class for handling image-related operations.
- **Buffer.hpp:** Template-based thread-safe buffer for producer-consumer operations.
- **CMakeLists.txt:** Configuration for building the project with CMake.

## Parameters
The following parameters can be adjusted in `main.cpp`:
- **NUM_PRODUCERS:** Number of producer threads (default: 5).
- **NUM_CONSUMERS:** Number of consumer threads (default: 5).
- **PRODUCER_DELAY_TO_PRODUCE:** Delay in nanoseconds for producers (default: 1).
- **CONSUMER_DELAY_TO_CONSUME:** Delay in nanoseconds for consumers (default: 3).

## Foolproof Checks
The program includes checks for:
- **Command-line arguments:**
  Ensures exactly two arguments are passed for input and output directories.
- **Directory validation:**
  Verifies the provided directories exist and contain valid images.
- **Buffer capacity:**
  Prevents overflows by limiting the buffer size to the predefined capacity.

## Usage Example
```bash
./Buffer /path/to/input/images /path/to/output/images
```

## Error Handling
- If invalid paths are provided or directories are empty, the program exits with an appropriate error message.
- If no image files with supported extensions (`png`, `jpg`) are found, the program notifies the user.

## Notes
- Ensure the input directory contains images with valid extensions (`png`, `jpg`).
- The output directory must have write permissions.
- The OpenCV library must be properly installed and linked.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

## Acknowledgments
- OpenCV library for image processing.
- C++ Standard Library for threading and synchronization tools.
