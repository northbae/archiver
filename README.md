# C++ File Archiver

This project is a C++ console application designed for compressing and decompressing files using various lossless compression algorithms. The archiver includes features to compare the efficiency of different methods by measuring execution time and compression ratios.

## Features

The project implements the following algorithms:

*   **RLE (Run-Length Encoding)** — Simple sequence encoding.
*   **Huffman Coding** — Entropy encoding algorithm.
*   **LZW (Lempel-Ziv-Welch)** — Dictionary-based compression method.
*   **BWT (Burrows-Wheeler Transform)** — Used as a data preprocessing step to improve compression efficiency for other algorithms.
*   **Arithmetic Coding** — *(In development)*.

## Project Structure

*   **`Tester.cpp/h`** — The main testing module. It manages the compression and decompression process, measures time (`clock_t`), and calculates the compression ratio.
*   **`RLE.cpp/h`, `Huffman.cpp/h`, `BWT.cpp/h`, `LZW.cpp/h`** — Implementation modules for the respective algorithms.
*   **`FileAccessor`** — A helper class for reading and writing files in binary mode.
*   **`files/`** — Folder containing source files for testing.
*   **`CompressedFiles/`** — Folder where compressed and decompressed files are saved.

## Build and Run

The project uses a **Makefile** for build automation. The default compiler is `clang++`.

### Requirements

*   `clang++` (or `g++` if you change the `CXX` variable in the Makefile)
*   Make
*   Linux / macOS (or Windows via WSL/MinGW)

### Build Commands

**Build Project (Release):**

Creates the `main` executable with optimization flags.
```bash
make
# or
make all
```
**Build for Debugging:**

Creates the main-debug executable with debug symbols (-g) and optimization disabled.

```Bash
make main-debug
```
**Clean Project:**

Removes compiled binary files.

```Bash
make clean
```
## Usage

In the current implementation, the logic is executed via the Tester class.

Workflow example:

The program reads the input file from the specified path.

A compression method is selected:

'R' — RLE

'H' — Huffman

'L' — LZW

Optionally, BWT is applied before the main compression.

The result is saved to the CompressedFiles/ folder.

Reverse decompression is performed to verify data integrity.

Example Output

Upon completion, the Tester::GetTesting method returns a statistics string:

```text

method LZW + BWT
compression time = 0.045 sec
decompression time = 0.032 sec
initial file size = 15400
final file size = 8200
compression ratio 53.246%
```
## File System

Ensure the output directory exists before running the program, otherwise the results may not be saved:

```Bash
mkdir -p CompressedFiles
```
