# MatrixLib

MatrixLib is a C library that provides matrix operations, such as: matrix multiplication, transposition, addition, subtraction, etc. 

MatrixLib is planned to have bindings to other languages, however that is still in production.

# Installation / Use

To install MatrixLib simply use the following command to copy it to your desired folder:

```powershell
git clone https://github.com/The-codeMachine/MatrixLib.git
```

Currently, to access the matrix operations include "your/folder/dir/src/include/matrix.h", for CPU multithreading include "your/folder/dir/src/include/cpuMultithreading.h"

When GPU multithreading is added a header for that will also need to be include if you want to do GPU multithreading.

Eventually, there will be a main.h that will include the necessary headers for you, and compile the correct source code. 

# Compilation

To compile this project successfully you must compile the CUDA components, and then the C components. To compile successfully enter the following commands:

```powershell
nvcc -c gpu_matmul.cu -o gpu_matmul.o
                                # another test file goes here (for compilation)
gcc -c matrix.c multithreading.c -o matrix.o

nvcc matrix.o gpu_matmul.o -o matrixlib

```
