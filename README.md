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