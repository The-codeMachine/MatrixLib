# MatrixLib

MatrixLib is a C library that provides matrix operations, such as: matrix multiplication, transposition, addition, subtraction, etc. 

MatrixLib is planned to have bindings to other languages, however that is still in production.

# Installation / Use

To install MatrixLib simply use the following command to copy it to your desired folder:

```powershell
git clone https://github.com/The-codeMachine/MatrixLib.git
```

Currently, to access the matrix operations include "your/folder/dir/src/include/matrix.h", for multithreading include "your/folder/dir/src/include/multithreading.h"

When GPU multithreading is added a header for that will also need to be include if you want to do GPU multithreading.

Eventually, there will be a main.h that will include the necessary headers for you, and compile the correct source code. 

# Compilation

To compile this project successfully you must compile the CUDA components, and then the C components. To compile successfully enter the following commands:

```powershell
nvcc -c src/cude/gpu_matmul.cu -o gpu_matmul.obj # necessary for GPU compilation
cl src/matrix.c # necessary
cl src/multithreading.c # necessary
cl test/matrixgputest.c # any usage file

# then you must link
nvcc matrix.obj multithreading.obj gpu_matmul.obj test.obj -o app.exe

app
```

The above code was taken from the root directory of matrixlib.

To ensure that this will work please make sure you have CUDA's nvcc installed, and that you use x64 Native Tools for 2022 VS Development command prompt, 
to ensure that the nvcc can access the cl.exe.

# TODO

- Rename the mulithreading file into matrix multiplication
- Stress test
- Implement a better matrix by matrix multiplication algorithm